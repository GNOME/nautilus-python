BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(VERSION)
FULL_VERSION = $(VERSION)

FIXXREF = $(srcdir)/xsl/fixxref.py
HTML_STYLE = $(srcdir)/xsl/ref-html-style.xsl

XML_FILES = 							\
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
HTML_FILES =						\
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
HTML_DATA = $(HTMLFILES)

XSL_FILES =             \
	xsl/common.xsl      \
	xsl/devhelp.xsl     \
	xsl/html.xsl        \
	xsl/pdf-style.xsl   \
	xsl/pdf.xsl         \
	xsl/style.css
XSL_DATA = $(XSL_FILES) $(FIXXREF)
XSLdir = $(BUILDDIR)/xsl

CSS_FILES = xsl/style.css
CSSdir = $(HTMLdir)
CSS_DATA = $(CSS_FILES)

BUILT_SOURCES = 		\
	reference/builddate.xml	\
	$(HTML_FILES)

CLEANFILES = 			\
	nautilus-python-ref.*	\
	reference/builddate.xml	\
	$(HTML_FILES)

EXTRA_DIST = 		\
	$(XML_FILES)     \
	$(XSL_FILES)    \
	$(FIXXREF)      \
	$(HTML_STYLE)

REFERENCE_DEPS = 	\
	reference 	\
	$(XML_FILES)    \
	$(XSL_FILES)    \
	$(FIXXREF)

if ENABLE_GTK_DOC

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c 'import datetime; print datetime.date.today()' > $@

$(HTML_FILES): $(REFERENCE_DEPS)
	xsltproc --nonet --xinclude -o $(BUILDDIR)/html/ \
		 --path $(BUILDDIR)/reference:$(srcdir)/reference \
		 --stringparam gtkdoc.bookname "nautilus-python" \
		 --stringparam gtkdoc.version ${REF_VERSION} \
		 $(HTML_STYLE) $(srcdir)/reference/nautilus-python-ref.xml
	$(FIXXREF) -i xsl $(BUILDDIR)/html 
	touch $@

endif
