INCLUDES =						\
	-DG_LOG_DOMAIN=\"Nautilus-Python\"	        \
	-DDATADIR=\"$(datadir)\"			\
	-DLIBDIR=\"$(libdir)\"				\
	-I$(top_srcdir)					\
	-I$(top_builddir)				\
	$(DISABLE_DEPRECATED_CFLAGS)			\
	$(NAUTILUS_CFLAGS)				\
	$(PY_CFLAGS)					\
	$(PYGTK_CFLAGS)

PYTHON_LIBS = 			\
	-l$(PY_LIBS)		\
	$(PY_OTHER_LIBS)	\
	$(PY_EXTRA_LIBS)

nautilus_extensiondir=$(NAUTILUS_LIBDIR)/nautilus/extensions-1.0

nautilus_extension_LTLIBRARIES = libnautilus-python.la

libnautilus_python_la_SOURCES =     	\
	nautilus-python.c		\
	nautilus-python.h		\
	nautilus-python-object.c	\
	nautilus-python-object.h

libnautilus_python_la_LDFLAGS = -module -avoid-version $(PY_LIB_LOC)
libnautilus_python_la_LIBADD  = $(NAUTILUS_LIBS) $(PYTHON_LIBS)

pyexec_LTLIBRARIES = nautilus.la
pyexecdir = $(NAUTILUS_LIBDIR)/nautilus-python

nautilus_la_LDFLAGS = -module -avoid-version -export-symbols-regex initnautilus
nautilus_la_LIBADD = $(NAUTILUS_LIBS)
nautilus_la_SOURCES = nautilusmodule.c
nodist_nautilus_la_SOURCES = nautilus.c
nautilus.c: nautilus.defs nautilus.override
CLEANFILES = nautilus.c
EXTRA_DIST = nautilus.override nautilus.defs pygnomevfs.h

.defs.c:
	(cd $(srcdir)\
         && $(PYGTK_CODEGEN) \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
            --register $(PYGTK_DEFSDIR)/gdk-types.defs \
            --register $(PYGTK_DEFSDIR)/gtk-types.defs \
            --override $*.override \
            --prefix py$* $*.defs) > gen-$*.c \
        && cp gen-$*.c $*.c \
        && rm -f gen-$*.c
