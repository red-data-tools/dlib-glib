#pragma once

#include <glib-object.h>
#include <dlib-glib/image.h>
#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDlib_TYPE_DETECTOR (gdlib_detector_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibDetector,
                         gdlib_detector,
                         GDlib,
                         DETECTOR,
                         GObject)

struct _GDlibDetectorClass
{
  GObjectClass parent_class;
};

GDlibDetector *gdlib_detector_new(void);
GList *gdlib_detector_detect(GDlibDetector *detector,
                             GDlibImage *image);

G_END_DECLS
