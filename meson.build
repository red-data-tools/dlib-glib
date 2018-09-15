project('dlib-glib',
        'c', 'cpp',
        version: '1.0.0',
        license: 'Boost Software License',
        default_options : ['cpp_std=c++11'])

api_version = '1.0'
library_version = '1.0.0'

prefix = get_option('prefix')
include_dir = join_paths(prefix, get_option('includedir'))
data_dir = join_paths(prefix, get_option('datadir'))

gnome = import('gnome')
pkgconfig = import('pkgconfig')

root_inc = include_directories('.')

subdir('dlib-glib')

if get_option('gtk_doc')
  subdir('doc/reference')
endif

run_test = find_program('test/run-test.sh')
test('unit test', run_test)
