#include "app/components/image/image.h"
#include "app/global/subjects.h"
#include "file-bar.h"

struct _FileBar {
  GtkWindow parent;
  GtkNotebook* notebook;
};

G_DEFINE_FINAL_TYPE(FileBar, file_bar, GTK_TYPE_BOX)

static void onPageAdded(GtkNotebook* notebook, GtkImage* image) {
  auto app = Application::instance;
  auto size = app->fileSize();
  // gtk_notebook_set_current_page(notebook, size - 1);
}

void file_bar_ready(_FileBar* file_bar) {
  auto lambda = [file_bar](File* file) {
    auto app = Application::instance;
    auto label = gtk_label_new(file->getName().c_str());

    auto button = gtk_button_new();
    gtk_button_set_icon_name(GTK_BUTTON(button), "stock-close");

    auto box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), button);
    try {
      auto image = GTK_IMAGE(gtk_image_new());
      gtk_image_set_from_paintable(image, GDK_PAINTABLE(file->getTexture()));

      // gtk_notebook_append_page(file_bar->notebook, GTK_WIDGET(image), box);
    } catch (exception e) {
      cout << e.what() << endl;
    }
  };
  Subjects::fileAdded->subscribe(lambda);
}

COMPONENT_INIT(FileBar, file_bar, "/ui/components/file-bar/file-bar.component.ui", (notebook), (), (onPageAdded))
