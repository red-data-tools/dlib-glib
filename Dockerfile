FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN \
  apt update && \
  apt install -y \
    g++ \
    gcc \
    meson \
    ruby-dev \
    libx11-dev \
    wget \
    cmake

RUN \
  wget http://dlib.net/files/dlib-19.16.tar.bz2 && \
  tar xvf dlib-19.16.tar.bz2 && \
  cd dlib-19.16 && \
  mkdir build && \
  cd build && \
  cmake .. -DBUILD_SHARED_LIBS=ON && \
  cmake --build . && \
  make install

RUN \
  gem install gobject-introspection

RUN \
  useradd --user-group --create-home dlib-glib

COPY . /home/dlib-glib/dlib-glib

USER dlib-glib
WORKDIR /home/dlib-glib/dlib-glib

CMD \
  BUILD_DIR=../dlib-glib.build; \
  meson ${BUILD_DIR} && \
  ninja -C ${BUILD_DIR} && \
  (ninja -C ${BUILD_DIR} test; \
   code=$?; \
   cat ${BUILD_DIR}/meson-logs/testlog.txt; \
   exit $code)
