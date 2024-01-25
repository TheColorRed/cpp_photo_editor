#pragma once

#include <gtk/gtk.h>

#include <functional>
#include <initializer_list>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef void (*CallbackType)();

class ComponentData;

struct ComponentTriggerEvent {
  string eventName;
  ComponentData *component;
  gulong id;
  function<void(ComponentData *)> callbackWithComponent;
  function<void()> callbackWithoutComponent;
};

struct ComponentDestroyEvent {
  ComponentData *component;
  map<string, vector<ComponentTriggerEvent *>> events;
};

class ComponentData {
protected:
  string tpl;
  GtkBuilder *builder;
  GObject *widget;

  // map<string, vector<gulong>> gtkEvents;
  map<string, vector<ComponentTriggerEvent *>> events;
  // map<string, vector<function<void(Component *)>>> events;
  // map<string, vector<function<void()>>> emptyEvents;

public:
  ComponentData(string tpl, GtkBuilder *builder);
  ~ComponentData();
  /**
   * Gets a child component of this component.
   */
  ComponentData *getComponent(string id);
  /**
   * Adds an event listener to this component.
   */
  ComponentData on(string event, function<void(ComponentData *)> callback);
  ComponentData on(string event, function<void()> callback);

private:
  static void trigger(GtkWidget *widget, ComponentTriggerEvent *event);
  static void onDestroy(GtkWidget *widget, ComponentDestroyEvent event);
};
