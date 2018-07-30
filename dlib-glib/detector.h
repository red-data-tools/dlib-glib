#pragma once

#include <glib-object.h>
#include <dlib-glib/image.h>
#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_DETECTOR (gdlib_detector_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBDetector,
                         gdlib_detector,
                         GDLIB,
                         DETECTOR,
                         GObject)

struct _GDLIBDetectorClass
{
  GObjectClass parent_class;
};

GDLIBDetector *gdlib_detector_new(void);
GList *gdlib_detector_detect(GDLIBDetector *detector,
                             GDLIBImage *image);

G_END_DECLS
