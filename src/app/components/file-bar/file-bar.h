#pragma once

#include "gui/gui.h"

#define DRAW_TYPE_FILE_BAR file_bar_get_type()

G_DECLARE_FINAL_TYPE(FileBar, file_bar, FILE_BAR, WIDGET, GtkBox)
COMPONENT_H(FileBar, file_bar)
