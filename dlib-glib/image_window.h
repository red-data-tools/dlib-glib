#pragma once

#include <glib-object.h>

#include <dlib-glib/image.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_IMAGE_WINDOW (gdlib_image_window_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBImageWindow,
                         gdlib_image_window,
                         GDLIB,
                         IMAGE_WINDOW,
                         GObject)

struct _GDLIBImageWindowClass
{
  GObjectClass parent_class;
};

GDLIBImageWindow *gdlib_image_window_new(void);
void gdlib_image_window_clear_overlay(GDLIBImageWindow *image_window);
void gdlib_image_window_set_image(GDLIBImageWindow *image_window,
                                  GDLIBImage *image);
void gdlib_image_window_add_overlay(GDLIBImageWindow *image_window,
                                    GList *overlay_lines);
void gdlib_image_window_wait_until_closed(GDLIBImageWindow *image_window);

G_END_DECLS
