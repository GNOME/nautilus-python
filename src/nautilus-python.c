/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 *  Copyright (C) 2004 Johan Dahlin
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
#include <pygtk/pygtk.h>

#include "nautilus-python.h"
#include "nautilus-python-object.h"
#include "pygnomevfs.h"

#include <libnautilus-extension/nautilus-extension-types.h>


static GArray *all_types = NULL;

#define ENTRY_POINT "nautilus_extension_types"

static void
nautilus_python_load_file(GTypeModule *type_module, char *filename)
{
	PyObject *main_module, *main_locals, *locals, *key, *value;
	PyObject *module;
	GType gtype;
	int pos = 0;
	
	debug_enter_args("filename=%s", filename);
	
	main_module = PyImport_AddModule("__main__");
	if (main_module == NULL) {
		g_warning("Could not get __main__.");
		return;
	}
	
	main_locals = PyModule_GetDict(main_module);
	module = PyImport_ImportModuleEx(filename, main_locals, main_locals, NULL);
	if (!module) {
		PyErr_Print();
		return;
	}
	
	locals = PyModule_GetDict(module);
	
	while (PyDict_Next(locals, &pos, &key, &value)) {
		if (!PyType_Check(value))
			continue;

		if (PyObject_IsSubclass(value, (PyObject*)&PyNautilusColumnProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusInfoProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusMenuProvider_Type) ||
			PyObject_IsSubclass(value, (PyObject*)&PyNautilusPropertyPageProvider_Type)) {
			
			gtype = nautilus_python_object_get_type(type_module, value);
			g_array_append_val(all_types, gtype);
		}
	}
	
	debug("Loaded python modules");
}

static GList *
nautilus_python_load_dir (const char *dirname)
{
	GDir *dir;
	GList *files = NULL;
	const char *name;

	debug_enter_args("dirname=%s", dirname);
	
	dir = g_dir_open(dirname, 0, NULL);
	if (!dir)
		return NULL;
			
	while ((name = g_dir_read_name(dir))) {
		if (g_str_has_suffix(name, ".py")) {
			char *modulename;
			int len;

			len = strlen(name) - 3;
			modulename = g_new0(char, len + 1 );
			strncpy(modulename, name, len);
			files = g_list_append(files, modulename);
		}
	}
	g_dir_close(dir);

	return files;
}

gboolean
nautilus_python_init_python (void)
{
	PyObject *pygtk, *mdict, *require;
	PyObject *sys_path, *nautilus, *gtk, *pygtk_version, *pygtk_required_version;
	char *home_dir;
	char *argv[] = { "nautilus", NULL };

	if (Py_IsInitialized())
		return TRUE;
	
	Py_Initialize();
	PySys_SetArgv(1, argv);
	
	pygtk = PyImport_ImportModule("pygtk");
	mdict = PyModule_GetDict(pygtk);
	require = PyDict_GetItemString(mdict, "require");
	PyObject_CallObject(require, Py_BuildValue("(S)", PyString_FromString("2.0")));
	
  	debug("init_pygobject");
	np_init_pygobject();
	debug("init_pygtk");
	np_init_pygtk();
	debug("init_gnomevfs");
        np_init_pygnomevfs();

    debug("pyg_enable_threads");
	setenv("PYGTK_USE_GIL_STATE_API", "", 0);
	pyg_enable_threads();
	
	gtk = PyImport_ImportModule("gtk");
	mdict = PyModule_GetDict(gtk);
	pygtk_version = PyDict_GetItemString(mdict, "pygtk_version");
	pygtk_required_version = Py_BuildValue("(iii)", 2, 4, 0);
	if (PyObject_Compare(pygtk_version, pygtk_required_version) == -1) {
		g_warning("PyGTK %s required, but %s found.",
				  PyString_AsString(PyObject_Repr(pygtk_required_version)),
				  PyString_AsString(PyObject_Repr(pygtk_version)));
		Py_DECREF(pygtk_required_version);
		return FALSE;
	}
	Py_DECREF(pygtk_required_version);
	
	debug("sys.path.insert(0, ...)");
	sys_path = PySys_GetObject("path");
	PyList_Insert(sys_path, 0,
				  PyString_FromString(NAUTILUS_LIBDIR "/nautilus-python"));
	home_dir = g_strdup_printf("%s/.nautilus/python-extensions/",
							   g_get_home_dir());
	PyList_Insert(sys_path, 1, PyString_FromString(home_dir));
	PyList_Insert(sys_path, 2,
				  PyString_FromString(NAUTILUS_LIBDIR "/nautilus/extensions-1.0/python"));
			
	debug("import nautilus");
	nautilus = PyImport_ImportModule("nautilus");
	if (!nautilus) {
		PyErr_Print();
		return FALSE;
	}

	mdict = PyModule_GetDict(nautilus);
	
#define IMPORT(x, y) \
    _PyNautilus##x##_Type = (PyTypeObject *)PyDict_GetItemString(mdict, y); \
	if (_PyNautilus##x##_Type == NULL) { \
		PyErr_Print(); \
		return FALSE; \
	}

	IMPORT(Column, "Column");
	IMPORT(ColumnProvider, "ColumnProvider");
	IMPORT(InfoProvider, "InfoProvider");
	IMPORT(MenuItem, "MenuItem");
	IMPORT(MenuProvider, "MenuProvider");
	IMPORT(PropertyPage, "PropertyPage");
	IMPORT(PropertyPageProvider, "PropertyPageProvider");

#undef IMPORT
	
	return TRUE;
}

void
nautilus_module_initialize(GTypeModule *module)
{
	GList *filenames, *l;
	
	debug_enter();

	all_types = g_array_new(FALSE, FALSE, sizeof(GType));

	if (!nautilus_python_init_python())
		return;
		
	filenames = nautilus_python_load_dir(NAUTILUS_LIBDIR "/nautilus/extensions-1.0/python");
	if (!filenames) {
		debug("No python extensions found.");
		return;
	}

	for (l = filenames; l; l = l->next) {
		nautilus_python_load_file(module, l->data);
		g_free(l->data);
	}

	g_list_free(filenames);
}
 
void
nautilus_module_shutdown(void)
{
	debug_enter();

	if (Py_IsInitialized()) {
		Py_Finalize();
	}

	debug("Shutting down nautilus-python extension.");
}

void 
nautilus_module_list_types(const GType **types,
						   int          *num_types)
{
	debug_enter();
	
	*types = (GType*)all_types->data;
	*num_types = all_types->len;
}
