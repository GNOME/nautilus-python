## 4.1.0 (2025-10-04)

- Added support for Nautilus 49 (https://gitlab.gnome.org/GNOME/nautilus-python/-/merge_requests/13)
- Removed `MenuItem.icon`, `MenuItem.priority`, `MenuItem.tip` from docs. These were unsupported for a long time and now Nautilus officially deprecated them.

## 4.0.1 (2024-04-19)

- Fixed build failure due to underlinking. (https://gitlab.gnome.org/GNOME/nautilus-python/-/merge_requests/13)
- Fixed build failure with Python 3.13 (Patrick Monnerat)

## 4.0 (2022-09-17)

- Updated migration docs and rewrote overview.

## 4.0.alpha (2022-08-12)

- The extension was ported to Nautilus 43 (https://gitlab.gnome.org/GNOME/nautilus-python/-/merge_requests/11)
  - Notably, this removes any direct access to GTK widgets from the API. **Most scripts will need to be modified.** Please check the migration guide in the docs on how to update your scripts.
- Switched to Meson build system (https://gitlab.gnome.org/GNOME/nautilus-python/-/merge_requests/10)
- Removed support for Python 2
- Fixed build with `-fno-common` (Andreas Henriksson)
- Added missing parent constructor calls to examples
- Decorated the examples with typehints
- Fixed several memory leaks (Michael Webster)

## 1.2.3 (2019-07-17)

- First release from gitlab
- Fixed open-terminal example extension (Maximillian Schambach)
- Fixed invalid DOAP file category (Andre Klapper)
- Fixed bug https://gitlab.gnome.org/GNOME/nautilus-python/-/issues/3, setting `argv[0]` to thunar
- Fixed bug https://gitlab.gnome.org/GNOME/nautilus-python/-/issues/4, allow overriding the build date to enable reproducible builds
- Removed build warnings (Christian Stadelman)
- Fix to work with python 3.8 (stratakis)

## 1.2.2 (2018-01-14)

- Fixed [bug #792427](https://bugzilla.gnome.org/show_bug.cgi?id=792427), Fix folder string comparison to prevent duplicate extension loading

## 1.2.1 (2018-01-08)

- Fixed [bug #792348](https://bugzilla.gnome.org/show_bug.cgi?id=792348), Fix syntax error when building docs using python3

## 1.2.0 (2018-01-02)

- Added capability to compile with python 3 support using PYTHON environment variable
- Fix [#781232](https://bugzilla.gnome.org/show_bug.cgi?id=781232), Improve extension path loading semantics to follow XDG recommendations
- Fix [#791208](https://bugzilla.gnome.org/show_bug.cgi?id=791208), require Nautilus 3.0 before importing extensions to prevent warnings
- Switch to using gtkdoc mkhtml for generating devhelp2 documentation

## 1.1.0 (2011-10-17)

- Added pygobject3 compatibility. Retained pygobject 2.28.x compatibility.
  - Updated extension examples to support pygobject3.
- Fixed [bug #660290](https://bugzilla.gnome.org/show_bug.cgi?id=660290). Updated the FSF address
- Fixed [bug #660288](https://bugzilla.gnome.org/show_bug.cgi?id=660288). Fix autogen warnings with additional macro ACLOCAL_AMFLAGS
- Fixed [bug #660287](https://bugzilla.gnome.org/show_bug.cgi?id=660287). Make the docdir not hard-coded
- Fixed [bug #660286](https://bugzilla.gnome.org/show_bug.cgi?id=660286). Fixes m4 underquoting warning
- Fixed [bug #660283](https://bugzilla.gnome.org/show_bug.cgi?id=660283). Fixes html docs installation issue
- Fixed [bug #653169](https://bugzilla.gnome.org/show_bug.cgi?id=653169). Upated the COPYING file with the most recent GPLv2 license

## 1.0.0 (2011-04-17)

- Use the gobject instrospection dynamic bindings, breaks compatibility for existing extensions.
- For Nautilus3, the `get_toolbar_items` methods have been removed. (Only reporting that change, it isn't up to us). Should still work with Nautilus 2.x annotations.
- No longer look in the old `~/.nautilus/python-extensions` or `/usr/lib/nautilus/extensions2.0/python` folders for extensions. Now look in `~/.local/share/nautilus-python/extensions` or `$XDG_DATA_DIR/nautilus-python/extensions`. Extensions should be arch-independent now.
- General clean up of the repository, removed old .cvsignore files
- Updated the gtk-doc documentation and examples to work with new dynamic bindings.

## 0.7.3 (2011-03-28)

- Use `PyCapsule_Import` for pygobject as well as pygtk
- Fixed bug [#644399](https://bugzilla.gnome.org/show_bug.cgi?id=644399), in the property page example plugin, get the md5sum of the file contents, not the file name
- Removed extraneous `.cvsignore` files
- Fixed the update-file-info-async example plugin

## 0.7.2 (2011-03-04)

- Fix to get the PyCapsule patch to work even if there is no PyCapsule object set up for pygtk.

## 0.7.1 (2011-03-02)

- Fixed AM_CHECK_PYTHON_LIBS usage of test (GNOME [bug #619440](https://bugzilla.gnome.org/show_bug.cgi?id=619440))
- Cleaned up the docs Makefile.am to make it more consistent
- Fix some python3 syntax issues in the python.m4 script
- Add python 2.7 support (GNOME [bug #633171](https://bugzilla.gnome.org/show_bug.cgi?id=633171))

## 0.7.0 (2010-05-21)

- Added methods:
  - `nautilus.InfoProvider.update_file_info_full`
  - `nautilus.InfoProvider.update_complete_invoke`
  - `nautilus.InfoProvider.cancel_update`
  - `nautilus.MenuProvider.get_file_items_full`
  - `nautilus.MenuProvider.get_background_items_full`
  - `nautilus.MenuProvider.get_toolbar_items_full`
  - `nautilus.MenuProvider.emit_items_updated_signal`
- Added complete gtk-doc documentation: tutorial and reference. Enable by adding the `--enable-gtk-doc` argument to `./configure` or `./autogen.sh`
- Updated the `autogen.sh` file so it is not a copied-over obsolete version of gnome-autogen.sh, but a shell that calls the user's installed gnome-autogen.sh.
- Removed obsolete .spec file
- Removed obsolete `examples/documentation.py` file
- Added an example plugin for the LocationWidgetProvider
- Look for python plugins in `$XDG_DATA_DIR/nautilus-python/extensions`. This includes `~/.local/share` and `/usr/share` (or whatever `$XDG_DATA_DIR` is set to)

## 0.6.1 (2010-01-19)

- Look for `libpython2.6.so.1.0` instead of `libpython2.6.so`, the latter is general available from -devel packages only.
- Re-added the missing spec and pc files
- Free pygobject data directly after using file objects. Stops segfaults from occurring when nautilus wants to free pygobject data after `Py_Finalize()` is called.

## 0.6.0 (2010-01-15)

- Remove eel dependency (Vincent Untz)
- Sanitize python search path (Mark Lee)
- Remove gnomevfs dependency and unused code (Daniel Holbach)
- Load python from lib64 in 64 bit multilib distributions (Ted Toth)
- Fix segfault when a plugin doesn't implement the `__init__` method
- Added the `can_write`, `get_mount`, `get_file_type`, `get_location`, and `get_parent_location` methods to the `NautilusFileInfo` object
- Added the `NautilusMenu.get_items` method
- Updated some example plugins
- Bug fix for some `PyThreadState_New` segmentation faults
- Use the nautilus prefix by default for distfiles, rather than /usr
- Require nautilus-2.22 and pygobject-2.16 now that we support GIO

## 0.5.2 (2010-03-01)

- Look for libpython2.6.so.1.0 instead of libpython2.6.so, the latter is general available from -devel packages only.
- Remove eel dependency (Vincent Untz)
- Sanitize python search path (Mark Lee)
- Load python from lib64 in 64 bit multilib distributions (Ted Toth)
- Updated some example plugins
- Added explicit gnome-vfs build dependency
- Removed obsolete .spec file

## 0.5.1 (2008-09-16)

- Add support for location widgets (Tim Cole)

## 0.5.0 (2008-01-11)

- Add support for submenus (Lukáš Lalinský, Sylvain Baubeau, Erik Wien)
- Make it work with nautilus 2.22 (Brian Pepple)
- Initialize gnomevfs explicitly (Scott Tsai)
- Compilable with Python 2.5 (Jonathan Rogers)
- Shutdown Python (Gustavo Carneiro)
- Initialize PyGObject/PyGTK/PyGNOMEVFS on demand (Gustavo Carneiro)

## 0.4.3 (2006-02-15)

- Make debugging messages a run-time option
- Fix bug in loading extensions from system extensions dir
- Fix crash when no extensions were loaded

## 0.4.2 (2006-02-10)

- Make it work again with nautilus ≥ 2.13.4
- Minor bug fixes

## 0.4.1 (2005-09-22)

(missing)

## 0.4.0 (2005-05-30)

First public release
