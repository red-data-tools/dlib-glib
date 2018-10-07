#pragma once

#include <memory>

#include <dlib/image_processing/frontal_face_detector.h>

#include <dlib-glib/frontal-face-detector.h>

GDlibFrontalFaceDetector *gdlib_frontal_face_detector_new_raw(std::shared_ptr<dlib::frontal_face_detector> *dlib_frontal_face_detector);
std::shared_ptr<dlib::frontal_face_detector> gdlib_frontal_face_detector_get_raw(GDlibFrontalFaceDetector *frontal_face_detector);
