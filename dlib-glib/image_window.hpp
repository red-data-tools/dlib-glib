#pragma once

#include <memory>

#include <dlib-glib/image_window.h>

GDLIBImageWindow *gdlib_image_window_new_raw(std::shared_ptr<dlib::image_window> *image_window);
std::shared_ptr<dlib::image_window> gdlib_image_window_get_raw(GDLIBImageWindow *image_window);
