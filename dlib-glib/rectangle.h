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

GDLIBRectangle *gdlib_rectangle_new(void);

G_END_DECLS
