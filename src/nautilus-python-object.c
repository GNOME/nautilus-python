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
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <config.h>

#include "nautilus-python-object.h"
#include "nautilus-python.h"

#include <nautilus-extension.h>

#include <pygobject.h>

#include <string.h>

#define METHOD_PREFIX ""

static GObjectClass *parent_class;

/* These macros assumes the following things:
 *   a METHOD_NAME is defined with is a string
 *   a goto label called beach
 *   the return value is called ret
 */

#define CHECK_METHOD_NAME(self)                                        \
    if (!PyObject_HasAttrString(self, METHOD_NAME))                    \
        goto beach;

#define CHECK_OBJECT(object)                                           \
      if (object->instance == NULL)                                       \
      {                                                                   \
          g_object_unref (object);                                       \
          goto beach;                                                       \
      }                                                                   \

#define CONVERT_LIST(py_files, files)                                  \
    {                                                                  \
        GList *l;                                                      \
        py_files = PyList_New(0);                                      \
        for (l = files; l; l = l->next)                                \
        {                                                              \
            PyObject *item = pygobject_new ((GObject *)l->data);       \
            PyList_Append(py_files, item);                             \
            Py_DECREF (item);                                          \
        }                                                              \
    }

#define HANDLE_RETVAL(py_ret)                                          \
    if (!py_ret)                                                       \
    {                                                                  \
        PyErr_Print();                                                 \
        goto beach;                                                    \
    }                                                                  \
    else if (py_ret == Py_None)                                        \
    {                                                                  \
        goto beach;                                                    \
    }

#define HANDLE_LIST(py_ret, type, type_name)                           \
    {                                                                  \
        Py_ssize_t i = 0;                                              \
        if (!PySequence_Check(py_ret) || PyUnicode_Check(py_ret))      \
        {                                                              \
            PyErr_SetString(PyExc_TypeError,                           \
                            METHOD_NAME " must return a sequence");    \
            goto beach;                                                \
        }                                                              \
        for (i = 0; i < PySequence_Size (py_ret); i++)                 \
        {                                                              \
            PyGObject *py_item;                                        \
            py_item = (PyGObject*)PySequence_GetItem (py_ret, i);      \
            if (!pygobject_check(py_item, &Py##type##_Type))           \
            {                                                          \
                PyErr_SetString(PyExc_TypeError,                       \
                                METHOD_NAME                            \
                                " must return a sequence of "          \
                                type_name);                            \
                goto beach;                                            \
            }                                                          \
            ret = g_list_append (ret, (type*) g_object_ref(py_item->obj));  \
            Py_DECREF(py_item);                                        \
        }                                                              \
    }


static void
free_pygobject_data(gpointer data, gpointer user_data) {
    /* Some NautilusFileInfo objects are cached and not freed until nautilus
        itself is closed.  Since PyGObject stores data that must be freed by
        the Python interpreter, we must always free it before the interpreter
        is finalized. */
    g_object_set_data((GObject *)data, "PyGObject::instance-data", NULL);
}

static void
free_pygobject_data_list(GList *list) {
    if (list == NULL)
        return;
        
    g_list_foreach(list, (GFunc)free_pygobject_data, NULL);
}

static PyObject *
nautilus_python_boxed_new (PyTypeObject *type, gpointer boxed, gboolean free_on_dealloc) {
    PyGBoxed *self = (PyGBoxed *) type->tp_alloc (type, 0);
    self->gtype = pyg_type_from_object ( (PyObject *) type);
    self->boxed = boxed;
    self->free_on_dealloc = free_on_dealloc;
    
    return (PyObject *) self;
}

#define METHOD_NAME "get_models"
static GList *
nautilus_python_object_get_models (NautilusPropertiesModelProvider *provider,
                                   GList                           *files) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    PyObject *py_files, *py_ret = NULL;
    GList *ret = NULL;
    PyGILState_STATE state = pyg_gil_state_ensure();

    debug_enter();

    CHECK_OBJECT(object);
    CHECK_METHOD_NAME(object->instance);

    CONVERT_LIST(py_files, files);

    py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX METHOD_NAME,
                                 "(N)", py_files);
    HANDLE_RETVAL(py_ret);

    HANDLE_LIST(py_ret, NautilusPropertiesModel, "Nautilus.PropertiesModel");

beach:
    free_pygobject_data_list(files);
    Py_XDECREF(py_ret);
    pyg_gil_state_release(state);
    return ret;
}
#undef METHOD_NAME

static void
nautilus_python_object_properties_model_provider_interface_init (NautilusPropertiesModelProviderInterface *interface) {
    interface->get_models = nautilus_python_object_get_models;
}

#define METHOD_NAME "get_file_items"
static GList *
nautilus_python_object_get_file_items (NautilusMenuProvider *provider,
                                       GList                 *files) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    GList *ret = NULL;
    PyObject *py_ret = NULL, *py_files;
    PyGILState_STATE state = pyg_gil_state_ensure();
    
    debug_enter();

    CHECK_OBJECT(object);    

    if (PyObject_HasAttrString(object->instance, "get_file_items_full")) {
        CONVERT_LIST(py_files, files);
        py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX "get_file_items_full",
                                     "(NN)",
                                     pygobject_new((GObject *)provider), 
                                     py_files);
    }
    else if (PyObject_HasAttrString(object->instance, "get_file_items")) {
        CONVERT_LIST(py_files, files);
        py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX METHOD_NAME,
                                     "(N)",
                                     py_files);
    }
    else {
        goto beach;
    }

    HANDLE_RETVAL(py_ret);

    HANDLE_LIST(py_ret, NautilusMenuItem, "Nautilus.MenuItem");

beach:
	free_pygobject_data_list(files);
    Py_XDECREF(py_ret);
    pyg_gil_state_release(state);
    return ret;
}
#undef METHOD_NAME

#define METHOD_NAME "get_background_items"
static GList *
nautilus_python_object_get_background_items (NautilusMenuProvider *provider,
                                             NautilusFileInfo       *file) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    GList *ret = NULL;
    PyObject *py_ret = NULL;
    PyGILState_STATE state = pyg_gil_state_ensure();
    
    debug_enter();

    CHECK_OBJECT(object);

    if (PyObject_HasAttrString(object->instance, "get_background_items_full")) {
        py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX "get_background_items_full",
                                     "(NN)",
                                     pygobject_new((GObject *)provider),
                                     pygobject_new((GObject *)file));
    }
    else if (PyObject_HasAttrString(object->instance, "get_background_items")) {
        py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX METHOD_NAME,
                                     "(N)",
                                     pygobject_new((GObject *)file));
    }
    else {
        goto beach;
    }

    HANDLE_RETVAL(py_ret);

    HANDLE_LIST(py_ret, NautilusMenuItem, "Nautilus.MenuItem");
    
beach:
   free_pygobject_data(file, NULL);
    Py_XDECREF(py_ret);
    pyg_gil_state_release(state);
    return ret;
}
#undef METHOD_NAME

static void
nautilus_python_object_menu_provider_interface_init (NautilusMenuProviderInterface *interface) {
    interface->get_background_items = nautilus_python_object_get_background_items;
    interface->get_file_items = nautilus_python_object_get_file_items;
}

#define METHOD_NAME "get_columns"
static GList *
nautilus_python_object_get_columns (NautilusColumnProvider *provider) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    GList *ret = NULL;
    PyObject *py_ret = NULL;
    PyGILState_STATE state = pyg_gil_state_ensure();                                    \

    debug_enter();
        
    CHECK_OBJECT(object);
    CHECK_METHOD_NAME(object->instance);

    py_ret = PyObject_CallMethod(object->instance, METHOD_PREFIX METHOD_NAME,
                                 NULL);

    HANDLE_RETVAL(py_ret);

    HANDLE_LIST(py_ret, NautilusColumn, "Nautilus.Column");
    
beach:
    if (py_ret != NULL)
        Py_XDECREF(py_ret);
    pyg_gil_state_release(state);
    return ret;
}
#undef METHOD_NAME

static void
nautilus_python_object_column_provider_interface_init (NautilusColumnProviderInterface *interface) {
    interface->get_columns = nautilus_python_object_get_columns;
}


#define METHOD_NAME "cancel_update"
static void
nautilus_python_object_cancel_update (NautilusInfoProvider         *provider,
                                      NautilusOperationHandle     *handle) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    PyGILState_STATE state = pyg_gil_state_ensure();
    PyObject *py_handle = nautilus_python_boxed_new (_PyNautilusOperationHandle_Type, handle, FALSE);

    debug_enter();

    CHECK_OBJECT(object);
    CHECK_METHOD_NAME(object->instance);

    PyObject_CallMethod(object->instance,
                                 METHOD_PREFIX METHOD_NAME, "(NN)",
                                 pygobject_new((GObject*)provider),
                                 py_handle);

beach:
    pyg_gil_state_release(state);
}
#undef METHOD_NAME

#define METHOD_NAME "update_file_info"
static NautilusOperationResult
nautilus_python_object_update_file_info (NautilusInfoProvider         *provider,
                                         NautilusFileInfo             *file,
                                         GClosure                     *update_complete,
                                         NautilusOperationHandle   **handle) {
    NautilusPythonObject *object = (NautilusPythonObject*)provider;
    NautilusOperationResult ret = NAUTILUS_OPERATION_COMPLETE;
    PyObject *py_ret = NULL;
    PyGILState_STATE state = pyg_gil_state_ensure();
    PyObject *py_handle = nautilus_python_boxed_new (_PyNautilusOperationHandle_Type, *handle, FALSE);

    debug_enter();

    CHECK_OBJECT(object);

    if (PyObject_HasAttrString(object->instance, "update_file_info_full")) {
        py_ret = PyObject_CallMethod(object->instance,
                                     METHOD_PREFIX "update_file_info_full", "(NNNN)",
                                     pygobject_new((GObject*)provider),
                                     py_handle,
                                     pyg_boxed_new(G_TYPE_CLOSURE, update_complete, TRUE, TRUE),
                                     pygobject_new((GObject*)file));
    }
    else if (PyObject_HasAttrString(object->instance, "update_file_info")) {
        py_ret = PyObject_CallMethod(object->instance,
                                     METHOD_PREFIX METHOD_NAME, "(N)",
                                     pygobject_new((GObject*)file));
    }
    else {
        goto beach;
    }
    
    HANDLE_RETVAL(py_ret);

    if (!PyLong_Check(py_ret)) {
        PyErr_SetString(PyExc_TypeError,
                        METHOD_NAME " must return None or a int");
        goto beach;
    }

    ret = PyLong_AsLong(py_ret);

beach:
    free_pygobject_data(file, NULL);
    Py_XDECREF(py_ret);
    pyg_gil_state_release(state);
    return ret;
}
#undef METHOD_NAME

static void
nautilus_python_object_info_provider_interface_init (NautilusInfoProviderInterface *interface) {
    interface->cancel_update = nautilus_python_object_cancel_update;
    interface->update_file_info = nautilus_python_object_update_file_info;
}

static void 
nautilus_python_object_instance_init (NautilusPythonObject *object) {
    NautilusPythonObjectClass *class;
    debug_enter();

    class = (NautilusPythonObjectClass*)(((GTypeInstance*)object)->g_class);

    object->instance = PyObject_CallObject(class->type, NULL);
    if (object->instance == NULL)
        PyErr_Print();
}

static void
nautilus_python_object_finalize (GObject *object) {
    debug_enter();

    if (((NautilusPythonObject *)object)->instance != NULL)
        Py_DECREF(((NautilusPythonObject *)object)->instance);
}

static void
nautilus_python_object_class_init (NautilusPythonObjectClass *class,
                                   gpointer                   class_data) {
    debug_enter();

    parent_class = g_type_class_peek_parent (class);
    
    class->type = (PyObject*)class_data;
    
    G_OBJECT_CLASS (class)->finalize = nautilus_python_object_finalize;
}

GType 
nautilus_python_object_get_type (GTypeModule *module, 
                                 PyObject     *type) {
    PyObject *name_str = NULL;
    g_autofree GTypeInfo *info = NULL;
    g_autofree gchar *type_name = NULL;
    GType gtype;

    static const GInterfaceInfo properties_model_provider_interface_info = {
        (GInterfaceInitFunc) nautilus_python_object_properties_model_provider_interface_init,
        NULL,
        NULL
    };

    static const GInterfaceInfo menu_provider_interface_info = {
        (GInterfaceInitFunc) nautilus_python_object_menu_provider_interface_init,
        NULL,
        NULL
    };

    static const GInterfaceInfo column_provider_interface_info = {
        (GInterfaceInitFunc) nautilus_python_object_column_provider_interface_init,
        NULL,
        NULL
    };

    static const GInterfaceInfo info_provider_interface_info = {
        (GInterfaceInitFunc) nautilus_python_object_info_provider_interface_init,
        NULL,
        NULL
    };

    name_str = PyObject_GetAttrString(type, "__name__");
    debug_enter_args("type=%s", PyUnicode_AsUTF8(name_str));
    info = g_new0 (GTypeInfo, 1);
    
    info->class_size = sizeof (NautilusPythonObjectClass);
    info->class_init = (GClassInitFunc)nautilus_python_object_class_init;
    info->instance_size = sizeof (NautilusPythonObject);
    info->instance_init = (GInstanceInitFunc)nautilus_python_object_instance_init;

    info->class_data = type;
    Py_INCREF(type);

    type_name = g_strdup_printf("%s+NautilusPython", PyUnicode_AsUTF8(name_str));

    Py_XDECREF(name_str);

    gtype = g_type_module_register_type (module, 
                                         G_TYPE_OBJECT,
                                         type_name,
                                         info, 0);

    if (PyObject_IsSubclass(type, (PyObject*)&PyNautilusPropertiesModelProvider_Type)) {
        g_type_module_add_interface (module, gtype,
                                     NAUTILUS_TYPE_PROPERTIES_MODEL_PROVIDER,
                                     &properties_model_provider_interface_info);
    }

    if (PyObject_IsSubclass(type, (PyObject*)&PyNautilusMenuProvider_Type)) {
        g_type_module_add_interface (module, gtype, 
                                     NAUTILUS_TYPE_MENU_PROVIDER,
                                     &menu_provider_interface_info);
    }

    if (PyObject_IsSubclass(type, (PyObject*)&PyNautilusColumnProvider_Type)) {
        g_type_module_add_interface (module, gtype, 
                                     NAUTILUS_TYPE_COLUMN_PROVIDER,
                                     &column_provider_interface_info);
    }
    
    if (PyObject_IsSubclass(type, (PyObject*)&PyNautilusInfoProvider_Type)) {
        g_type_module_add_interface (module, gtype, 
                                     NAUTILUS_TYPE_INFO_PROVIDER,
                                     &info_provider_interface_info);
    }
    
    return gtype;
}
