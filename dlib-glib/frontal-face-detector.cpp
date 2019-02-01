#include <dlib-glib/frontal-face-detector.hpp>
#include <dlib-glib/image.hpp>
#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: frontal-face-detector
 * @title: FrontalFaceDetector class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDlibFrontalFaceDetector is a class for face detector.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::frontal_face_detector> frontal_face_detector;
} GDlibFrontalFaceDetectorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibFrontalFaceDetector, gdlib_frontal_face_detector, G_TYPE_OBJECT)

#define GDLIB_FRONTAL_FACE_DETECTOR_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                                    \
                               GDLIB_TYPE_FRONTAL_FACE_DETECTOR,         \
                               GDlibFrontalFaceDetectorPrivate))

enum {
  PROP_0,
  PROP_FRONTAL_FACE_DETECTOR
};

static void
gdlib_frontal_face_detector_finalize(GObject *object)
{
  auto priv = GDLIB_FRONTAL_FACE_DETECTOR_GET_PRIVATE(object);

  priv->frontal_face_detector = nullptr;

  G_OBJECT_CLASS(gdlib_frontal_face_detector_parent_class)->finalize(object);
}

static void
gdlib_frontal_face_detector_set_property(GObject *object,
                                         guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec)
{
  auto priv = GDLIB_FRONTAL_FACE_DETECTOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_FRONTAL_FACE_DETECTOR:
    priv->frontal_face_detector =
      *static_cast<std::shared_ptr<dlib::frontal_face_detector> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_frontal_face_detector_init(GDlibFrontalFaceDetector *object)
{
}

static void
gdlib_frontal_face_detector_class_init(GDlibFrontalFaceDetectorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_frontal_face_detector_finalize;
  gobject_class->set_property = gdlib_frontal_face_detector_set_property;

  spec = g_param_spec_pointer("frontal_face_detector",
                              "FrontalFaceDetector",
                              "The raw std::shared_ptr<dlib::frontal_face_detector> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_FRONTAL_FACE_DETECTOR, spec);
}

/**
 * gdlib_frontal_face_detector_new:
 *
 * Returns: A newly created #GDlibFrontalFaceDetector.
 *
 * Since: 1.0.0
 */
GDlibFrontalFaceDetector *
gdlib_frontal_face_detector_new(void)
{
  auto dlib_frontal_face_detector =
    std::make_shared<dlib::frontal_face_detector>(dlib::get_frontal_face_detector());
  return gdlib_frontal_face_detector_new_raw(&dlib_frontal_face_detector);
}

/**
 * gdlib_frontal_face_detector_detect:
 * @frontal_face_detector: A #GDlibFrontalFaceDetector.
 * @image: A #GDlibImage.
 *
 * Returns: (element-type GDlibRectangle) (transfer full):
 *   The rectangles of the face detections is made using the now classic
 *   HOG feature combined with a linear classifier.
 *
 * Since: 1.0.0
 */
GList *
gdlib_frontal_face_detector_detect(GDlibFrontalFaceDetector *frontal_face_detector,
                                   GDlibImage *image)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_frontal_face_detector = dlib::get_frontal_face_detector();
  auto dlib_rectangles = dlib_frontal_face_detector(*dlib_image);
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

GDlibFrontalFaceDetector *
gdlib_frontal_face_detector_new_raw(std::shared_ptr<dlib::frontal_face_detector> *dlib_frontal_face_detector)
{
  auto frontal_face_detector = g_object_new(GDLIB_TYPE_FRONTAL_FACE_DETECTOR,
                                            "frontal_face_detector", dlib_frontal_face_detector,
                                            NULL);
  return GDlib_FRONTAL_FACE_DETECTOR(frontal_face_detector);
}

std::shared_ptr<dlib::frontal_face_detector>
gdlib_frontal_face_detector_get_raw(GDlibFrontalFaceDetector *frontal_face_detector)
{
  auto priv = GDLIB_FRONTAL_FACE_DETECTOR_GET_PRIVATE(frontal_face_detector);
  return priv->frontal_face_detector;
}
