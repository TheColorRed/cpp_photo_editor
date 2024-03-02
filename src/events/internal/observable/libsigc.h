#pragma once

#include <gtkmm.h>

#include <functional>

#include "../../debug.h"
#include "../../events/event.h"
#include "../observable.h"
#include "../subscriber.h"

namespace rx {
  using namespace std;
  using namespace Gtk;
  using namespace Glib;

  template <typename T>
  class SignalEvent : public Event<T> {
  private:
    T _value;

  public:
    const T& value = _value;

    SignalEvent(T val) {
      this->_value = val;
    }
    virtual ~SignalEvent() {
      Debug::debug("SignalEvent::~SignalEvent");
    }
  };

  /**
   * Creates an Observable from a raw pointer widget.
   * @param widget The widget that will emit the signal.
   * @param sig The signal to listen to.
   * @example
   * auto button = new Button();
   * auto observable = fromSignal(button, &Button::signal_clicked);
   */
  template <typename T>
  Observable<SignalEvent<T*>*>* fromSignal(T* widget, SignalProxy<void()> (T::*sig)()) {
    return new Observable<SignalEvent<T*>*>([widget, sig](Subscriber<SignalEvent<T*>*>* subscriber) -> optional<TeardownLogic> {
      Debug::debug("fromSignal -> connect signal");
      auto conn = invoke(sig, widget).connect([widget, subscriber]() mutable {
        Debug::debug("fromSignal -> next");
        SignalEvent<T*>* signalEvent = new SignalEvent<T*>(widget);
        subscriber->next(signalEvent);
      });
      subscriber->add([conn]() mutable -> optional<TeardownLogic> {
        Debug::debug("fromSignal -> teardown");
        conn.disconnect();
        return nullopt;
      });
      return nullopt;
    });
  }
}
