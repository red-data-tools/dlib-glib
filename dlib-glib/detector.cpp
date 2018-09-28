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
 * #GDlibDetector is a class for face detector.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::frontal_face_detector> detector;
} GDlibDetectorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibDetector, gdlib_detector, G_TYPE_OBJECT)

#define GDlib_DETECTOR_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                       \
                               GDlib_TYPE_DETECTOR,         \
                               GDlibDetectorPrivate))

enum {
  PROP_0,
  PROP_DETECTOR
};

static void
gdlib_detector_finalize(GObject *object)
{
  auto priv = GDlib_DETECTOR_GET_PRIVATE(object);

  priv->detector = nullptr;

  G_OBJECT_CLASS(gdlib_detector_parent_class)->finalize(object);
}

static void
gdlib_detector_set_property(GObject *object,
                            guint prop_id,
                            const GValue *value,
                            GParamSpec *pspec)
{
  auto priv = GDlib_DETECTOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_DETECTOR:
    priv->detector =
      *static_cast<std::shared_ptr<dlib::frontal_face_detector> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_detector_init(GDlibDetector *object)
{
}

static void
gdlib_detector_class_init(GDlibDetectorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_detector_finalize;
  gobject_class->set_property = gdlib_detector_set_property;

  spec = g_param_spec_pointer("detector",
                              "Detector",
                              "The raw std::shared_ptr<dlib::frontal_face_detector> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_DETECTOR, spec);
}

/**
 * gdlib_detector_new:
 *
 * Returns: A newly read #GDlibDetector.
 *
 * Since: 1.0.0
 */
GDlibDetector *
gdlib_detector_new(void)
{
  auto dlib_detector =
    std::make_shared<dlib::frontal_face_detector>(dlib::get_frontal_face_detector());
  return gdlib_detector_new_raw(&dlib_detector);
}

/**
 * gdlib_detector_detect:
 * @detector: A #GDlibDetector.
 * @image: A #GDlibImage.
 *
 * Returns: (element-type GDlibRectangle) (transfer full):
 *   The rectangles of the face detections is made using the now classic HOG feature combined with a linear classifier.
 *
 * Since: 1.0.0
 */
GList *
gdlib_detector_detect(GDlibDetector *detector,
                      GDlibImage *image)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_detector = dlib::get_frontal_face_detector();
  auto dlib_rectangles = dlib_detector(*dlib_image);
  auto size = dlib_rectangles.size();

  GList *rectangles = NULL;
  for (gsize i = 0; i < size; ++i) {
    auto dlib_rectangle = std::make_shared<dlib::rectangle>(dlib_rectangles[i]);
    GDlibRectangle *rectangle = gdlib_rectangle_new_raw(&dlib_rectangle);
    rectangles = g_list_prepend(rectangles, rectangle);
  }

  return g_list_reverse(rectangles);
}

G_END_DECLS

GDlibDetector *
gdlib_detector_new_raw(std::shared_ptr<dlib::frontal_face_detector> *dlib_detector)
{
  auto detector = g_object_new(GDlib_TYPE_DETECTOR,
                               "detector", dlib_detector,
                               NULL);
  return GDlib_DETECTOR(detector);
}

std::shared_ptr<dlib::frontal_face_detector>
gdlib_detector_get_raw(GDlibDetector *detector)
{
  auto priv = GDlib_DETECTOR_GET_PRIVATE(detector);
  return priv->detector;
}
