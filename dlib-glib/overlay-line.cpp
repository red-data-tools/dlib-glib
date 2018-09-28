#include <memory>

#include <dlib/image_processing/render_face_detections.h>

#include <dlib-glib/overlay-line.hpp>
#include <dlib-glib/full-object-detection.hpp>

G_BEGIN_DECLS

/**
 * SECTION: overlay-line
 * @title: OverlayLine class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDlibOverlayLine is a class for overlay line.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::image_window::overlay_line> overlay_line;
} GDlibOverlayLinePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibOverlayLine, gdlib_overlay_line, G_TYPE_OBJECT)

#define GDlib_OVERLAY_LINE_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                           \
                               GDlib_TYPE_OVERLAY_LINE,         \
                               GDlibOverlayLinePrivate))

enum {
  PROP_0,
  PROP_OVERLAY_LINE
};

static void
gdlib_overlay_line_finalize(GObject *object)
{
  auto priv = GDlib_OVERLAY_LINE_GET_PRIVATE(object);

  priv->overlay_line = nullptr;

  G_OBJECT_CLASS(gdlib_overlay_line_parent_class)->finalize(object);
}

static void
gdlib_overlay_line_set_property(GObject *object,
                                guint prop_id,
                                const GValue *value,
                                GParamSpec *pspec)
{
  auto priv = GDlib_OVERLAY_LINE_GET_PRIVATE(object);

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
gdlib_overlay_line_init(GDlibOverlayLine *object)
{
}

static void
gdlib_overlay_line_class_init(GDlibOverlayLineClass *klass)
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
 * Returns: A newly created #GDlibOverlayLine.
 *
 * Since: 1.0.0
 */
GDlibOverlayLine *
gdlib_overlay_line_new(void)
{
  auto dlib_overlay_line =
    std::make_shared<dlib::image_window::overlay_line>();
  return gdlib_overlay_line_new_raw(&dlib_overlay_line);
}

/**
 * gdlib_overlay_line_render_face_detections:
 * @full_object_detections: (element-type GDlibFullObjectDetection):
 *    The full object detections.
 *
 * Returns: (element-type GDlibOverlayLine) (transfer full):
 *   The overlay lines rendering face detections with the full object detections.
 *
 * Since: 1.0.0
 */
GList *
gdlib_overlay_line_render_face_detections(GList *full_object_detections)
{
  std::vector<dlib::full_object_detection> dlib_full_object_detections;
  for (GList *node = full_object_detections; node; node = node->next) {
    GDlibFullObjectDetection *full_object_detection = GDlib_FULL_OBJECT_DETECTION(node->data);
    dlib_full_object_detections.push_back(*gdlib_full_object_detection_get_raw(full_object_detection));
  }
  auto dlib_overlay_lines = dlib::render_face_detections(dlib_full_object_detections);
  auto size = dlib_overlay_lines.size();
  GList *overlay_lines = NULL;
  for (gsize i = 0; i < size; ++i) {
    auto dlib_overlay_line =
      std::make_shared<dlib::image_window::overlay_line>(dlib_overlay_lines[i]);
    GDlibOverlayLine *overlay_line = gdlib_overlay_line_new_raw(&dlib_overlay_line);
    overlay_lines = g_list_prepend(overlay_lines, overlay_line);
  }

  return g_list_reverse(overlay_lines);
}

G_END_DECLS

GDlibOverlayLine *
gdlib_overlay_line_new_raw(std::shared_ptr<dlib::image_window::overlay_line> *dlib_overlay_line)
{
  auto overlay_line = g_object_new(GDlib_TYPE_OVERLAY_LINE,
                                   "overlay_line", dlib_overlay_line,
                                   NULL);
  return GDlib_OVERLAY_LINE(overlay_line);
}

std::shared_ptr<dlib::image_window::overlay_line>
gdlib_overlay_line_get_raw(GDlibOverlayLine *overlay_line)
{
  auto priv = GDlib_OVERLAY_LINE_GET_PRIVATE(overlay_line);
  return priv->overlay_line;
}
