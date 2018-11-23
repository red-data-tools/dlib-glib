#include <dlib-glib/image.hpp>
#include <dlib-glib/rectangle.hpp>
#include <dlib-glib/chip-detail.hpp>

G_BEGIN_DECLS

/**
 * SECTION: image
 * @title: Image class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDlibImage is a class for image.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> image;
} GDlibImagePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibImage, gdlib_image, G_TYPE_OBJECT)

#define GDlib_IMAGE_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                    \
                               GDLIB_TYPE_IMAGE,         \
                               GDlibImagePrivate))

enum {
  PROP_0,
  PROP_IMAGE
};

static void
gdlib_image_finalize(GObject *object)
{
  auto priv = GDlib_IMAGE_GET_PRIVATE(object);

  priv->image = nullptr;

  G_OBJECT_CLASS(gdlib_image_parent_class)->finalize(object);
}

static void
gdlib_image_set_property(GObject *object,
                         guint prop_id,
                         const GValue *value,
                         GParamSpec *pspec)
{
  auto priv = GDlib_IMAGE_GET_PRIVATE(object);

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
gdlib_image_init(GDlibImage *object)
{
}

static void
gdlib_image_class_init(GDlibImageClass *klass)
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
 * Returns: A newly created #GDlibImage.
 *
 * Since: 1.0.0
 */
GDlibImage *
gdlib_image_new(const gchar *filename)
{
  auto image = std::make_shared<dlib::array2d<dlib::rgb_pixel>>();
  dlib::load_image(*image, filename);
  return gdlib_image_new_raw(&image);
}

/**
 * gdlib_image_save_jpeg:
 * @image: A #GDlibImage.
 * @filename: The filename to be read.
 *
 * Since: 1.0.0
 */
void
gdlib_image_save_jpeg(GDlibImage *image,
                      const gchar *filename)
{
  auto dlib_image = gdlib_image_get_raw(image);
  dlib::save_jpeg(*dlib_image, filename);
}

/**
 * gdlib_image_draw_rectangle:
 * @image: A #GDlibImage.
 * @rectangle: A #GDlibRectangle.
 * @red: A red pixel value.
 * @green: A green pixel value.
 * @blue: A blue pixel value.
 *
 * Since: 1.0.0
 */
void
gdlib_image_draw_rectangle(GDlibImage *image,
                           GDlibRectangle *rectangle,
                           gdouble red,
                           gdouble green,
                           gdouble blue)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_rectangle = gdlib_rectangle_get_raw(rectangle);
  auto dlib_rgb_pixel = dlib::rgb_pixel(red, green, blue);
  dlib::draw_rectangle(*dlib_image, *dlib_rectangle, dlib_rgb_pixel);
}

/**
 * gdlib_image_gaussian_blur:
 * @image: A #GDlibImage.
 *
 * Returns: (transfer full): The image blurred
 *   using Gaussian function.
 *
 * Since: 1.0.0
 */
GDlibImage *
gdlib_image_gaussian_blur(GDlibImage *image)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_blurred_image = std::make_shared<dlib::array2d<dlib::rgb_pixel>>();
  dlib::gaussian_blur(*dlib_image, *dlib_blurred_image);
  return gdlib_image_new_raw(&dlib_blurred_image);
}

/**
 * gdlib_image_extract_image_chip:
 * @image: A #GDlibImage.
 * @chip_detail: A #GDlibChipDetail.
 *
 * Returns: (transfer full):
 *   The image of each face that are cropped.
 *
 * Since: 1.0.0
 */
GDlibImage *
gdlib_image_extract_image_chip(GDlibImage *image,
                               GDlibChipDetail *chip_detail)
{
  auto dlib_image = gdlib_image_get_raw(image);
  auto dlib_chip_detail = gdlib_chip_detail_get_raw(chip_detail);
  auto dlib_face_chip = std::make_shared<dlib::array2d<dlib::rgb_pixel>>();
  dlib::extract_image_chip(*dlib_image, *dlib_chip_detail, *dlib_face_chip);
  return gdlib_image_new_raw(&dlib_face_chip);
}

/**
 * gdlib_image_find_candidate_object_locations:
 * @image: A #GDlibImage.
 * @min_size: The size of the output segments.
 * @max_merging_iterations: The number of iterations has
 *   some effect on the number of output rectangles.
 *
 * Returns: (element-type GDlibRectangle) (transfer full):
 *   The rectangles of locations of candidate objects.
 *
 * Since: 1.0.0
 */
GList *
gdlib_image_find_candidate_object_locations(GDlibImage *image,
                                            gint min_size,
                                            gint max_merging_iterations)
{
  auto dlib_image = gdlib_image_get_raw(image);
  std::vector<dlib::rectangle> dlib_rectangles;
  dlib::find_candidate_object_locations(*dlib_image, dlib_rectangles, dlib::linspace(20, 200, 3), min_size, max_merging_iterations);
  auto size = dlib_rectangles.size();
  GList *rectangles = NULL;
  for (gsize i = 0; i < size; ++i) {
    auto dlib_rectangle =
      std::make_shared<dlib::rectangle>(dlib_rectangles[i]);
    auto rectangle = gdlib_rectangle_new_raw(&dlib_rectangle);
    rectangles = g_list_prepend(rectangles, rectangle);
  }

  return g_list_reverse(rectangles);
}

/**
 * gdlib_image_get_n_rows:
 * @image: A #GDlibImage.
 *
 * Returns: The number of rows in the image.
 *
 * Since: 1.0.0
 */
glong
gdlib_image_get_n_rows(GDlibImage *image)
{
  auto dlib_image = gdlib_image_get_raw(image);
  return dlib_image->nr();
}

G_END_DECLS

GDlibImage *
gdlib_image_new_raw(std::shared_ptr<dlib::array2d<dlib::rgb_pixel>> *dlib_image)
{
  auto image = g_object_new(GDLIB_TYPE_IMAGE,
                            "image", dlib_image,
                            NULL);
  return GDlib_IMAGE(image);
}

std::shared_ptr<dlib::array2d<dlib::rgb_pixel>>
gdlib_image_get_raw(GDlibImage *image)
{
  auto priv = GDlib_IMAGE_GET_PRIVATE(image);
  return priv->image;
}
