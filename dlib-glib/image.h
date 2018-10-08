#pragma once

#include <glib-object.h>

#include <dlib-glib/rectangle.h>
#include <dlib-glib/chip-detail.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_IMAGE (gdlib_image_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibImage,
                         gdlib_image,
                         GDlib,
                         IMAGE,
                         GObject)

struct _GDlibImageClass
{
  GObjectClass parent_class;
};

GDlibImage *gdlib_image_new(const gchar *filename);
void gdlib_image_save_jpeg(GDlibImage *image,
                           const gchar *filename);
void gdlib_image_draw_rectangle(GDlibImage *image,
                                GDlibRectangle *rectangle,
                                gdouble red,
                                gdouble green,
                                gdouble blue);
GDlibImage *gdlib_image_gaussian_blur(GDlibImage *image);
GDlibImage *gdlib_image_extract_image_chip(GDlibImage *image,
                                           GDlibChipDetail *chip_detail);
GList *gdlib_image_find_candidate_object_locations(GDlibImage *image,
                                                   gint min_size,
                                                   gint max_merging_iterations);

G_END_DECLS
