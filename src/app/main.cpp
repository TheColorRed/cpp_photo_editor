#include <iostream>

#include "app/components/file-bar/file-bar.h"
#include "app/components/image/image.h"
#include "app/components/menu/file/file.h"
#include "gui/gui.h"
#include "main.h"

extern "C" {
#include "resources.h"
}

using namespace std;

int main(int argc, char* argv[]) {
  int status = 0;
  try {
    auto resource = app_get_resource();
    auto app = Application::create(argc, argv, resource);

    app->startup([app]() {
      printf("startup\n");

      // Register the menu app menu items.
      auto gApp = app->instance->get();

      // Register the components.
      COMPONENT_REGISTER(DRAW_TYPE_IMAGE);
      COMPONENT_REGISTER(DRAW_TYPE_FILE_BAR);
    });

    status = app->run([app]() {
      printf("activate\n");

      auto mainWindow = app->mainWindow("/ui/main-window.ui", "/ui/main-menu.ui");

      mainWindow->onAfterWindowInit([](Window* window) {
        printf("after window init\n");

        // Register the menu window menu items.
        auto win = window->getWindow();
        WIN_COMPONENT_REGISTER(menu_file, win);
      });

      mainWindow->load();
    });
  } catch (exception e) {
    cout << e.what() << endl;
  }
}
