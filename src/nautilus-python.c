/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 *  Copyright (C) 2004,2005 Johan Dahlin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <Python.h>
#include <pygobject.h>
#include <gmodule.h>
#include <gtk/gtk.h>

#include "nautilus-python.h"
#include "nautilus-python-object.h"

#include <libnautilus-extension/nautilus-extension-types.h>

static const GDebugKey nautilus_python_debug_keys[] = {
	{"misc", NAUTILUS_PYTHON_DEBUG_MISC},
};
static const guint nautilus_python_ndebug_keys = sizeof (nautilus_python_debug_keys) / sizeof (GDebugKey);
NautilusPythonDebug nautilus_python_debug;

static gboolean nautilus_python_init_python(void);

static GArray *all_types = NULL;


static inline gboolean 
np_init_pygobject(void)
{
#ifdef Py_CAPSULE_H
		void *capsule = PyCapsule_Import("gobject._PyGObject_API", 0);
		if (capsule)
		{
			_PyGObject_API = (struct _PyGObject_Functions*)capsule;
			return TRUE;
		}
#endif
    PyObject *gobject = PyImport_ImportModule("gobject");
    if (gobject != NULL)
    {
        PyObject *mdict = PyModule_GetDict(gobject);
        PyObject *cobject = PyDict_GetItemString(mdict, "_PyGObject_API");
        if (PyCObject_Check(cobject))
        {
            _PyGObject_API = (struct _PyGObject_Functions *)PyCObject_AsVoidPtr(cobject);
        }
        else
        {
            PyErr_SetString(PyExc_RuntimeError,
                            "could not find _PyGObject_API object");
			PyErr_Print();
			return FALSE;
        }
    }
    else
    {
        PyErr_Print();
        g_warning("could not import gobject");
        return FALSE;
    }
	return TRUE;
}

static inline gboolean
np_init_pygi(void)
{
	PyObject *gi;
	
	gi = PyImport_ImportModule ("gi");
	if (gi == NULL)
	{
        PyErr_Print();
        g_warning("could not import gi");
        return FALSE;
	}
	
	return TRUE;
}

static void
nautilus_python_load_file(GTypeModule *type_module, 
						  const gchar *filename)
{
	PyObject *main_module, *main_locals, *locals, *key, *value;
	PyObject *module;
	GType gtype;
	Py_ssize_t pos = 0;
	
	debug_enter_args("filename=%s", filename);
	
	main_module = PyImport_AddModule("__main__");
	if (main_module == NULL)
	{
		g_warning("Could not get __main__.");
		return;
	}
	
	main_locals = PyModule_GetDict(main_module);
	module = PyImport_ImportModuleEx((char *) filename, main_locals, main_locals, NULL);
	if (!module)
	{
		PyErr_Print();
		return;
	}
	
	locals = PyModule_GetDict(module);
	
	while (PyDict_Next(locals, &pos, &key, &value))
	{
		if (!PyType_Check(value))
			continue;

		if (PyObject_IsSubclass(value, (PyObject*)&PyNautilusColumnProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusInfoProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusLocationWidgetProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusMenuProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusPropertyPageProvider_Type))
		{
			gtype = nautilus_python_object_get_type(type_module, value);
			g_array_append_val(all_types, gtype);
		}
	}
	
	debug("Loaded python modules");
}

static void
nautilus_python_load_dir (GTypeModule *module, 
						  const char  *dirname)
{
	GDir *dir;
	const char *name;
	gboolean initialized = FALSE;

	debug_enter_args("dirname=%s", dirname);
	
	dir = g_dir_open(dirname, 0, NULL);
	if (!dir)
		return;
			
	while ((name = g_dir_read_name(dir)))
	{
		if (g_str_has_suffix(name, ".py"))
		{
			char *modulename;
			int len;

			len = strlen(name) - 3;
			modulename = g_new0(char, len + 1 );
			strncpy(modulename, name, len);

			if (!initialized)
			{
				PyObject *sys_path, *py_path;
				
				/* n-p python part is initialized on demand (or not
				* at all if no extensions are found) */
				if (!nautilus_python_init_python())
				{
					g_warning("nautilus_python_init_python failed");
					g_dir_close(dir);
				}
				
				/* sys.path.insert(0, dirname) */
				sys_path = PySys_GetObject("path");
				py_path = PyString_FromString(dirname);
				PyList_Insert(sys_path, 0, py_path);
				Py_DECREF(py_path);
			}
			nautilus_python_load_file(module, modulename);
		}
	}	
}

static gboolean
nautilus_python_init_python (void)
{
	PyObject *sys_path, *nautilus;
	GModule *libpython;
	char *argv[] = { "nautilus", NULL };

	if (Py_IsInitialized())
		return TRUE;

  	debug("g_module_open " PY_LIB_LOC "/libpython" PYTHON_VERSION "." G_MODULE_SUFFIX ".1.0");
	libpython = g_module_open(PY_LIB_LOC "/libpython" PYTHON_VERSION "." G_MODULE_SUFFIX ".1.0", 0);
	if (!libpython)
		g_warning("g_module_open libpython failed: %s", g_module_error());

	debug("Py_Initialize");
	Py_Initialize();
	if (PyErr_Occurred())
	{
		PyErr_Print();
		return FALSE;
	}
	
	debug("PySys_SetArgv");
	PySys_SetArgv(1, argv);
	if (PyErr_Occurred())
	{
		PyErr_Print();
		return FALSE;
	}
	
	debug("Sanitize the python search path");
	PyRun_SimpleString("import sys; sys.path = filter(None, sys.path)");
	if (PyErr_Occurred())
	{
		PyErr_Print();
		return FALSE;
	}

	/* import gobject */
  	debug("init_pygobject");
	if (!np_init_pygobject())
	{
		g_warning("pygobject initialization failed");
		return FALSE;
	}
	
	/* import gi */
  	debug("init_pygi");
	if (!np_init_pygi())
	{
		g_warning("pygi initialization failed");
		return FALSE;
	}
	
	/* import nautilus */
	g_setenv("INSIDE_NAUTILUS_PYTHON", "", FALSE);
	debug("import nautilus");
	nautilus = PyImport_ImportModule("gi.repository.Nautilus");
	if (!nautilus)
	{
		PyErr_Print();
		return FALSE;
	}

	_PyGtkWidget_Type = pygobject_lookup_class(GTK_TYPE_WIDGET);
	g_assert(_PyGtkWidget_Type != NULL);

#define IMPORT(x, y) \
    _PyNautilus##x##_Type = (PyTypeObject *)PyObject_GetAttrString(nautilus, y); \
	if (_PyNautilus##x##_Type == NULL) { \
		PyErr_Print(); \
		return FALSE; \
	}

	IMPORT(Column, "Column");
	IMPORT(ColumnProvider, "ColumnProvider");
	IMPORT(InfoProvider, "InfoProvider");
	IMPORT(LocationWidgetProvider, "LocationWidgetProvider");
	IMPORT(Menu, "Menu");
	IMPORT(MenuItem, "MenuItem");
	IMPORT(MenuProvider, "MenuProvider");
	IMPORT(PropertyPage, "PropertyPage");
	IMPORT(PropertyPageProvider, "PropertyPageProvider");
	IMPORT(OperationHandle, "OperationHandle");

#undef IMPORT
	
	return TRUE;
}

void
nautilus_module_initialize(GTypeModule *module)
{
	gchar *user_extensions_dir;
	const gchar *env_string;

	env_string = g_getenv("NAUTILUS_PYTHON_DEBUG");
	if (env_string != NULL)
	{
		nautilus_python_debug = g_parse_debug_string(env_string,
													 nautilus_python_debug_keys,
													 nautilus_python_ndebug_keys);
		env_string = NULL;
    }
	
	debug_enter();

	all_types = g_array_new(FALSE, FALSE, sizeof(GType));

	// Look in the new global path, $DATADIR/nautilus-python/extensions
	nautilus_python_load_dir(module, DATADIR "/nautilus-python/extensions");

	// Look in XDG_DATA_DIR, ~/.local/share/nautilus-python/extensions
	user_extensions_dir = g_build_filename(g_get_user_data_dir(), 
		"nautilus-python", "extensions", NULL);
	nautilus_python_load_dir(module, user_extensions_dir);
}
 
void
nautilus_module_shutdown(void)
{
	debug_enter();

	if (Py_IsInitialized())
		Py_Finalize();

	g_array_free(all_types, TRUE);
}

void 
nautilus_module_list_types(const GType **types,
						   int          *num_types)
{
	debug_enter();
	
	*types = (GType*)all_types->data;
	*num_types = all_types->len;
}
