#pragma once

#include <gtk/gtk.h>

#include <cstddef>
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <type_traits>
#include <vector>

#include "app/macros/args.h"
#include "app/macros/foreach-component.h"

using namespace std;

#define BIND_CHILD(WIDGET_NAME, PREFIX, ARG) \
  printf("BIND_CHILD(): %s\n", #ARG);        \
  gtk_widget_class_bind_template_child(widget_class, WIDGET_NAME, ARG);

#define BIND_CALLBACK(WIDGET_NAME, PREFIX, ARG) \
  printf("BIND_CALLBACK(): %s\n", #ARG);        \
  gtk_widget_class_bind_template_callback(widget_class, ARG);

#define PROP(WIDGET_NAME, PREFIX, ARG)                \
  printf("PROP(): %s\n", #ARG);                       \
  object_class->set_property = PREFIX##_set_property; \
  object_class->get_property = PREFIX##_get_property; \
  g_object_class_install_property(object_class, 1, g_param_spec_string(#ARG, #ARG, #ARG, "", G_PARAM_READWRITE));

#define PROP_FUNC(WIDGET_NAME, PREFIX, ARG)                                                                       \
  static void PREFIX##_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec) { \
    WIDGET_NAME* self = (WIDGET_NAME*)object;                                                                     \
    printf("Setting property: %s to %s\n", #ARG, g_value_get_string(value));                                      \
    self->ARG = (char*)g_value_get_string(value);                                                                 \
  }                                                                                                               \
  static void PREFIX##_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec) {       \
    WIDGET_NAME* self = (WIDGET_NAME*)object;                                                                     \
    printf("Getting property: %s as %s\n", #ARG, self->ARG);                                                      \
    g_value_set_string(value, self->ARG);                                                                         \
  }

#define COMPONENT_INIT(WIDGET_NAME, PREFIX, TPL_RESOURCE, BINDINGS, PROPS, CALLBACKS) \
  FOREACH_COMPONENT(PROP_FUNC, WIDGET_NAME, PREFIX, ARGS PROPS)                       \
  static void PREFIX##_dispose(GObject* object) {                                     \
    printf("Running: %s_dispose(GObject* object)\n", #PREFIX);                        \
    gtk_widget_dispose_template(GTK_WIDGET(object), PREFIX##_get_type());             \
    G_OBJECT_CLASS(PREFIX##_parent_class)->dispose(object);                           \
  }                                                                                   \
  static void PREFIX##_init(WIDGET_NAME* self) {                                      \
    printf("Running: %s_init(%s* self)\n", #PREFIX, #WIDGET_NAME);                    \
    gtk_widget_init_template(GTK_WIDGET(self));                                       \
    if (PREFIX##_ready) {                                                             \
      PREFIX##_ready(self);                                                           \
    }                                                                                 \
  }                                                                                   \
  static void PREFIX##_class_init(WIDGET_NAME##Class* klass) {                        \
    printf("Running: %s_class_init(%sClass* klass)\n", #PREFIX, #WIDGET_NAME);        \
    G_OBJECT_CLASS(klass)->dispose = PREFIX##_dispose;                                \
    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);                           \
    GObjectClass* object_class = G_OBJECT_CLASS(klass);                               \
    string tpl(TPL_RESOURCE);                                                         \
    if (tpl.size() > 0)                                                               \
      gtk_widget_class_set_template_from_resource(widget_class, tpl.c_str());         \
    FOREACH_COMPONENT(BIND_CHILD, WIDGET_NAME, PREFIX, ARGS BINDINGS)                 \
    FOREACH_COMPONENT(PROP, WIDGET_NAME, PREFIX, ARGS PROPS)                          \
    FOREACH_COMPONENT(BIND_CALLBACK, WIDGET_NAME, PREFIX, ARGS CALLBACKS)             \
  }

#define COMPONENT_H(WIDGET_NAME, PREFIX) \
  void PREFIX##_ready(WIDGET_NAME* self) __attribute__((weak));

#define COMPONENT_REGISTER(VALUE)      \
  printf("Ensure Type: %s\n", #VALUE); \
  g_type_ensure(VALUE);

struct ComponentDeclaration {
  string name;
  gssize member_name;
  string templatePath;
  string cssPath;
};

class Component {
public:
  void registerComponent(GtkWidgetClass*) {}
  virtual GtkWidget* getType() = 0;

  inline static vector<ComponentDeclaration>
      components;

  template <typename T>
  static optional<ComponentDeclaration> get() {
    auto component = T();
    for (auto declaration : components) {
      if (declaration.templatePath == component.tpl) {
        return declaration;
      }
    }
    return nullopt;
  }

  static optional<ComponentDeclaration> get(string templatePath) {
    for (auto declaration : components) {
      if (declaration.templatePath == templatePath) {
        return declaration;
      }
    }
    return nullopt;
  }

  template <typename T, typename enable_if<is_base_of<Component, T>::value>::type* = nullptr>
  static void declare() {
    // unique_ptr<T> component(new T());
    // component->getType();
    // auto type = draw_image_get_type();
    // auto w = "hi";
    // GTK_WIDGET(g_object_new(draw_image_get_type(), NULL));

    // ComponentDeclaration declaration;
    // declaration.templatePath = T::tpl;
    // declaration.cssPath = T::css;
    // declaration.name = T::name;
    // declaration.member_name = T::member_name;
    // // declaration.name = regex_replace(typeid(T).name(), regex("^\\d+"), "");
    // // Component::initSelf(declaration);
    // auto type = component->getType();
    // if (type.has_value()) {
    //   component->registerComponent(type.value());
    // }
    // Component::components.push_back(declaration);
  }

  Component() {
    printf("Component constructor\n");
  }

protected:
  void initBindings(GtkWidgetClass* widget_class, string name, gssize member_name);
};
