#pragma once

#include <memory>

#include <dlib-glib/shape-predictor.h>

GDLIBShapePredictor *gdlib_shape_predictor_new_raw(std::shared_ptr<dlib::shape_predictor> *dlib_shape_predictor);
std::shared_ptr<dlib::shape_predictor> gdlib_shape_predictor_get_raw(GDLIBShapePredictor *shape_predictor);
