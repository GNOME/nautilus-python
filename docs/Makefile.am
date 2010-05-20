BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(VERSION)
FULL_VERSION = $(VERSION)

HTML_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/ref-html-style.xsl
PDF_STYLE = $(PYGOBJECT_DATADIR)/pygobject/xsl/pdf-style.xsl

XMLFILES = 							\
	reference/nautilus-python-ref.xml			\
	reference/nautilus-python-column.xml   \
	reference/nautilus-python-column-provider.xml   \
	reference/nautilus-python-menu.xml  \
	reference/nautilus-python-menu-item.xml \
	reference/nautilus-python-menu-provider.xml \
	reference/nautilus-python-property-page.xml 

HTMLdir = $(datadir)/gtk-doc/html/nautilus-python
HTML_DATA =						\
	html/index.html					\
	html/index.sgml					\
	html/class-nautilus-python-column.html \
	html/class-nautilus-python-column-provider.html \
	html/class-nautilus-python-menu.html  \
	html/class-nautilus-python-menu-item.html  \
	html/class-nautilus-python-menu-provider.html  \
	html/class-nautilus-python-property-page.html  \
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

if ENABLE_DOCS

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

