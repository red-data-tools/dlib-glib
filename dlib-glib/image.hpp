#pragma once

#include <memory>

#include <dlib-glib/image.h>

GDLIBImage *gdlib_image_new_raw(std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> *dlib_image);
std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> gdlib_image_get_raw(GDLIBImage *image);
