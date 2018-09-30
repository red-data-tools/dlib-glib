sources = files(
  'frontal-face-detector.cpp',
  'image.cpp',
  'rectangle.cpp',
  'shape-predictor.cpp',
  'full-object-detection.cpp',
  'image-window.cpp',
  'overlay-line.cpp',
  'chip-detail.cpp'
)

headers = files(
  'frontal-face-detector.h',
  'image.h',
  'rectangle.h',
  'shape-predictor.h',
  'full-object-detection.h',
  'image-window.h',
  'overlay-line.h',
  'chip-detail.h'
)

install_headers(headers, subdir: meson.project_name())

dependencies = [
  dependency('gobject-2.0'),
  dependency('dlib-1'),
  dependency('x11')
]
libdlib_glib = library('dlib-glib',
                         sources: sources,
                         install: true,
                         dependencies: dependencies,
                         include_directories: [
                           root_inc,
                         ],
                         version: library_version)

libdlib_glib_dependency = declare_dependency(link_with: libdlib_glib,
                                             include_directories: [
                                               root_inc,
                                             ],
                                             dependencies: dependencies)

gnome.generate_gir(libdlib_glib,
                   sources: sources + headers,
                   namespace: 'Dlib',
                   nsversion: api_version,
                   identifier_prefix: 'GDlib',
                   symbol_prefix: 'gdlib',
                   export_packages: 'dlib-glib',
                   includes: [
                     'GObject-2.0',
                   ],
                   install: true,
                   extra_args: [
                     '--warn-all',
                   ])

pkg = import('pkgconfig')
pkg.generate(filebase: meson.project_name(),
             name: 'Dlib GLib',
             description: 'C API for Dlib based on GLib',
             version: meson.project_version(),
             requires: ['gobject-2.0', 'dlib'],
             libraries: [libdlib_glib])
