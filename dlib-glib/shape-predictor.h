#pragma once

#include <glib-object.h>

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

GDLIBShapePredictor *gdlib_shape_predictor_new(void);

G_END_DECLS
