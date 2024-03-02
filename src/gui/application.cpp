// #include "application.h"

// Application *Application::instance = nullptr;

// Application *Application::create(int argc, char *argv[], GResource *resource) {
//   if (Application::instance == nullptr) {
//     Application::instance = new Application(argc, argv, resource);
//   }
//   return Application::instance;
// }

// void Application::startup(function<void()> callback) {
//   this->startupCallback = callback;
//   g_signal_connect(app, "startup", G_CALLBACK(Application::startup_callback), this);
// }

// int Application::run(function<void()> callback) {
//   this->activateCallback = callback;
//   g_signal_connect(app, "activate", G_CALLBACK(Application::activate_callback), this);
//   g_setenv("GTK_CSD", "0", FALSE);

//   g_resources_register(resource);

//   printf("Running application: g_application_run\n");
//   return g_application_run(G_APPLICATION(app), argc, argv);
// }

// void declarations(vector<Component> components) {
//   // Application::declaredComponents = components;
//   // for (auto component : components) {
//   //   Application::declaredComponents.push_back(component);
//   // }
// }
