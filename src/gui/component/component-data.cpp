#include "component-data.h"

ComponentData::ComponentData(string id, GtkBuilder *builder) {
  this->tpl = id;
  this->builder = builder;
  this->widget = gtk_builder_get_object(builder, id.c_str());

  auto event = new ComponentDestroyEvent();
  event->component = this;
  event->events = events;

  g_signal_connect(widget, "destroy", G_CALLBACK(ComponentData::onDestroy), event);
}

void ComponentData::onDestroy(GtkWidget *widget, ComponentDestroyEvent event) {
  printf("Destroying component %s\n", event.component->tpl.c_str());
  for (auto event : event.events) {
    for (auto evt : event.second) {
      printf("Disconnecting event %s\n", event.first.c_str());
      g_signal_handler_disconnect(widget, evt->id);
    }
  }
}

ComponentData::~ComponentData() {
  // for (auto event : events) {
  //   for (auto id : event.second) {
  //     printf("Disconnecting event %s\n", event.first.c_str());
  //     g_signal_handler_disconnect(widget, id);
  //   }
  // }
}

ComponentData *ComponentData::getComponent(string id) {
  auto component = new ComponentData(id, builder);
  return component;
}

ComponentData ComponentData::on(string event, function<void()> callback) {
  auto evt = new ComponentTriggerEvent();

  GCallback func = G_CALLBACK(ComponentData::trigger);
  auto id = g_signal_connect(widget, event.c_str(), func, evt);

  evt->id = id;
  evt->eventName = event;
  evt->component = this;
  evt->callbackWithoutComponent = callback;
  events[event].push_back(evt);

  return *this;
}

ComponentData ComponentData::on(string event, function<void(ComponentData *)> callback) {
  auto evt = new ComponentTriggerEvent();
  GCallback func = G_CALLBACK(ComponentData::trigger);
  auto id = g_signal_connect(widget, event.c_str(), func, evt);

  evt->id = id;
  evt->eventName = event;
  evt->component = this;
  evt->callbackWithComponent = callback;
  events[event].push_back(evt);

  return *this;
}

void ComponentData::trigger(GtkWidget *widget, ComponentTriggerEvent *event) {
  auto paramEvents = event->component->events[event->eventName];
  for (auto evt : paramEvents) {
    if (evt->callbackWithComponent != nullptr)
      evt->callbackWithComponent(evt->component);
    else
      evt->callbackWithoutComponent();
  }
}
