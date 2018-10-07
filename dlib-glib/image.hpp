#pragma once

#include <memory>

#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include <dlib-glib/image.h>

GDlibImage *gdlib_image_new_raw(std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> *dlib_image);
std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> gdlib_image_get_raw(GDlibImage *image);
