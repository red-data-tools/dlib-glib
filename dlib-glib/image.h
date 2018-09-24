#pragma once

#include <glib-object.h>

#include <dlib-glib/rectangle.h>
#include <dlib-glib/chip-detail.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_IMAGE (gdlib_image_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBImage,
                         gdlib_image,
                         GDLIB,
                         IMAGE,
                         GObject)

struct _GDLIBImageClass
{
  GObjectClass parent_class;
};

GDLIBImage *gdlib_image_new(const gchar *filename);
GDLIBImage *gdlib_image_new_empty(void);
void gdlib_image_save_jpeg(GDLIBImage *image,
                           const gchar *filename);
void gdlib_image_draw_rectangle(GDLIBImage *image,
                                GDLIBRectangle *rectangle,
                                gdouble red,
                                gdouble green,
                                gdouble blue);
GDLIBImage *gdlib_image_gaussian_blur(GDLIBImage *image,
                                      GDLIBImage *blurred_image);
GDLIBImage *gdlib_image_extract_image_chip(GDLIBImage *image,
                                           GDLIBChipDetail *chip_detail);

G_END_DECLS
