#pragma once

#include <glib-object.h>

#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_FULL_OBJECT_DETECTION (gdlib_full_object_detection_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBFullObjectDetection,
                         gdlib_full_object_detection,
                         GDLIB,
                         FULL_OBJECT_DETECTION,
                         GObject)

struct _GDLIBFullObjectDetectionClass
{
  GObjectClass parent_class;
};

GDLIBFullObjectDetection *gdlib_full_object_detection_new(GDLIBRectangle *rectangle);
GDLIBRectangle *gdlib_full_object_detection_rectangle(GDLIBFullObjectDetection *full_object_detection);
gulong gdlib_full_object_detection_get_n_parts(GDLIBFullObjectDetection *full_object_detection);

G_END_DECLS
