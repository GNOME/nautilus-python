INCLUDES =						\
	-DG_LOG_DOMAIN=\"Nautilus-Python\"	        \
	-DDATADIR=\"$(datadir)\"			\
	-DLIBDIR=\"$(libdir)\"				\
	-I$(top_srcdir)					\
	-I$(top_builddir)				\
	$(DISABLE_DEPRECATED_CFLAGS)			\
	$(NAUTILUS_PYTHON_CFLAGS)			\
	-DPYTHON_VERSION=\"$(PYTHON_VERSION)\"		\
	-DPY_LIB_LOC="\"$(PYTHON_LIB_LOC)\""		\
	$(PYTHON_INCLUDES)

nautilus_extensiondir=$(NAUTILUS_EXTENSION_DIR)

nautilus_extension_LTLIBRARIES = libnautilus-python.la

libnautilus_python_la_SOURCES =     	\
	nautilus-python.c		\
	nautilus-python.h		\
	nautilus-python-object.c	\
	nautilus-python-object.h

libnautilus_python_la_LDFLAGS = -module -avoid-version
libnautilus_python_la_LIBADD  = $(NAUTILUS_PYTHON_LIBS) $(PYTHON_LIBS)
