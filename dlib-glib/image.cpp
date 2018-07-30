#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include <dlib-glib/image.hpp>
#include <dlib-glib/rectangle.hpp>

G_BEGIN_DECLS

/**
 * SECTION: image
 * @title: Image class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBImage is a image class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> image;
} GDLIBImagePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBImage, gdlib_image, G_TYPE_OBJECT)

#define GDLIB_IMAGE_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                    \
                               GDLIB_TYPE_IMAGE,         \
                               GDLIBImagePrivate))

enum {
  PROP_0,
  PROP_IMAGE
};

static void
gdlib_image_finalize(GObject *object)
{
  auto priv = GDLIB_IMAGE_GET_PRIVATE(object);

  priv->image = nullptr;

  G_OBJECT_CLASS(gdlib_image_parent_class)->finalize(object);
}

static void
gdlib_image_set_property(GObject *object,
                         guint prop_id,
                         const GValue *value,
                         GParamSpec *pspec)
{
  auto priv = GDLIB_IMAGE_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_IMAGE:
    priv->image =
      *static_cast<std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_image_init(GDLIBImage *object)
{
}

static void
gdlib_image_class_init(GDLIBImageClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_image_finalize;
  gobject_class->set_property = gdlib_image_set_property;

  spec = g_param_spec_pointer("image",
                              "Image",
                              "The raw std::shared<dlib::array2d<dlib::rgb_pixel>> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_IMAGE, spec);
}

/**
 * gdlib_image_new:
 * @filename: The filename to be read.
 *
 * Since: 1.0.0
 */
GDLIBImage *
gdlib_image_new(const gchar *filename)
{
  auto image = std::make_shared<dlib::array2d<dlib::rgb_pixel>>();
  dlib::load_image(*image, filename);
  return gdlib_image_new_raw(&image);
}

/**
 * gdlib_image_save_jpeg:
 * @image: A #GDLIBImage.
 * @filename: The filename to be read.
 *
 * Since: 1.0.0
 */
void *
gdlib_image_save_jpeg(GDLIBImage *image, const gchar *filename)
{
  auto dlib_image = gdlib_image_get_raw(image);
  dlib::save_jpeg(*dlib_image, filename);
  return image;
}

/**
 * gdlib_image_draw_rectangle:
 * @image: A #GDLIBImage.
 * @rectangle: A #GDLIBRectangle.
 * @red: A red pixel value.
 * @green: A green pixel value.
 * @blue: A blue pixel value.
 */
void *
gdlib_image_draw_rectangle(GDLIBImage *image,
                           GDLIBRectangle *rectangle,
                           gdouble red,
                           gdouble green,
                           gdouble blue)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  auto dlib_rgb_pixel = dlib::rgb_pixel(red, green, blue);
  dlib::draw_rectangle(*dlib_image, *dlib_rectangle, dlib_rgb_pixel);
  return image;
}

G_END_DECLS

GDLIBImage *
gdlib_image_new_raw(std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> *dlib_image)
{
  auto image = g_object_new(GDLIB_TYPE_IMAGE,
                            "image", dlib_image,
                            NULL);
  return GDLIB_IMAGE(image);
}

std::shared_ptr<dlib::array2d<dlib::rgb_pixel>>
gdlib_image_get_raw(GDLIBImage *image)
{
  auto priv = GDLIB_IMAGE_GET_PRIVATE(image);
  return priv->image;
}
