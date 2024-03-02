// #include "gui/application.h"
// #include "gui/component/component.h"
// #include "window.h"

// GtkWindow *Window::getWindow() {
//   return window;
// }

// GtkWidget *Window::getWindowWidget() {
//   return windowWidget;
// }

// ComponentData *Window::getComponent(string id) {
//   auto component = new ComponentData(id, builder);
//   return component;
// }

// void Window::loadWindow() {
//   builder = gtk_builder_new_from_resource(resource.c_str());

//   if (beforeLoadCallback != nullptr)
//     this->beforeLoadCallback();

//   window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
//   applicationWindow = GTK_APPLICATION_WINDOW(window);
//   windowWidget = GTK_WIDGET(window);

//   if (afterWindowInit != nullptr)
//     this->afterWindowInit(this);

//   GMenuModel *menubar = nullptr;
//   GtkBuilder *menuBuilder = nullptr;
//   if (menuResource != "") {
//     menuBuilder = gtk_builder_new_from_resource(menuResource.c_str());
//     menubar = G_MENU_MODEL(gtk_builder_get_object(menuBuilder, "menubar"));
//     gtk_application_set_menubar(app, menubar);
//     gtk_application_window_set_show_menubar(applicationWindow, TRUE);
//     printf("loaded menu\n");
//   }

//   gtk_window_set_application(window, app);

//   if (menuBuilder != nullptr)
//     g_object_unref(menuBuilder);
// }

// void Window::loadStyles() {
//   display = gdk_display_get_default();
//   provider = gtk_css_provider_new();

//   gtk_css_provider_load_from_resource(provider, "/css/dark/theme.css");
//   gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

//   g_signal_connect(windowWidget, "destroy", G_CALLBACK(&Window::before_window_destroy), provider);
// }

// void Window::close() {
//   gtk_window_close(window);
// }

// void Window::before_window_destroy(GtkWidget *win, GtkCssProvider *provider) {
//   GdkDisplay *display = gdk_display_get_default();
//   gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(provider));
//   g_object_unref(provider);
// }

// void Window::onBeforeLoad(function<void()> callback) {
//   beforeLoadCallback = callback;
// }

// void Window::onAfterWindowInit(function<void(Window *)> callback) {
//   afterWindowInit = callback;
// }

// Window::Window(GtkApplication *app, string resource) {
//   this->app = app;
//   this->resource = resource;
// }

// Window::Window(GtkApplication *app, string resource, string menuResource) {
//   this->app = app;
//   this->resource = resource;
//   this->menuResource = menuResource;
// }

// void Window::load() {
//   // load the window
//   loadWindow();

//   // load the styles
//   loadStyles();

//   gtk_widget_set_visible(windowWidget, TRUE);
//   gtk_window_present(GTK_WINDOW(windowWidget));
// }
