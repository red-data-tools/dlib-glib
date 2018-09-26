#pragma once

#include <glib-object.h>

#include <dlib-glib/full-object-detection.h>
#include <dlib-glib/image.h>
#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDlib_TYPE_SHAPE_PREDICTOR (gdlib_shape_predictor_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibShapePredictor,
                         gdlib_shape_predictor,
                         GDlib,
                         SHAPE_PREDICTOR,
                         GObject)

struct _GDlibShapePredictorClass
{
  GObjectClass parent_class;
};

GDlibShapePredictor *gdlib_shape_predictor_new(const gchar *predictor);
GDlibFullObjectDetection *gdlib_shape_predictor_detect(GDlibShapePredictor *shape_predictor,
                                                       GDlibImage *image,
                                                       GDlibRectangle *rectangle);

G_END_DECLS
