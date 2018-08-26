#include <dlib/geometry/rectangle.h>

#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: rectangle
 * @title: Rectangle class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBRectangle is a rectangle class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::rectangle> rectangle;
} GDLIBRectanglePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBRectangle, gdlib_rectangle, G_TYPE_OBJECT)

#define GDLIB_RECTANGLE_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                        \
                               GDLIB_TYPE_RECTANGLE,         \
                               GDLIBRectanglePrivate))

enum {
  PROP_0,
  PROP_RECTANGLE
};

static void
gdlib_rectangle_finalize(GObject *object)
{
  auto priv = GDLIB_RECTANGLE_GET_PRIVATE(object);

  priv->rectangle = nullptr;

  G_OBJECT_CLASS(gdlib_rectangle_parent_class)->finalize(object);
}

static void
gdlib_rectangle_set_property(GObject *object,
                             guint prop_id,
                             const GValue *value,
                             GParamSpec *pspec)
{
  auto priv = GDLIB_RECTANGLE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_RECTANGLE:
    priv->rectangle =
      *static_cast<std::shared_ptr<dlib::rectangle> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_rectangle_init(GDLIBRectangle *object)
{
}

static void
gdlib_rectangle_class_init(GDLIBRectangleClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_rectangle_finalize;
  gobject_class->set_property = gdlib_rectangle_set_property;

  spec = g_param_spec_pointer("rectangle",
                              "Rectangle",
                              "The raw std::shared<dlib::rectangle>> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_RECTANGLE, spec);
}

/**
 * gdlib_rectangle_new:
 *
 * Returns: A newly read #GDLIBRectangle.
 *
 * Since: 1.0.0
 */
GDLIBRectangle *
gdlib_rectangle_new(void)
{
  auto rectangle = std::make_shared<dlib::rectangle>();
  return gdlib_rectangle_new_raw(&rectangle);
}

/**
 * gdlib_rectangle_left:
 * @rectangle: A #GDLIBRectangle.
 *
 * Returns: The position of this rectangle.
 *
 * Since: 1.0.0
 */
glong
gdlib_rectangle_left(GDLIBRectangle *rectangle)
{
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  return dlib_rectangle->left();
}

/**
 * gdlib_rectangle_top:
 * @rectangle: A #GDLIBRectangle.
 *
 * Returns: The position of this rectangle.
 *
 * Since: 1.0.0
 */
glong
gdlib_rectangle_top(GDLIBRectangle *rectangle)
{
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  return dlib_rectangle->top();
}

/**
 * gdlib_rectangle_right:
 * @rectangle: A #GDLIBRectangle.
 *
 * Returns: The position of this rectangle.
 *
 * Since: 1.0.0
 */
glong
gdlib_rectangle_right(GDLIBRectangle *rectangle)
{
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  return dlib_rectangle->right();
}

/**
 * gdlib_rectangle_bottom:
 * @rectangle: A #GDLIBRectangle.
 *
 * Returns: The position of this rectangle.
 *
 * Since: 1.0.0
 */
glong
gdlib_rectangle_bottom(GDLIBRectangle *rectangle)
{
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  return dlib_rectangle->bottom();
}

G_END_DECLS

GDLIBRectangle *
gdlib_rectangle_new_raw(std::shared_ptr<dlib::rectangle> *dlib_rectangle)
{
  auto rectangle = g_object_new(GDLIB_TYPE_RECTANGLE,
                                "rectangle", dlib_rectangle,
                                NULL);
  return GDLIB_RECTANGLE(rectangle);
}

std::shared_ptr<dlib::rectangle>
gdlib_rectangle_get_raw(GDLIBRectangle *rectangle)
{
  auto priv = GDLIB_RECTANGLE_GET_PRIVATE(rectangle);
  return priv->rectangle;
}
