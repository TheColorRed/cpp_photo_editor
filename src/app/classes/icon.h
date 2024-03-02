#pragma once

#include <gtk/gtk.h>
#include <gtkmm.h>

#include <variant>

using namespace std;

enum class IconColor {
  light,
  dark
};

class Icon : public Gtk::Image {
public:
  Icon(string name, IconColor color = IconColor::light) {
    string path = "/icons/" + name + ".svg";
    this->set_from_resource(path);

    // auto filename = gio_file_new_for_uri()
    // auto bytes = Gio::Resource::lookup_data_global(path).get();
    // gsize size;
    // auto data = bytes->get_data(size);
    // printf("bytes: %s\n", filename);
    // this->set_from_resource("/icons/" + name + ".svg");
  }
};
