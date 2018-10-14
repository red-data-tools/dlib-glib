#include <dlib-glib/full-object-detection.hpp>
#include <dlib-glib/shape-predictor.hpp>
#include <dlib-glib/image.hpp>
#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: shape-predictor
 * @title: ShapePredictor class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDlibShapePredictor is a class for shape prediction.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::shape_predictor> shape_predictor;
} GDlibShapePredictorPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibShapePredictor, gdlib_shape_predictor, G_TYPE_OBJECT)

#define GDlib_SHAPE_PREDICTOR_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                              \
                               GDLIB_TYPE_SHAPE_PREDICTOR,         \
                               GDlibShapePredictorPrivate))

enum {
  PROP_0,
  PROP_SHAPE_PREDICTOR
};

static void
gdlib_shape_predictor_finalize(GObject *object)
{
  auto priv = GDlib_SHAPE_PREDICTOR_GET_PRIVATE(object);

  priv->shape_predictor = nullptr;

  G_OBJECT_CLASS(gdlib_shape_predictor_parent_class)->finalize(object);
}

static void
gdlib_shape_predictor_set_property(GObject *object,
                                   guint prop_id,
                                   const GValue *value,
                                   GParamSpec *pspec)
{
  auto priv = GDlib_SHAPE_PREDICTOR_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_SHAPE_PREDICTOR:
    priv->shape_predictor =
      *static_cast<std::shared_ptr<dlib::shape_predictor> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_shape_predictor_init(GDlibShapePredictor *object)
{
}

static void
gdlib_shape_predictor_class_init(GDlibShapePredictorClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_shape_predictor_finalize;
  gobject_class->set_property = gdlib_shape_predictor_set_property;

  spec = g_param_spec_pointer("shape_predictor",
                              "ShapePredictor",
                              "The raw std::shared_ptr<dlib::shape_predictor> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_SHAPE_PREDICTOR, spec);
}

/**
 * gdlib_shape_predictor_new:
 * @predictor: The trained shape predictor model.
 *
 * Returns: A newly read #GDlibShapePredictor.
 *
 * Since: 1.0.0
 */
GDlibShapePredictor *
gdlib_shape_predictor_new(const gchar *predictor)
{
  auto shape_predictor = std::make_shared<dlib::shape_predictor>();
  dlib::deserialize(predictor) >> *shape_predictor;
  return gdlib_shape_predictor_new_raw(&shape_predictor);
}

/**
 * gdlib_shape_predictor_detect:
 * @shape_predictor: A #GDlibShapePredictor.
 * @image: A #GDlibImage.
 * @rectangle: A #GDlibRectangle.
 *
 * Returns: (transfer full):
 *   The full object detection of each face detected.
 *
 * Since: 1.0.0
 */
GDlibFullObjectDetection *
gdlib_shape_predictor_detect(GDlibShapePredictor *shape_predictor,
                             GDlibImage *image,
                             GDlibRectangle *rectangle)
{
  auto dlib_shape_predictor =
    *gdlib_shape_predictor_get_raw(shape_predictor);
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  auto full_object_detection =
    dlib_shape_predictor(*dlib_image, *dlib_rectangle);
  auto dlib_full_object_detection =
    std::make_shared<dlib::full_object_detection>(full_object_detection);
  return gdlib_full_object_detection_new_raw(&dlib_full_object_detection);
}

G_END_DECLS

GDlibShapePredictor *
gdlib_shape_predictor_new_raw(std::shared_ptr<dlib::shape_predictor> *dlib_shape_predictor)
{
  auto shape_predictor = g_object_new(GDLIB_TYPE_SHAPE_PREDICTOR,
                                      "shape_predictor", dlib_shape_predictor,
                                      NULL);
  return GDlib_SHAPE_PREDICTOR(shape_predictor);
}

std::shared_ptr<dlib::shape_predictor>
gdlib_shape_predictor_get_raw(GDlibShapePredictor *shape_predictor)
{
  auto priv = GDlib_SHAPE_PREDICTOR_GET_PRIVATE(shape_predictor);
  return priv->shape_predictor;
}
