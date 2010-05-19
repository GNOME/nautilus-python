SUBDIRS = src examples

if ENABLE_DOCS
SUBDIRS += docs
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = nautilus-python.pc

EXTRA_DIST = nautilus-python.pc.in nautilus-python.spec.in nautilus-python.spec

DISTCHECK_CONFIGURE_FLAGS=--enable-gtk-doc
