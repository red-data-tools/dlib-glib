#!/bin/sh

test_dir="$(cd $(dirname $0); pwd)"
build_dir="$(cd .; pwd)"

module="dlib-glib"

if [ -f "build.ninja" ]; then
  ninja || exit $?
fi

export LD_LIBRARY_PATH="${build_dir}/${module}:${LD_LIBRARY_PATH}"

export GI_TYPELIB_PATH="${build_dir}/${module}:${GI_TYPELIB_PATH}"

ruby ${test_dir}/test-image.rb "$@"
