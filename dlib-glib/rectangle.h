#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_RECTANGLE (gdlib_rectangle_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBRectangle,
                         gdlib_rectangle,
                         GDLIB,
                         RECTANGLE,
                         GObject)

struct _GDLIBRectangleClass
{
  GObjectClass parent_class;
};

GDLIBRectangle *gdlib_rectangle_new(glong left, glong top, glong right, glong bottom);
GDLIBRectangle *gdlib_rectangle_new_empty(void);
glong gdlib_rectangle_get_left(GDLIBRectangle *rectangle);
glong gdlib_rectangle_get_top(GDLIBRectangle *rectangle);
glong gdlib_rectangle_get_right(GDLIBRectangle *rectangle);
glong gdlib_rectangle_get_bottom(GDLIBRectangle *rectangle);
void gdlib_rectangle_set_left(GDLIBRectangle *rectangle, glong left);
void gdlib_rectangle_set_top(GDLIBRectangle *rectangle, glong top);
void gdlib_rectangle_set_right(GDLIBRectangle *rectangle, glong right);
void gdlib_rectangle_set_bottom(GDLIBRectangle *rectangle, glong bottom);

G_END_DECLS
