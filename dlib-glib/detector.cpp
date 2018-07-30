#include <memory>

#include <dlib/image_processing/frontal_face_detector.h>

#include <dlib-glib/detector.hpp>
#include <dlib-glib/image.hpp>
#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: detector
 * @title: Detector class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBDetector is a detector class.
 *
 * Since: 1.0.0
 */

typedef struct {
  dlib::frontal_face_detector *detector;
} GDLIBDetectorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBDetector, gdlib_detector, G_TYPE_OBJECT)

#define GDLIB_DETECTOR_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                       \
                               GDLIB_TYPE_DETECTOR,         \
                               GDLIBDetectorPrivate))

enum {
  PROP_0,
  PROP_DETECTOR
};

static void
gdlib_detector_finalize(GObject *object)
{
  auto priv = GDLIB_DETECTOR_GET_PRIVATE(object);

  priv->detector = nullptr;

  G_OBJECT_CLASS(gdlib_detector_parent_class)->finalize(object);
}

static void
gdlib_detector_set_property(GObject *object,
                            guint prop_id,
                            const GValue *value,
                            GParamSpec *pspec)
{
  auto priv = GDLIB_DETECTOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_DETECTOR:
    priv->detector =
      static_cast<dlib::frontal_face_detector *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_detector_init(GDLIBDetector *object)
{
}

static void
gdlib_detector_class_init(GDLIBDetectorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_detector_finalize;
  gobject_class->set_property = gdlib_detector_set_property;

  spec = g_param_spec_pointer("detector",
                              "Detector",
                              "The raw dlib::frontal_face_detector *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_DETECTOR, spec);
}

/**
 * gdlib_detector_new:
 *
 * Returns: A newly read #GDLIBDetector.
 *
 * Since: 1.0.0
 */
GDLIBDetector *
gdlib_detector_new(void)
{
  auto detector = dlib::get_frontal_face_detector();
  return gdlib_detector_new_raw(&detector);
}

/**
 * gdlib_detector_detect:
 * @detector: A #GDLIBDetector.
 * @image: A #GDLIBImage.
 *
 * Returns: (element-type GDLIBRectangle) (transfer full):
 *   The #GDLIBRectangle of the rectangles.
 *
 * Since: 1.0.0
 */
GList *
gdlib_detector_detect(GDLIBDetector *detector,
                      GDLIBImage *image)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_detector = dlib::get_frontal_face_detector();
  auto dlib_rectangles = dlib_detector(*dlib_image);
  auto size = dlib_rectangles.size();

  GList *rectangles = NULL;
  for (gsize i = 0; i < size; ++i) {
    auto dlib_rectangle = std::make_shared<dlib::rectangle>(dlib_rectangles[i]);
    GDLIBRectangle *rectangle = gdlib_rectangle_new_raw(&dlib_rectangle);
    rectangles = g_list_prepend(rectangles, rectangle);
  }

  return g_list_reverse(rectangles);
}

G_END_DECLS

GDLIBDetector *
gdlib_detector_new_raw(dlib::frontal_face_detector *dlib_detector)
{
  auto detector = g_object_new(GDLIB_TYPE_DETECTOR,
                               "detector", dlib_detector,
                               NULL);
  return GDLIB_DETECTOR(detector);
}

dlib::frontal_face_detector *
gdlib_detector_get_raw(GDLIBDetector *detector)
{
  auto priv = GDLIB_DETECTOR_GET_PRIVATE(detector);
  return priv->detector;
}
