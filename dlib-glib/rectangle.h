#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GDlib_TYPE_RECTANGLE (gdlib_rectangle_get_type())
G_DECLARE_DERIVABLE_TYPE(GDlibRectangle,
                         gdlib_rectangle,
                         GDlib,
                         RECTANGLE,
                         GObject)

struct _GDlibRectangleClass
{
  GObjectClass parent_class;
};

GDlibRectangle *gdlib_rectangle_new(glong left,
                                    glong top,
                                    glong right,
                                    glong bottom);
GDlibRectangle *gdlib_rectangle_new_empty(void);
glong gdlib_rectangle_get_left(GDlibRectangle *rectangle);
glong gdlib_rectangle_get_top(GDlibRectangle *rectangle);
glong gdlib_rectangle_get_right(GDlibRectangle *rectangle);
glong gdlib_rectangle_get_bottom(GDlibRectangle *rectangle);
void gdlib_rectangle_set_left(GDlibRectangle *rectangle,
                              glong left);
void gdlib_rectangle_set_top(GDlibRectangle *rectangle,
                             glong top);
void gdlib_rectangle_set_right(GDlibRectangle *rectangle,
                               glong right);
void gdlib_rectangle_set_bottom(GDlibRectangle *rectangle,
                                glong bottom);
gboolean gdlib_rectangle_is_empty(GDlibRectangle *rectangle);

G_END_DECLS
