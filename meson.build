project(
  'nautilus-python',
  'c',
  version: '4.1.0',
  meson_version: '>= 0.59.0',
)

gnome = import('gnome', required: get_option('docs'))
pkg = import('pkgconfig')
python = import('python')

prefix = get_option('prefix')
libdir = get_option('libdir')
# Needs to be absolute for C constant.
datadir = prefix / get_option('datadir')
docdir = datadir / 'doc' / meson.project_name()

python3 = python.find_installation('python3')
pygobject_major_version = 3
pygobject_minor_version = 0
pygobject_micro_version = 0
pygobject = dependency('pygobject-3.0', version: f'>= @pygobject_major_version@.@pygobject_minor_version@.@pygobject_micro_version@')
libnautilus_extension = dependency('libnautilus-extension-4', version: '>= 43.beta')
if libnautilus_extension.version().version_compare('>= 49')
  add_project_arguments('-DNAUTILUS_4_1_API', language: 'c')
endif
gmodule = dependency('gmodule-2.0', version: '>= 2.44')
python_dep = python3.dependency(embed: true)

nautilus_extension_dir = libnautilus_extension.get_variable('extensiondir', pkgconfig_define: ['libdir', libdir])

py_so_filename = python3.get_variable('INSTSONAME')
python_libpath = python3.get_variable('LIBDIR') / py_so_filename

conf = configuration_data()
conf.set_quoted('DATADIR', datadir)
conf.set('PYGOBJECT_MAJOR_VERSION', pygobject_major_version)
conf.set('PYGOBJECT_MINOR_VERSION', pygobject_minor_version)
conf.set('PYGOBJECT_MICRO_VERSION', pygobject_micro_version)
conf.set_quoted('PYTHON_LIBPATH', python_libpath)

configure_file(
  output: 'config.h',
  configuration: conf,
)

root_incdir = include_directories('.')

if get_option('docs').enabled()
  subdir('docs/reference')
endif
subdir('examples')
subdir('src')

pkg.generate(
  name: 'nautilus-python',
  description: 'Nautilus-Python Components',
  variables: [
    # TODO: Remove when bumping minimum Meson version to 0.62
    # https://mesonbuild.com/Release-notes-for-0-62-0.html#pkgconfiggenerate-will-now-include-variables-for-builtin-directories-when-referenced
    f'prefix=@prefix@',
    'datadir=${prefix}/share',
    'pythondir=${datadir}/nautilus-python/extensions',
  ],
  dataonly: true,
)

summary({
  'PyGObject Version': 'pygobject-3.0',
  'Python Library': python_libpath,
  'Documentation': get_option('docs'),
})
