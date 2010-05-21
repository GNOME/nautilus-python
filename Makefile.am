SUBDIRS = src examples

if ENABLE_GTK_DOC
SUBDIRS += docs
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = nautilus-python.pc

EXTRA_DIST = nautilus-python.pc.in

DISTCHECK_CONFIGURE_FLAGS=--enable-gtk-doc
