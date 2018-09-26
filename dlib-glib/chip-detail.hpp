#pragma once

#include <memory>

#include <dlib-glib/chip-detail.h>

GDlibChipDetail *gdlib_chip_detail_new_raw(std::shared_ptr<dlib::chip_details> *dlib_chip_detail);
std::shared_ptr<dlib::chip_details> gdlib_chip_detail_get_raw(GDlibChipDetail *chip_detail);
