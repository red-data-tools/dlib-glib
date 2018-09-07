#pragma once

#include <glib-object.h>

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

G_END_DECLS
