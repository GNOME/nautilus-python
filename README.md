# nautilus-python

This is an extension for Nautilus that allows further extending it with Python scripts with the help of Nautilus’s GObject API.

Documentation, including an API reference, is available through the [Devhelp app](https://apps.gnome.org/app/org.gnome.Devhelp/), if you have `nautilus-python` package installed, or [on-line](https://gnome.pages.gitlab.gnome.org/nautilus-python/). For sample extensions, check the `examples/` subdirectory in the source distribution. Note that some distros move the documentation into a separate package.

## Requirements

- Nautilus ≥ 43.beta
- Python 3.x
- PyGObject 3

## Running Extensions

Scripts are loaded in the following order:

 1. `$XDG_DATA_HOME/nautilus-python/extensions` (i.e. `~/.local/share/…`)
 2. `nautilus_prefix/share/nautilus-python/extensions` (i.e. `~/Development/…`)
 3. `$XDG_DATA_DIRS/nautilus-python/extensions` (i.e. `/usr/share/…`)

Simply copy your Python scripts into one of those directories and restart Nautilus.

## Issues

It is currently not possible to reload a Python script without restarting Nautilus.

Run Nautilus with the `NAUTILUS_PYTHON_DEBUG=misc` environment variable to print out debug information.

## License

nautilus-python is released under the terms of the GNU General Public License, either version 2.0 or, at your option, any later version.
