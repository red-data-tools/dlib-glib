#pragma once

#include <glib-object.h>

#include <dlib-glib/image.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_WIDGETS (gdlib_widgets_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBWidgets,
                         gdlib_widgets,
                         GDLIB,
                         WIDGETS,
                         GObject)

struct _GDLIBWidgetsClass
{
  GObjectClass parent_class;
};

GDLIBWidgets *gdlib_widgets_new(void);
void gdlib_widgets_clear_overlay(GDLIBWidgets *widgets);
void gdlib_widgets_set_image(GDLIBWidgets *widgets,
                             GDLIBImage *image);
void gdlib_widgets_add_overlay(GDLIBWidgets *widgets,
                               GList *overlay_lines);
void gdlib_widgets_wait_until_closed(GDLIBWidgets *widgets);

G_END_DECLS
