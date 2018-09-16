#include <memory>

#include <dlib/gui_widgets.h>

#include <dlib-glib/widgets.hpp>
#include <dlib-glib/image.hpp>
#include <dlib-glib/overlay-line.hpp>

G_BEGIN_DECLS

/**
 * SECTION: widgets
 * @title: Widgets class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBWidgets is a widgets class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::image_window> widgets;
} GDLIBWidgetsPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBWidgets, gdlib_widgets, G_TYPE_OBJECT)

#define GDLIB_WIDGETS_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                      \
                               GDLIB_TYPE_WIDGETS,         \
                               GDLIBWidgetsPrivate))

enum {
  PROP_0,
  PROP_WIDGETS
};

static void
gdlib_widgets_finalize(GObject *object)
{
  auto priv = GDLIB_WIDGETS_GET_PRIVATE(object);

  priv->widgets = nullptr;

  G_OBJECT_CLASS(gdlib_widgets_parent_class)->finalize(object);
}

static void
gdlib_widgets_set_property(GObject *object,
                           guint prop_id,
                           const GValue *value,
                           GParamSpec *pspec)
{
  auto priv = GDLIB_WIDGETS_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_WIDGETS:
    priv->widgets =
      *static_cast<std::shared_ptr<dlib::image_window> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_widgets_init(GDLIBWidgets *object)
{
}

static void
gdlib_widgets_class_init(GDLIBWidgetsClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_widgets_finalize;
  gobject_class->set_property = gdlib_widgets_set_property;

  spec = g_param_spec_pointer("widgets",
                              "Widgets",
                              "The raw std::shared_ptr<dlib::image_window> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_WIDGETS, spec);
}

/**
 * gdlib_widgets_new:
 *
 * Returns: A newly created #GDLIBWidgets.
 *
 * Since: 1.0.0
 */
GDLIBWidgets *
gdlib_widgets_new(void)
{
  auto widgets = std::make_shared<dlib::image_window>();
  return gdlib_widgets_new_raw(&widgets);
}

/**
 * gdlib_widgets_clear_overlay:
 * @widgets: A #GDLIBWidgets.
 *
 * Since: 1.0.0
 */
void
gdlib_widgets_clear_overlay(GDLIBWidgets *widgets)
{
  auto dlib_widgets = gdlib_widgets_get_raw(widgets);
  dlib_widgets->clear_overlay();
}

/**
 * gdlib_widgets_set_image:
 * @widgets: A #GDLIBWidgets.
 * @image: A #GDLIBImage.
 *
 * Since: 1.0.0
 */
void
gdlib_widgets_set_image(GDLIBWidgets *widgets,
                        GDLIBImage *image)
{
  auto dlib_widgets = gdlib_widgets_get_raw(widgets);
  auto dlib_image = gdlib_image_get_raw(image);
  dlib_widgets->set_image(*dlib_image);
}

/**
 * gdlib_widgets_add_overlay:
 * @widgets: A #GDLIBWidgets.
 * @overlay_lines: (element-type GDLIBOverlayLine):
 *   The overlay lines in the widgets.
 *
 * Since: 1.0.0
 */
void
gdlib_widgets_add_overlay(GDLIBWidgets *widgets,
                          GList *overlay_lines)
{
  auto dlib_widgets = gdlib_widgets_get_raw(widgets);
  std::vector<dlib::image_window::overlay_line> dlib_overlay_lines;
  for (GList *node = overlay_lines; node; node = node->next) {
    GDLIBOverlayLine *overlay_line = GDLIB_OVERLAY_LINE(node->data);
    dlib_overlay_lines.push_back(*gdlib_overlay_line_get_raw(overlay_line));
  }
  dlib_widgets->add_overlay(dlib_overlay_lines);
}

/**
 * gdlib_widgets_wait_until_closed:
 * @widgets: A #GDLIBWidgets.
 *
 * Since: 1.0.0
 */
void
gdlib_widgets_wait_until_closed(GDLIBWidgets *widgets)
{
  auto dlib_widgets = gdlib_widgets_get_raw(widgets);
  dlib_widgets->wait_until_closed();
}

G_END_DECLS

GDLIBWidgets *
gdlib_widgets_new_raw(std::shared_ptr<dlib::image_window> *dlib_widgets)
{
  auto widgets = g_object_new(GDLIB_TYPE_WIDGETS,
                              "widgets", dlib_widgets,
                              NULL);
  return GDLIB_WIDGETS(widgets);
}

std::shared_ptr<dlib::image_window>
gdlib_widgets_get_raw(GDLIBWidgets *widgets)
{
  auto priv = GDLIB_WIDGETS_GET_PRIVATE(widgets);
  return priv->widgets;
}
