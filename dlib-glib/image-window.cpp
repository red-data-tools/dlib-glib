#include <dlib-glib/image-window.hpp>
#include <dlib-glib/image.hpp>
#include <dlib-glib/overlay-line.hpp>
#include <dlib-glib/chip-detail.hpp>

G_BEGIN_DECLS

/**
 * SECTION: image-window
 * @title: ImageWindow class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDlibImageWindow is a class for GUI window capable of showing images
 * on the screen.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::image_window> image_window;
} GDlibImageWindowPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDlibImageWindow, gdlib_image_window, G_TYPE_OBJECT)

#define GDLIB_IMAGE_WINDOW_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                           \
                               GDLIB_TYPE_IMAGE_WINDOW,         \
                               GDlibImageWindowPrivate))

enum {
  PROP_0,
  PROP_IMAGE_WINDOW
};

static void
gdlib_image_window_finalize(GObject *object)
{
  auto priv = GDLIB_IMAGE_WINDOW_GET_PRIVATE(object);

  priv->image_window = nullptr;

  G_OBJECT_CLASS(gdlib_image_window_parent_class)->finalize(object);
}

static void
gdlib_image_window_set_property(GObject *object,
                                guint prop_id,
                                const GValue *value,
                                GParamSpec *pspec)
{
  auto priv = GDLIB_IMAGE_WINDOW_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_IMAGE_WINDOW:
    priv->image_window =
      *static_cast<std::shared_ptr<dlib::image_window> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_image_window_init(GDlibImageWindow *object)
{
}

static void
gdlib_image_window_class_init(GDlibImageWindowClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_image_window_finalize;
  gobject_class->set_property = gdlib_image_window_set_property;

  spec = g_param_spec_pointer("image_window",
                              "ImageWindow",
                              "The raw std::shared_ptr<dlib::image_window> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_IMAGE_WINDOW, spec);
}

/**
 * gdlib_image_window_new:
 *
 * Returns: A newly created #GDlibImageWindow.
 *
 * Since: 1.0.0
 */
GDlibImageWindow *
gdlib_image_window_new(void)
{
  auto image_window = std::make_shared<dlib::image_window>();
  return gdlib_image_window_new_raw(&image_window);
}

/**
 * gdlib_image_window_clear_overlay:
 * @image_window: A #GDlibImageWindow.
 *
 * Since: 1.0.0
 */
void
gdlib_image_window_clear_overlay(GDlibImageWindow *image_window)
{
  auto dlib_image_window = gdlib_image_window_get_raw(image_window);
  dlib_image_window->clear_overlay();
}

/**
 * gdlib_image_window_set_image:
 * @image_window: A #GDlibImageWindow.
 * @image: A #GDlibImage.
 *
 * Since: 1.0.0
 */
void
gdlib_image_window_set_image(GDlibImageWindow *image_window,
                             GDlibImage *image)
{
  auto dlib_image_window = gdlib_image_window_get_raw(image_window);
  auto dlib_image = gdlib_image_get_raw(image);
  dlib_image_window->set_image(*dlib_image);
}

/**
 * gdlib_image_window_add_overlay:
 * @image_window: A #GDlibImageWindow.
 * @overlay_lines: (element-type GDlibOverlayLine):
 *   The lines added to image_window.
 *
 * Since: 1.0.0
 */
void
gdlib_image_window_add_overlay(GDlibImageWindow *image_window,
                               GList *overlay_lines)
{
  auto dlib_image_window = gdlib_image_window_get_raw(image_window);
  std::vector<dlib::image_window::overlay_line> dlib_overlay_lines;
  for (GList *node = overlay_lines; node; node = node->next) {
    GDlibOverlayLine *overlay_line = GDlib_OVERLAY_LINE(node->data);
    dlib_overlay_lines.push_back(*gdlib_overlay_line_get_raw(overlay_line));
  }
  dlib_image_window->add_overlay(dlib_overlay_lines);
}

/**
 * gdlib_image_window_wait_until_closed:
 * @image_window: A #GDlibImageWindow.
 *
 * Since: 1.0.0
 */
void
gdlib_image_window_wait_until_closed(GDlibImageWindow *image_window)
{
  auto dlib_image_window = gdlib_image_window_get_raw(image_window);
  dlib_image_window->wait_until_closed();
}

/**
 * gdlib_image_window_set_face_chip_details:
 * @image_window: A #GDlibImageWindow.
 * @image: A #GDlibImage.
 * @chip_details: (element-type GDlibChipDetail):
 *   The #GDlibChipDetail in the full object detections.
 *
 * Since: 1.0.0
 */
void
gdlib_image_window_set_face_chip_details(GDlibImageWindow *image_window,
                                         GDlibImage *image,
                                         GList *chip_details)
{
  auto dlib_image_window = gdlib_image_window_get_raw(image_window);
  auto dlib_image = gdlib_image_get_raw(image);
  std::vector<dlib::chip_details> dlib_chip_details;
  for (GList *node = chip_details; node; node = node->next) {
    GDlibChipDetail *chip_detail = GDlib_CHIP_DETAIL(node->data);
    dlib_chip_details.push_back(*gdlib_chip_detail_get_raw(chip_detail));
  }
  dlib::array<dlib::array2d<dlib::rgb_pixel>> dlib_face_chips;
  dlib::extract_image_chips(*dlib_image, dlib_chip_details, dlib_face_chips);
  dlib_image_window->set_image(dlib::tile_images(dlib_face_chips));
}

G_END_DECLS

GDlibImageWindow *
gdlib_image_window_new_raw(std::shared_ptr<dlib::image_window> *dlib_image_window)
{
  auto image_window = g_object_new(GDLIB_TYPE_IMAGE_WINDOW,
                                   "image_window", dlib_image_window,
                                   NULL);
  return GDlib_IMAGE_WINDOW(image_window);
}

std::shared_ptr<dlib::image_window>
gdlib_image_window_get_raw(GDlibImageWindow *image_window)
{
  auto priv = GDLIB_IMAGE_WINDOW_GET_PRIVATE(image_window);
  return priv->image_window;
}
