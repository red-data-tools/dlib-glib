#pragma once

#include <glib-object.h>
#include <dlib-glib/image.h>
#include <dlib-glib/rectangle.h>

G_BEGIN_DECLS

#define GDlib_TYPE_FRONTAL_FACE_DETECTOR (gdlib_frontal_face_detector_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibFrontalFaceDetector,
                         gdlib_frontal_face_detector,
                         GDlib,
                         FRONTAL_FACE_DETECTOR,
                         GObject)

struct _GDlibFrontalFaceDetectorClass
{
  GObjectClass parent_class;
};

GDlibFrontalFaceDetector *gdlib_frontal_face_detector_new(void);
GList *gdlib_frontal_face_detector_detect(GDlibFrontalFaceDetector *frontal_face_detector,
                                          GDlibImage *image);

G_END_DECLS
