/*
 *  nautilus-python-object.h - Generation of wrapper objects for nautilus 
 *                           extension objects in python.
 * 
 *  Copyright (C) 2003 Novell, Inc.
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
 *  Author: Dave Camp <dave@ximian.com>
 * 
 */

#ifndef NAUTILUS_PYTHON_OBJECT_H
#define NAUTILUS_PYTHON_OBJECT_H

#include <Python.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _NautilusPythonObject       NautilusPythonObject;
typedef struct _NautilusPythonObjectClass  NautilusPythonObjectClass;

struct _NautilusPythonObject {
  GObject parent_slot;
  PyObject *instance;
};

struct _NautilusPythonObjectClass {
    GObjectClass parent_slot;
    PyObject *type;
};

GType nautilus_python_object_get_type (GTypeModule *module, PyObject *type);

G_END_DECLS

#endif
