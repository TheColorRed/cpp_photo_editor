#pragma once

#include "gui/gui.h"

#define DRAW_TYPE_MENU_FILE menu_file_get_type()

G_DECLARE_FINAL_TYPE(MenuFile, menu_file, MENU_FILE, WIDGET, GtkBox)

void menu_file_win_startup(GtkWindow *win);
