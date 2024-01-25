#include <bits/stdc++.h>

#include "app/global/subjects.h"
#include "app/macros/args.h"
#include "app/macros/foreach.h"
#include "file.h"

#define F(ARG)                                              \
  filter = gtk_file_filter_new();                           \
  gtk_file_filter_add_pattern(filter, FIRST_ARG(ARGS ARG)); \
  gtk_file_filter_set_name(filter, LAST_ARG(ARGS ARG));     \
  g_list_store_append(filters, filter);

#define FILE_FILTER(...) \
  FOREACH(F, ##__VA_ARGS__)

static void new_activated(GSimpleAction *action, GVariant *parameter, gpointer data) {
  printf("new\n");
}

static void open_accept(GObject *source_object, GAsyncResult *res, gpointer data) {
  GtkFileDialog *dialog = GTK_FILE_DIALOG(source_object);
  GFile *sourceFile = gtk_file_dialog_open_finish(dialog, res, NULL);
  if (sourceFile == NULL)
    return;

  // A file was opened.

  string path(g_file_get_path(sourceFile));
  auto file = File::create(path);
  Application::instance->addFile(file);
  Subjects::fileAdded->next(file);
}

static void open_activated(GSimpleAction *action, GVariant *parameter, gpointer data) {
  auto win = GTK_WINDOW(data);
  auto dialog = gtk_file_dialog_new();
  auto filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
  GtkFileFilter *filter = nullptr;

  FILE_FILTER(
      ("*", "All Formats"),
      ("*.jpg", "JPEG"),
      ("*.png", "PNG"),
      ("*.bmp", "BMP"));

  // Set dialog settings.
  gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));
  gtk_file_dialog_set_title(dialog, "Open Image");

  // Open the dialog.
  gtk_file_dialog_open(dialog, win, NULL, open_accept, data);
  g_object_unref(filters);
  g_object_unref(dialog);
}

void menu_file_win_startup(GtkWindow *win) {
  printf("setting up file menu\n");
  const GActionEntry menu_file_entries[] = {
      {"new", new_activated, NULL, NULL, NULL},
      {"open", open_activated, NULL, NULL, NULL},
  };
  g_action_map_add_action_entries(G_ACTION_MAP(win), menu_file_entries, G_N_ELEMENTS(menu_file_entries), win);
  // APP_MENU_ENTRIES(app, menu_file_entries);
}

GdkTexture *File::getTexture() {
  auto image = this->image;
  auto buffer = *image->getBuffer().get();
  auto size = buffer.size();
  guchar *data = &buffer[0];
  // unique_ptr<guchar> data(new guchar[size]);
  // for (int i = 0; i < size; i++) {
  //   data.get()[i] = buffer->at(i);
  // }
  // auto data = reinterpret_cast<uint8_t *>(&buffer);
  // copy(buffer->begin(), buffer->end(), data);
  // guchar *data = image->getBuffer().get();
  auto pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, true, 8, image->width, image->height);
  try {
    pixbuf = gdk_pixbuf_new_from_data(
        data,
        GDK_COLORSPACE_RGB,
        true, 8,
        this->image->width,
        this->image->height,
        this->image->width * 4,
        nullptr,
        nullptr);
  } catch (exception e) {
    cout << e.what() << endl;
  }
  return gdk_texture_new_for_pixbuf(pixbuf);
}
