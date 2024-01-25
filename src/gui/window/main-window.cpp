#include "main-window.h"

MainWindow *MainWindow::instance = nullptr;

MainWindow *MainWindow::create(GtkApplication *app, string resource, string menuResource) {
  if (MainWindow::instance == nullptr) {
    MainWindow::instance = new MainWindow(app, resource, menuResource);
  }
  return MainWindow::instance;
}

MainWindow::MainWindow(GtkApplication *app, string resource, string menuResource) : Window(app, resource, menuResource) {
  // g_signal_connect(windowWidget, "destroy", G_CALLBACK(&MainWindow::shutdown), NULL);
}
