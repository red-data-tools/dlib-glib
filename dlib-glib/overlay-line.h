#pragma once

#include <glib-object.h>

#include <dlib-glib/full-object-detection.h>

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
GList *gdlib_overlay_line_render_face_detections(GList *full_object_detections);

G_END_DECLS
