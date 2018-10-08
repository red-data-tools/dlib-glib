#pragma once

#include <glib-object.h>

#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_FULL_OBJECT_DETECTION (gdlib_full_object_detection_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibFullObjectDetection,
                         gdlib_full_object_detection,
                         GDlib,
                         FULL_OBJECT_DETECTION,
                         GObject)

struct _GDlibFullObjectDetectionClass
{
  GObjectClass parent_class;
};

GDlibFullObjectDetection *gdlib_full_object_detection_new(GDlibRectangle *rectangle);
GDlibRectangle *gdlib_full_object_detection_get_rectangle(GDlibFullObjectDetection *full_object_detection);
gulong gdlib_full_object_detection_get_n_parts(GDlibFullObjectDetection *full_object_detection);

G_END_DECLS
