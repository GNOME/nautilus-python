configure_file(
  input: 'entities.docbook.in',
  output: 'entities.docbook',
  configuration: {
    'VERSION': meson.project_version(),
  },
)

gnome.gtkdoc(
  'nautilus-python',
  main_xml: 'nautilus-python-ref.xml',
  src_dir: 'src',
  install: true,
)
