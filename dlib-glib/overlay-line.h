#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GDLIB_TYPE_OVERLAY_LINE (gdlib_overlay_line_get_type())
G_DECLARE_DERIVABLE_TYPE(GDLIBOverlayLine,
                         gdlib_overlay_line,
                         GDLIB,
                         OVERLAY_LINE,
                         GObject)

struct _GDLIBOverlayLineClass
{
  GObjectClass parent_class;
};

GDLIBOverlayLine *gdlib_overlay_line_new(void);

G_END_DECLS
