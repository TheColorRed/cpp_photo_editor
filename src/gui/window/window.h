// #pragma once

// #include <gtk/gtk.h>

// #include <functional>
// #include <string>

// #include "gui/component/component-data.h"

// using namespace std;

// class Window {
// protected:
//   GtkApplication *app;
//   string resource;
//   string menuResource;

//   GtkWindow *window;
//   GtkApplicationWindow *applicationWindow;

//   GtkBuilder *builder;
//   GtkWidget *windowWidget;

//   GdkDisplay *display;
//   GtkCssProvider *provider;

//   function<void()> beforeLoadCallback;
//   function<void(Window *)> afterWindowInit;

// protected:
//   /**
//  * Create a new window.
//  * @param app The application.
//  * @param resource The resource file for the window.
//  */
//   Window(GtkApplication *app, string resource);
//   /**
//    * Create a new window.
//    * @param app The application.
//    * @param resource The resource file for the window.
//    * @param menuResource The resource file for the menu.
//    */
//   Window(GtkApplication *app, string resource, string menuResource);
//   /**
//    * Load the window from the resource file.
//   */
//   void loadWindow();
//   /**
//    * Load the styles from the resource file.
//    */
//   void loadStyles();

//   static void before_window_destroy(GtkWidget *win, GtkCssProvider *provider);

// public:
//   /**
//    * Get the window.
//   */
//   GtkWindow *getWindow();
//   /**
//    * Get the window widget.
//    */
//   GtkWidget *getWindowWidget();
//   /**
//    * Get a widget by its id.
//    */
//   ComponentData *getComponent(string id);
//   /**
//    * Close the window.
//    */
//   void close();
//   /**
//    * Set the callback that is called before the window is loaded.
//    */
//   void onBeforeLoad(function<void()> callback);
//   /**
//    * Set the callback that is called after the window is initialized.
//    */
//   void onAfterWindowInit(function<void(Window *)> callback);
//   /**
//    * Load the window.
//    */
//   void load();
// };
