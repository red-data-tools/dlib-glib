#include <memory>

#include <dlib/image_processing/shape_predictor.h>
#include <dlib/image_processing/full_object_detection.h>

#include <dlib-glib/full-object-detection.hpp>
#include <dlib-glib/shape-predictor.hpp>
#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: full-object-detection
 * @title: FullObjectDetection class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBFullObjectDetection is a full_object_detection class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::full_object_detection> full_object_detection;
} GDLIBFullObjectDetectionPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBFullObjectDetection, gdlib_full_object_detection, G_TYPE_OBJECT)

#define GDLIB_FULL_OBJECT_DETECTION_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                                    \
                               GDLIB_TYPE_FULL_OBJECT_DETECTION,         \
                               GDLIBFullObjectDetectionPrivate))

enum {
  PROP_0,
  PROP_FULL_OBJECT_DETECTION
};

static void
gdlib_full_object_detection_finalize(GObject *object)
{
  auto priv = GDLIB_FULL_OBJECT_DETECTION_GET_PRIVATE(object);

  priv->full_object_detection = nullptr;

  G_OBJECT_CLASS(gdlib_full_object_detection_parent_class)->finalize(object);
}

static void
gdlib_full_object_detection_set_property(GObject *object,
                                         guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec)
{
  auto priv = GDLIB_FULL_OBJECT_DETECTION_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_FULL_OBJECT_DETECTION:
    priv->full_object_detection =
      *static_cast<std::shared_ptr<dlib::full_object_detection> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_full_object_detection_init(GDLIBFullObjectDetection *object)
{
}

static void
gdlib_full_object_detection_class_init(GDLIBFullObjectDetectionClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_full_object_detection_finalize;
  gobject_class->set_property = gdlib_full_object_detection_set_property;

  spec = g_param_spec_pointer("full_object_detection",
                              "FullObjectDetection",
                              "The raw std::shared_ptr<dlib::full_object_detection> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_FULL_OBJECT_DETECTION, spec);
}

/**
 * gdlib_full_object_detection_new:
 * @rectangle: A #GDLIBRectangle.
 *
 * Returns: A newly read #GDLIBFullObjectDetection.
 *
 * Since: 1.0.0
 */
GDLIBFullObjectDetection *
gdlib_full_object_detection_new(GDLIBRectangle *rectangle)
{
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  auto dlib_full_object_detection
    = std::make_shared<dlib::full_object_detection>(*dlib_rectangle);
  return gdlib_full_object_detection_new_raw(&dlib_full_object_detection);
}

/**
 * gdlib_full_object_detection_rectangle:
 * @full_object_detection: A #GDLIBFullObjectDetection.
 *
 * Returns: (transfer full):
 *   The #GDLIBRectangle of the full object detection.
 *
 * Since: 1.0.0
 */
GDLIBRectangle *
gdlib_full_object_detection_rectangle(GDLIBFullObjectDetection *full_object_detection)
{
  auto dlib_full_object_detection
    = gdlib_full_object_detection_get_raw(full_object_detection);
  auto dlib_rectangle
    = std::make_shared<dlib::rectangle>(dlib_full_object_detection->get_rect());
  return gdlib_rectangle_new_raw(&dlib_rectangle);
}

/**
 * gdlib_full_object_detection_get_n_parts:
 * @full_object_detection: A #GDLIBFullObjectDetection.
 *
 * Returns: The number of parts of the full object detection.
 *
 * Since: 1.0.0
 */
gulong
gdlib_full_object_detection_get_n_parts(GDLIBFullObjectDetection *full_object_detection)
{
  auto dlib_full_object_detection
    = gdlib_full_object_detection_get_raw(full_object_detection);
  return dlib_full_object_detection->num_parts();
}

G_END_DECLS

GDLIBFullObjectDetection *
gdlib_full_object_detection_new_raw(std::shared_ptr<dlib::full_object_detection> *dlib_full_object_detection)
{
  auto full_object_detection = g_object_new(GDLIB_TYPE_FULL_OBJECT_DETECTION,
                                            "full_object_detection", dlib_full_object_detection,
                                            NULL);
  return GDLIB_FULL_OBJECT_DETECTION(full_object_detection);
}

std::shared_ptr<dlib::full_object_detection>
gdlib_full_object_detection_get_raw(GDLIBFullObjectDetection *full_object_detection)
{
  auto priv = GDLIB_FULL_OBJECT_DETECTION_GET_PRIVATE(full_object_detection);
  return priv->full_object_detection;
}
