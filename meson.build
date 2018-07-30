project('dlib-glib',
        'c', 'cpp',
        version: '1.0.0',
        license: 'Boost Software License',
        default_options : ['cpp_std=c++11'])

api_version = '1.0'
library_version = '1.0.0'

gnome = import('gnome')
pkgconfig = import('pkgconfig')

root_inc = include_directories('.')

subdir('dlib-glib')

run_test = find_program('test/run-test.sh')
test('unit test', run_test)
