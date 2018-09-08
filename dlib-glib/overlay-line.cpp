#include <memory>

#include <dlib/image_processing/render_face_detections.h>

#include <dlib-glib/overlay-line.hpp>

G_BEGIN_DECLS

/**
 * SECTION: overlay-line
 * @title: OverlayLine class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBOverlayLine is a overlay_line class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::image_window::overlay_line> overlay_line;
} GDLIBOverlayLinePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBOverlayLine, gdlib_overlay_line, G_TYPE_OBJECT)

#define GDLIB_OVERLAY_LINE_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                           \
                               GDLIB_TYPE_OVERLAY_LINE,         \
                               GDLIBOverlayLinePrivate))

enum {
  PROP_0,
  PROP_OVERLAY_LINE
};

static void
gdlib_overlay_line_finalize(GObject *object)
{
  auto priv = GDLIB_OVERLAY_LINE_GET_PRIVATE(object);

  priv->overlay_line = nullptr;

  G_OBJECT_CLASS(gdlib_overlay_line_parent_class)->finalize(object);
}

static void
gdlib_overlay_line_set_property(GObject *object,
                                guint prop_id,
                                const GValue *value,
                                GParamSpec *pspec)
{
  auto priv = GDLIB_OVERLAY_LINE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_OVERLAY_LINE:
    priv->overlay_line =
      *static_cast<std::shared_ptr<dlib::image_window::overlay_line> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_overlay_line_init(GDLIBOverlayLine *object)
{
}

static void
gdlib_overlay_line_class_init(GDLIBOverlayLineClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_overlay_line_finalize;
  gobject_class->set_property = gdlib_overlay_line_set_property;

  spec = g_param_spec_pointer("overlay_line",
                              "OverlayLine",
                              "The raw std::shared_ptr<dlib::image_window::overlay_line> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_OVERLAY_LINE, spec);
}

/**
 * gdlib_overlay_line_new:
 *
 * Returns: A newly created #GDLIBOverlayLine.
 *
 * Since: 1.0.0
 */
GDLIBOverlayLine *
gdlib_overlay_line_new(void)
{
  auto dlib_overlay_line
    = std::make_shared<dlib::image_window::overlay_line>();
  return gdlib_overlay_line_new_raw(&dlib_overlay_line);
}

G_END_DECLS

GDLIBOverlayLine *
gdlib_overlay_line_new_raw(std::shared_ptr<dlib::image_window::overlay_line> *dlib_overlay_line)
{
  auto overlay_line = g_object_new(GDLIB_TYPE_OVERLAY_LINE,
                                   "overlay_line", dlib_overlay_line,
                                   NULL);
  return GDLIB_OVERLAY_LINE(overlay_line);
}

std::shared_ptr<dlib::image_window::overlay_line>
gdlib_overlay_line_get_raw(GDLIBOverlayLine *overlay_line)
{
  auto priv = GDLIB_OVERLAY_LINE_GET_PRIVATE(overlay_line);
  return priv->overlay_line;
}
