docsdir = $(docdir)

BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(VERSION)
FULL_VERSION = $(VERSION)

XMLdir = $(docsdir)/reference
XML_DATA = 							\
	reference/nautilus-python-ref.xml			\
	reference/nautilus-python-overview.xml			\
	reference/nautilus-python-overview-example.xml			\
	reference/nautilus-python-overview-methods.xml			\
	reference/nautilus-python-class-reference.xml			\
	reference/nautilus-python-provider-reference.xml			\
	reference/nautilus-python-column.xml   \
	reference/nautilus-python-column-provider.xml   \
	reference/nautilus-python-menu.xml  \
	reference/nautilus-python-menu-item.xml \
	reference/nautilus-python-menu-provider.xml \
	reference/nautilus-python-property-page.xml \
	reference/nautilus-python-property-page-provider.xml \
	reference/nautilus-python-location-widget-provider.xml \
	reference/nautilus-python-file-info.xml \
	reference/nautilus-python-info-provider.xml \
	reference/nautilus-python-enum-reference.xml \
	reference/nautilus-python-operation-result.xml

HTMLdir = $(HTML_DIR)/nautilus-python
HTML_DATA =						\
	index.html					\
	index.sgml					\
	nautilus-python-overview.html \
	nautilus-python-overview-example.html \
	nautilus-python-overview-methods.html \
	nautilus-python-class-reference.html \
	nautilus-python-provider-reference.html \
	class-nautilus-python-column.html \
	class-nautilus-python-column-provider.html \
	class-nautilus-python-menu.html  \
	class-nautilus-python-menu-item.html  \
	class-nautilus-python-menu-provider.html  \
	class-nautilus-python-property-page.html  \
	class-nautilus-python-property-page-provider.html  \
	class-nautilus-python-location-widget-provider.html  \
	class-nautilus-python-file-info.html  \
	class-nautilus-python-info-provider.html  \
	nautilus-python-enum-reference.html \
	enum-nautilus-python-operation-result.html  \
	nautilus-python.devhelp2 \
	up.png up-insensitive.png \
	right.png right-insensitive.png \
	left.png left-insensitive.png home.png \
	style.css

BUILT_SOURCES = 		\
	reference/builddate.xml	\
	$(HTML_DATA) \
	$(XML_DATA)

CLEANFILES = 			\
	nautilus-python-ref.*	\
	reference/builddate.xml	\
	$(HTML_DATA)

EXTRA_DIST = 		\
	$(XML_DATA)     \
	$(HTML_DATA)

REFERENCE_DEPS = 	\
	reference 	\
	$(XML_DATA) 

if ENABLE_GTK_DOC

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c "import datetime; import os; import time; print(datetime.datetime.utcfromtimestamp(int(os.environ.get('SOURCE_DATE_EPOCH', time.time()))).date())" > $@

$(HTML_DATA): $(REFERENCE_DEPS) reference/builddate.xml
	$(GTKDOC_MKHTML) \
		nautilus-python $(srcdir)/reference/nautilus-python-ref.xml \
		--path $(BUILDDIR)/reference:$(srcdir)/reference
	touch $@
	
endif
