#pragma once

#include <gtkmm.h>

#include "file-bar-label.h"

// #define DRAW_TYPE_FILE_BAR file_bar_get_type()

// G_DECLARE_FINAL_TYPE(FileBar, file_bar, FILE_BAR, WIDGET, GtkBox)
// COMPONENT_H(FileBar, file_bar)

using namespace std;
using namespace Gtk;

class FileBar : public Box {
public:
  FileBar() {
    this->set_expand(true);
    Notebook *notebook = new Notebook();
    notebook->set_expand(true);

    auto button = new Button("test");
    auto label = new FileBarLabel("Cat", notebook, button);

    notebook->append_page(*button, *label);

    this->append(*notebook);
  }
};
