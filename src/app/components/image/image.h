#pragma once

#include "gui/gui.h"

#define DRAW_TYPE_IMAGE draw_image_get_type()

G_DECLARE_FINAL_TYPE(DrawImage, draw_image, IMAGE, WIDGET, GtkBox)
COMPONENT_H(DrawImage, draw_image)

// class Image : public Component {
// public:
//   GtkWidget* getType();
// };
