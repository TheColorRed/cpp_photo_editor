#pragma once

#include <gtkmm.h>

#include <iostream>
#include <string>

#include "app/classes/icon.h"
#include "events/internal/observable/libsigc.h"
#include "events/operators/finalize.h"
#include "events/operators/map.h"
#include "events/operators/take.h"
#include "events/operators/tap.h"

using namespace std;
using namespace rx;
// using namespace sigc;
using namespace Gtk;

class FileBarLabel : public Box {
private:
  Subscription* sub;

public:
  FileBarLabel(string text, Notebook* notebook, Button* page) {
    this->set_orientation(Orientation::HORIZONTAL);
    this->set_hexpand(false);

    // The label for the notebook tab.
    Label label = Label(text);
    // The button to close the notebook tab.
    auto button = new Button();
    auto icon = new Icon("xmark");
    icon->set_hexpand(false);
    button->set_hexpand(false);
    button->set_child(*icon);

    using ButtonEvent = SignalEvent<Gtk::Button*>*;

    // Connect the button to the close function.
    auto click = fromSignal<Button>(button, &Button::signal_clicked);

    auto observer = click->pipe(
      // tap<ButtonEvent>([](auto value) {
      //   Debug::info("tap click");
      // }),
      // tap<ButtonEvent>([](auto value) {
      //   Debug::info("tap click");
      // })
      // rx::map<ButtonEvent, int>([](auto value) {
      //   return 123;
      // })
      // rx::finalize<ButtonEvent>([]() {
      //   Debug::info("finalize click");
      // })
      rx::take<ButtonEvent>(2)
    );

    sub = observer->subscribe([notebook, page, click]() {
      Debug::info("subscribe click");
      // notebook->remove_page(*page);
    });

    // Add the label and button to the notebook tab.
    this->append(label);
    this->append(*button);
  }
};
