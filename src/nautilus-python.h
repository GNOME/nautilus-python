/*
 *  nautilus-python.c - Nautilus Python extension
 * 
 *  Copyright (C) 2003, 2004 Novell, Inc.
 *  Copyright (C) 2004 Johan Dahlin
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Author: Calvin Gaisford <cgaisford@novell.com>
 *          Dave Camp <dave@ximian.com>
 * 
 */

#ifndef NAUTILUS_PYTHON_H
#define NAUTILUS_PYTHON_H

#include <glib-object.h>
#include <Python.h>

#ifdef DEBUG
# define debug(x) (g_printf( "nautilus-python:" x "\n"))
# define debug_enter() (g_printf("%s: entered\n", __FUNCTION__))
# define debug_enter_args(x, y) (g_printf("%s: entered " x "\n", __FUNCTION__, y))
#else
# define debug(x)
# define debug_enter()
# define debug_enter_args(x, y)
#endif

#define NAUTILUS_TYPE_OBJECT_LIST (nautilus_object_list_get_type ())
GType nautilus_object_list_get_type (void);

/* Macros from PyGTK, changed to return FALSE instead of nothing */
#define np_init_pygobject() { \
    PyObject *gobject = PyImport_ImportModule("gobject"); \
    if (gobject != NULL) { \
        PyObject *mdict = PyModule_GetDict(gobject); \
        PyObject *cobject = PyDict_GetItemString(mdict, "_PyGObject_API"); \
        if (PyCObject_Check(cobject)) \
            _PyGObject_API = (struct _PyGObject_Functions *)PyCObject_AsVoidPtr(cobject); \
        else { \
            PyErr_SetString(PyExc_RuntimeError, \
                            "could not find _PyGObject_API object"); \
	    return FALSE; \
        } \
    } else { \
        PyErr_SetString(PyExc_ImportError, \
                        "could not import gobject"); \
        return FALSE; \
    } \
}

#define np_init_pygtk() { \
    PyObject *pygtk = PyImport_ImportModule("gtk._gtk"); \
    if (pygtk != NULL) { \
	PyObject *module_dict = PyModule_GetDict(pygtk); \
	PyObject *cobject = PyDict_GetItemString(module_dict, "_PyGtk_API"); \
	if (PyCObject_Check(cobject)) \
	    _PyGtk_API = (struct _PyGtk_FunctionStruct*) \
		PyCObject_AsVoidPtr(cobject); \
	else { \
            PyErr_SetString(PyExc_RuntimeError, \
                            "could not find _PyGtk_API object"); \
	    return FALSE; \
        } \
    } else { \
        PyErr_SetString(PyExc_ImportError, \
                        "could not import gtk._gtk"); \
        return FALSE; \
    } \
}

PyTypeObject *_PyNautilusColumn_Type;
#define PyNautilusColumn_Type (*_PyNautilusColumn_Type)

PyTypeObject *_PyNautilusColumnProvider_Type;
#define PyNautilusColumnProvider_Type (*_PyNautilusColumnProvider_Type)

PyTypeObject *_PyNautilusInfoProvider_Type;
#define PyNautilusInfoProvider_Type (*_PyNautilusInfoProvider_Type)

PyTypeObject *_PyNautilusMenuItem_Type;
#define PyNautilusMenuItem_Type (*_PyNautilusMenuItem_Type)

PyTypeObject *_PyNautilusMenuProvider_Type;
#define PyNautilusMenuProvider_Type (*_PyNautilusMenuProvider_Type)

PyTypeObject *_PyNautilusPropertyPage_Type;
#define PyNautilusPropertyPage_Type (*_PyNautilusPropertyPage_Type)

PyTypeObject *_PyNautilusPropertyPageProvider_Type;
#define PyNautilusPropertyPageProvider_Type (*_PyNautilusPropertyPageProvider_Type)

#endif /* NAUTILUS_PYTHON_H */
