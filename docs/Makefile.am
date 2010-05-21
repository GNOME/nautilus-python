BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(VERSION)
FULL_VERSION = $(VERSION)

HTML_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/ref-html-style.xsl
PDF_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/pdf-style.xsl

XMLFILES = 							\
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

HTMLdir = $(datadir)/gtk-doc/html/nautilus-python
HTML_DATA =						\
	html/index.html					\
	html/index.sgml					\
	html/nautilus-python-overview.html \
	html/nautilus-python-overview-example.html \
	html/nautilus-python-overview-methods.html \
	html/nautilus-python-class-reference.html \
	html/nautilus-python-provider-reference.html \
	html/class-nautilus-python-column.html \
	html/class-nautilus-python-column-provider.html \
	html/class-nautilus-python-menu.html  \
	html/class-nautilus-python-menu-item.html  \
	html/class-nautilus-python-menu-provider.html  \
	html/class-nautilus-python-property-page.html  \
	html/class-nautilus-python-property-page-provider.html  \
	html/class-nautilus-python-location-widget-provider.html  \
	html/class-nautilus-python-file-info.html  \
	html/class-nautilus-python-info-provider.html  \
	html/nautilus-python-enum-reference.html \
	html/enum-nautilus-python-operation-result.html  \
	html/nautilus-python.devhelp

CSS_FILES = $(PYGOBJECT_PYGDOCS)/style.css
CSSdir = $(HTMLdir)
CSS_DATA = $(CSS_FILES)

BUILT_SOURCES = 		\
	build_stamp 		\
	reference/builddate.xml	\
	$(HTML_DATA)

CLEANFILES = 			\
	build_stamp 		\
	nautilus-python-ref.*	\
	reference/builddate.xml	\
	$(HTML_DATA)

EXTRA_DIST = 		\
	$(XMLFILES)

REFERENCE_DEPS = 	\
	reference 	\
	$(XMLFILES)

$(HTML_DATA): build_stamp

if ENABLE_GTK_DOC

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c 'import datetime; print datetime.date.today()' > $@

build_stamp: $(REFERENCE_DEPS) reference/builddate.xml
	xsltproc --nonet --xinclude -o $(BUILDDIR)/html/ \
		 --path $(BUILDDIR)/reference:$(srcdir)/reference \
		 --stringparam gtkdoc.bookname "nautilus-python" \
		 --stringparam gtkdoc.version ${REF_VERSION} \
		 $(HTML_STYLE) $(srcdir)/reference/nautilus-python-ref.xml
	$(PYGOBJECT_FIXXREF) -i $(PYGOBJECT_PYGDOCS) $(BUILDDIR)/html 
	touch $@

pdf: $(REFERENCE_DEPS) reference/builddate.xml
	xsltproc --nonet --xinclude -o nautilus-python-ref.fo \
		$(PDF_STYLE) reference/nautilus-python-ref.xml
	pdfxmltex nautilus-python-ref.fo >output </dev/null
endif

