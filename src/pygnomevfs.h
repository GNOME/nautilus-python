/*
 *  nautilus-python.c - Nautilus Python extension
 * 
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
 */

#ifndef PYGNOME_VFS_H
#define PYGNOME_VFS_H

#include <Python.h>

#include <libgnomevfs/gnome-vfs-init.h>
#include <libgnomevfs/gnome-vfs-uri.h>
#include <libgnomevfs/gnome-vfs-file-info.h>
#include <libgnomevfs/gnome-vfs-directory.h>
#include <libgnomevfs/gnome-vfs-ops.h>
#include <libgnomevfs/gnome-vfs-mime-handlers.h>
#include <libgnomevfs/gnome-vfs-mime-utils.h>
#include <libgnomevfs/gnome-vfs-result.h>
#include <libgnomevfs/gnome-vfs-context.h>
#include <libgnomevfs/gnome-vfs-xfer.h>

typedef struct {
    PyObject_HEAD
    GnomeVFSURI *uri;
} PyGnomeVFSURI;

typedef struct {
    PyObject_HEAD
    GnomeVFSFileInfo *finfo;
} PyGnomeVFSFileInfo;

typedef struct {
    PyObject_HEAD
    GnomeVFSContext *context;
} PyGnomeVFSContext;
    
#define pygnome_vfs_uri_get(v) (((PyGnomeVFSURI *)(v))->uri)
#define pygnome_vfs_uri_check(v) ((v)->ob_type == _PyGnomeVFS_API->uri_type)

#define pygnome_vfs_file_info_get(v) (((PyGnomeVFSFileInfo *)(v))->finfo)
#define pygnome_vfs_file_info_check(v) ((v)->ob_type == _PyGnomeVFS_API->file_info_type)

#define pygnome_vfs_context_get(v) (((PyGnomeVFSURI *)(v))->context)
#define pygnome_vfs_context_check(v) ((v)->ob_type == _PyGnomeVFS_API->context_type)

struct _PyGnomeVFS_Functions {
    GnomeVFSResult (* exception_check)(void);
    PyObject *(* uri_new)(GnomeVFSURI *uri);
    PyTypeObject *uri_type;
    PyObject *(* file_info_new)(GnomeVFSFileInfo *finfo);
    PyTypeObject *file_info_type;
    PyObject *(* context_new)(GnomeVFSContext *context);
    PyTypeObject *context_type;
};

#if defined(NO_IMPORT) || defined(NO_IMPORT_PYGNOMEVFS)
extern struct _PyGnomeVFS_Functions *_PyGnomeVFS_API;
#else
struct _PyGnomeVFS_Functions *_PyGnomeVFS_API;
#endif

#define pygnome_vfs_exception_check (_PyGnomeVFS_API->exception_check)
#define pygnome_vfs_uri_new         (_PyGnomeVFS_API->uri_new)
#define PyGnomeVFSURI_Type          (*_PyGnomeVFS_API->uri_type)
#define pygnome_vfs_file_info_new   (_PyGnomeVFS_API->file_info_new)
#define PyGnomeVFSFileInfo_Type     (*_PyGnomeVFS_API->file_info_type)
#define pygnome_vfs_context_new     (_PyGnomeVFS_API->context_new)
#define PyGnomeVFSContext_Type      (*_PyGnomeVFS_API->context_type)

#define np_init_pygnomevfs() { \
    PyObject *gobject = PyImport_ImportModule("gnomevfs"); \
    if (gobject != NULL) { \
        PyObject *mdict = PyModule_GetDict(gobject); \
        PyObject *cobject = PyDict_GetItemString(mdict, "_PyGnomeVFS_API"); \
        if (PyCObject_Check(cobject)) \
            _PyGnomeVFS_API = (struct _PyGnomeVFS_Functions *)PyCObject_AsVoidPtr(cobject); \
        else { \
	    Py_FatalError("could not find _PyGnomeVFS_API object"); \
	    return FALSE; \
        } \
    } else { \
        Py_FatalError("could not import gnomevfs"); \
        return FALSE; \
    } \
}

#endif /* PYGNOME_VFS_H */
