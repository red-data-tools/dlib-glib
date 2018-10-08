#pragma once

#include <glib-object.h>

#include <dlib-glib/chip-detail.h>
#include <dlib-glib/full-object-detection.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_CHIP_DETAIL (gdlib_chip_detail_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibChipDetail,
                         gdlib_chip_detail,
                         GDlib,
                         CHIP_DETAIL,
                         GObject)

struct _GDlibChipDetailClass
{
  GObjectClass parent_class;
};

GDlibChipDetail *gdlib_chip_detail_new(void);
GList *gdlib_chip_detail_get_face_chip_details(GList *full_object_detections);

G_END_DECLS
