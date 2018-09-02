#pragma once

#include <glib-object.h>

#include <dlib-glib/full-object-detection.h>
#include <dlib-glib/image.h>
#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_SHAPE_PREDICTOR (gdlib_shape_predictor_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBShapePredictor,
                         gdlib_shape_predictor,
                         GDLIB,
                         SHAPE_PREDICTOR,
                         GObject)

struct _GDLIBShapePredictorClass
{
  GObjectClass parent_class;
};

GDLIBShapePredictor *gdlib_shape_predictor_new(const gchar *predictor);
GDLIBFullObjectDetection *gdlib_shape_predictor_detect(GDLIBShapePredictor *shape_predictor,
                                                       GDLIBImage *image,
                                                       GDLIBRectangle *rectangle);

G_END_DECLS
