/* -*- Mode: C; c-basic-offset: 4 -*-
 * Copyright (C) 2004  Johan Dahlin
 *
 *   nautilus.override: overrides for the nautilus extension library
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/* include this first, before NO_IMPORT_PYGOBJECT is defined */
#include <pygobject.h>
#include <pygtk/pygtk.h>

void pynautilus_register_classes (PyObject *d);
void pynautilus_add_constants(PyObject *module, const gchar *strip_prefix);

extern PyMethodDef pynautilus_functions[];

DL_EXPORT(void)
initnautilus(void)
{
    PyObject *m, *d;
    
    if (!g_getenv("INSIDE_NAUTILUS_PYTHON")) {
	Py_FatalError("This module can only be used from nautilus");
	return;
    }
	
    init_pygobject ();
    init_pygtk ();

    m = Py_InitModule ("nautilus", pynautilus_functions);
    d = PyModule_GetDict (m);
	
    pynautilus_register_classes (d);
    pynautilus_add_constants(m, "NAUTILUS_");    
}
