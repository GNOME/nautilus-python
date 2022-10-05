nautilus_python = shared_module(
  'nautilus-python',
  sources: [
    'nautilus-python.c',
    'nautilus-python-object.c',
  ],
  dependencies: [
    libnautilus_extension,
    pygobject,
    gmodule,
    python_dep,
  ],
  include_directories: [
    root_incdir,
  ],
  install: true,
  install_dir: nautilus_extension_dir,
)
