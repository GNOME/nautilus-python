EXTRA_DIST = documentation.py README.in

docsdir = $(datadir)/doc/$(PACKAGE)
docs_DATA = documentation.py README

examplesdir = $(datadir)/doc/$(PACKAGE)/examples
examples_DATA =					\
	background-image.py			\
	block-size-column.py			\
	open-terminal.py			\
	md5sum-property-page.py

README: README.in
	sed -e s!\@NAUTILUS_LIBDIR\@!@NAUTILUS_LIBDIR@! < $< > $@
README: Makefile

