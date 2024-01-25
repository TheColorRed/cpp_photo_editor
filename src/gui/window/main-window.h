#pragma once

#include <gtk/gtk.h>

#include "window.h"

class MainWindow : public Window {
public:
  static MainWindow *instance;
  static MainWindow *create(GtkApplication *app, string resource, string menuResource);

private:
  MainWindow(GtkApplication *app, string resource, string menuResource);
  static void shutdown(GtkApplication *app) {
    auto g_app = g_application_get_default();
    g_application_quit(g_app);
  }
};
