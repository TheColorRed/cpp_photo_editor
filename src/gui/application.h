#pragma once

#include <gtk/gtk.h>

#include <functional>
#include <string>
#include <type_traits>

#include "app/classes/file.h"
#include "window/main-window.h"

using namespace std;

class Component;
class File;

#define APP_COMPONENT_REGISTER(PREFIX, APP) \
  if (PREFIX##_app_startup)                 \
    PREFIX##_app_startup(APP);

#define WIN_COMPONENT_REGISTER(PREFIX, WIN) \
  if (PREFIX##_win_startup)                 \
    PREFIX##_win_startup(WIN);

#define APP_MENU_ENTRIES(SOURCE, ENTRIES) \
  g_action_map_add_action_entries(G_ACTION_MAP(SOURCE), ENTRIES, G_N_ELEMENTS(ENTRIES), SOURCE)

class Application {
public:
  static Application *instance;

private:
  /**
   * The files that are currently open.
   */
  vector<File *> *files = new vector<File *>();
  function<void()> activateCallback;
  function<void()> startupCallback;
  vector<function<void(vector<File *>)>> filesChanged = vector<function<void(vector<File *>)>>();
  GtkApplication *app;
  int argc;
  char **argv;
  GResource *resource;

  Application(int argc, char *argv[], GResource *resource) {
    this->resource = resource;
    this->argc = argc;
    this->argv = argv;
    app = gtk_application_new("com.example.draw", G_APPLICATION_DEFAULT_FLAGS);
  }

public:
  /**
   * The number of files that are currently open.
   */
  int fileSize() {
    return files->size();
  }
  /**
   * Adds a file to the files vector.
   * @param file The file to add.
   */
  void addFile(File *file) {
    this->files->push_back(file);
  }
  /**
   * Removes the specified file from the files vector.
   * @param file The file to remove.
   */
  void removeFile(File *file) {
    this->files->erase(remove(this->files->begin(), this->files->end(), file), this->files->end());
    for (auto callback : filesChanged)
      callback(*files);
  }
  /**
   * Removes a file from the files vector at the specified index.
   * @param index The index of the file to remove.
   */
  void removeFile(int index) {
    this->files->erase(this->files->begin() + index);
    for (auto callback : filesChanged)
      callback(*files);
  }
  /**
   * Adds a callback that is called when the files vector changes.
   */
  void onFilesChanged(function<void(vector<File *>)> callback) {
    filesChanged.push_back(callback);
  }
  /**
   * Removes a callback that is called when the files vector changes.
   */
  void offFilesChanged(function<void(vector<File *>)> callback) {
    // filesChanged.erase(remove(filesChanged.begin(), filesChanged.end(), callback), filesChanged.end());
  }
  /**
   * Gets the Gtk application instance.
   */
  GApplication *get() {
    return G_APPLICATION(app);
  }
  static Application *create(int argc, char *argv[], GResource *resource);
  /**
   * Runs the application.
   * @param callback The callback that is called when Gtk activate signal is emitted.
   */
  int run(function<void()> callback);
  /**
   * Sets the callback that is called when Gtk startup signal is emitted.
   * @param callback The callback that is called when Gtk startup signal is emitted.
   */
  void startup(function<void()> callback);
  /**
   * Creates or gets the main window.
   * @param resource The path to the resource.
   */
  MainWindow *mainWindow(string resource, string menuResource) {
    return MainWindow::create(app, resource, menuResource);
  }
  /**
   * Executes the activate callback when Gtk activate signal is emitted.
   * @param app The Gtk application instance.
   * @param self The application instance.
   */
  static void activate_callback(GtkApplication *app, Application *self) {
    if (self->activateCallback != nullptr)
      self->activateCallback();
  }
  /**
   * Executes the startup callback when Gtk startup signal is emitted.
   * @param app The Gtk application instance.
   * @param self The application instance.
   */
  static void startup_callback(GtkApplication *app, Application *self) {
    if (self->startupCallback != nullptr)
      self->startupCallback();
  }
  /**
   * Gets resources from the resource file using the file name and starting path.
   */
  vector<string> *get_resource_files(const string &file_name, string path, vector<string> *files) {
    auto result = g_resource_enumerate_children(resource, path.c_str(), G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);

    if (result != nullptr) {
      for (int i = 0; result[i]; i++) {
        string file_path(result[i]);
        file_path = path + file_path;

        if (file_path.ends_with("/")) {
          get_resource_files(file_name, file_path, files);
        } else if (file_path.ends_with(file_name)) {
          files->push_back(file_path);
        }
      }
    }

    return files;
  }
};
