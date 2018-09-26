#pragma once

#include <memory>

#include <dlib-glib/full-object-detection.h>

GDlibFullObjectDetection *gdlib_full_object_detection_new_raw(std::shared_ptr<dlib::full_object_detection> *dlib_full_object_detection);
std::shared_ptr<dlib::full_object_detection> gdlib_full_object_detection_get_raw(GDlibFullObjectDetection *full_object_detection);
