#pragma once

#include <memory>

#include <dlib/geometry/rectangle.h>

#include <dlib-glib/rectangle.h>

GDlibRectangle *gdlib_rectangle_new_raw(std::shared_ptr<dlib::rectangle> *dlib_rectangle);
std::shared_ptr<dlib::rectangle> gdlib_rectangle_get_raw(GDlibRectangle *rectangle);
