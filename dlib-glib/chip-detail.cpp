#include <memory>

#include <dlib/image_transforms/interpolation.h>

#include <dlib-glib/chip-detail.hpp>
#include <dlib-glib/full-object-detection.hpp>

G_BEGIN_DECLS

/**
 * SECTION: ship-detail
 * @title: ChipDetail class
 * @include: dlib-glib/dlib-glib.h
 *
 * #GDLIBChipDetail is a chip_detail class.
 *
 * Since: 1.0.0
 */

typedef struct {
  std::shared_ptr<dlib::chip_details> chip_detail;
} GDLIBChipDetailPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GDLIBChipDetail, gdlib_chip_detail, G_TYPE_OBJECT)

#define GDLIB_CHIP_DETAIL_GET_PRIVATE(obj)                     \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                          \
                               GDLIB_TYPE_CHIP_DETAIL,         \
                               GDLIBChipDetailPrivate))

enum {
  PROP_0,
  PROP_CHIP_DETAIL
};

static void
gdlib_chip_detail_finalize(GObject *object)
{
  auto priv = GDLIB_CHIP_DETAIL_GET_PRIVATE(object);

  priv->chip_detail = nullptr;

  G_OBJECT_CLASS(gdlib_chip_detail_parent_class)->finalize(object);
}

static void
gdlib_chip_detail_set_property(GObject *object,
                               guint prop_id,
                               const GValue *value,
                               GParamSpec *pspec)
{
  auto priv = GDLIB_CHIP_DETAIL_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_CHIP_DETAIL:
    priv->chip_detail =
      *static_cast<std::shared_ptr<dlib::chip_details> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gdlib_chip_detail_init(GDLIBChipDetail *object)
{
}

static void
gdlib_chip_detail_class_init(GDLIBChipDetailClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gdlib_chip_detail_finalize;
  gobject_class->set_property = gdlib_chip_detail_set_property;

  spec = g_param_spec_pointer("chip_detail",
                              "ChipDetail",
                              "The raw std::shared_ptr<dlib::chip_details> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_CHIP_DETAIL, spec);
}

/**
 * gdlib_chip_detail_new:
 *
 * Returns: A newly created #GDLIBChipDetail.
 *
 * Since: 1.0.0
 */
GDLIBChipDetail *
gdlib_chip_detail_new(void)
{
  auto chip_detail = std::make_shared<dlib::chip_details>();
  return gdlib_chip_detail_new_raw(&chip_detail);
}

G_END_DECLS

GDLIBChipDetail *
gdlib_chip_detail_new_raw(std::shared_ptr<dlib::chip_details> *dlib_chip_detail)
{
  auto chip_detail = g_object_new(GDLIB_TYPE_CHIP_DETAIL,
                                  "chip_detail", dlib_chip_detail,
                                  NULL);
  return GDLIB_CHIP_DETAIL(chip_detail);
}

std::shared_ptr<dlib::chip_details>
gdlib_chip_detail_get_raw(GDLIBChipDetail *chip_detail)
{
  auto priv = GDLIB_CHIP_DETAIL_GET_PRIVATE(chip_detail);
  return priv->chip_detail;
}
