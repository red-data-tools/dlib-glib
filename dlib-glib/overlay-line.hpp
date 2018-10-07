#pragma once

#include <memory>

#include <dlib/image_processing/render_face_detections.h>

#include <dlib-glib/overlay-line.h>

GDlibOverlayLine *gdlib_overlay_line_new_raw(std::shared_ptr<dlib::image_window::overlay_line> *overlay_line);
std::shared_ptr<dlib::image_window::overlay_line> gdlib_overlay_line_get_raw(GDlibOverlayLine *overlay_line);
