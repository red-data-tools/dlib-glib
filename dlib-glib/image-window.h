#pragma once

#include <glib-object.h>

#include <dlib-glib/image.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_IMAGE_WINDOW (gdlib_image_window_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibImageWindow,
                         gdlib_image_window,
                         GDlib,
                         IMAGE_WINDOW,
                         GObject)

struct _GDlibImageWindowClass
{
  GObjectClass parent_class;
};

GDlibImageWindow *gdlib_image_window_new(void);
void gdlib_image_window_clear_overlay(GDlibImageWindow *image_window);
void gdlib_image_window_set_image(GDlibImageWindow *image_window,
                                  GDlibImage *image);
void gdlib_image_window_add_overlay(GDlibImageWindow *image_window,
                                    GList *overlay_lines);
void gdlib_image_window_wait_until_closed(GDlibImageWindow *image_window);
void gdlib_image_window_set_face_chip_details(GDlibImageWindow *image_window,
                                              GDlibImage *image,
                                              GList *chip_details);

G_END_DECLS
