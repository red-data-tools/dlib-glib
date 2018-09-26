#pragma once

#include <memory>

#include <dlib-glib/detector.h>

GDlibDetector *gdlib_detector_new_raw(dlib::frontal_face_detector *dlib_detector);
dlib::frontal_face_detector *gdlib_detector_get_raw(GDlibDetector *detector);
