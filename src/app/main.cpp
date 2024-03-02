#include <fontconfig/fontconfig.h>
#include <gtkmm.h>
#include <pangomm.h>

#include "app/components/file-bar/file-bar.h"
// #include "app/components/image/image.h"
// #include "app/components/menu/file/file.h"
#include "main.h"

extern "C" {
#include "resources.h"
}

using namespace std;
using namespace rx;

class MainWindow : public Gtk::Window {
public:
  MainWindow() {
    set_title("Basic application");
    set_default_size(1024, 768);

    FileBar fileBar = FileBar();
    this->set_child(fileBar);
    this->set_expand(true);
  }
};

int main(int argc, char* argv[]) {
  Debug::setLogLevel(LogLevel::DEBUG);
  app_get_resource();

  auto app = Gtk::Application::create("com.example.draw");

  Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
  css->load_from_resource("/css/themes/dark.css");

  Gtk::StyleProvider::add_provider_for_display(Gdk::Display::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  return app->make_window_and_run<MainWindow>(argc, argv);

  // int status = 0;
  // try {
  //   auto resource = app_get_resource();
  //   auto app = Application::create(argc, argv, resource);

  //   app->startup([app]() {
  //     printf("startup\n");

  //     // Register the menu app menu items.
  //     auto gApp = app->instance->get();

  //     // Register the components.
  //     COMPONENT_REGISTER(DRAW_TYPE_IMAGE);
  //     COMPONENT_REGISTER(DRAW_TYPE_FILE_BAR);
  //   });

  //   status = app->run([app]() {
  //     printf("activate\n");

  //     auto mainWindow = app->mainWindow("/ui/main-window.ui", "/ui/main-menu.ui");

  //     mainWindow->onAfterWindowInit([](Window* window) {
  //       printf("after window init\n");

  //       // Register the menu window menu items.
  //       auto win = window->getWindow();
  //       WIN_COMPONENT_REGISTER(menu_file, win);
  //     });

  //     mainWindow->load();
  //   });
  // } catch (exception e) {
  //   cout << e.what() << endl;
  // }
}
