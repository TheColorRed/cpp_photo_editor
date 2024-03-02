#pragma once

#include <functional>
#include <iostream>

#include "../debug.h"
#include "../types.h"
#include "consumer-observer.h"
#include "observer.h"
#include "subscription.h"
#include "unsubscribable.h"

namespace rx {
  template <typename T>
  class Subscriber : public Subscription, public Observer<T> {
  protected:
    bool isStopped = false;

  private:
    Observer<T> *destination;

    optional<NextFn<T>> _nextOverride;
    optional<ErrorFn> _errorOverride;
    optional<CompleteFn> _completeOverride;
    optional<FinalizeFn> _onFinalize;

    NextFn<T> _next = [this](Next<T> value) {
      try {
        if (ConsumerObserver<T> *consumer = dynamic_cast<ConsumerObserver<T> *>(this->destination)) {
          Debug::debug("Subscriber::_next -> using ConsumerObserver");
          callNextOperation(consumer->next, value);
        } else {
          NextFn<T> next = this->destination->next.value();
          callNextOperation(next, value);
        }
        Debug::debug("Subscriber::_next -> next");
      } catch (const exception &e) {
        Debug::debug("Subscriber::_next -> no destination defined");
      }
    };

    ErrorFn _error = [this](auto err) {
      try {
        this->destination->error.value()(err);
      } catch (const exception &e) {
        this->unsubscribe();
      }
    };

    CompleteFn _complete = [this]() {
      try {
        this->destination->complete.value()();
      } catch (const exception &e) {
        this->unsubscribe();
      }
    };

  public:
    Subscriber(ObserverOrNext<T> dest = monostate(), SubscriberOverrides<T> overrides = {}) {
      try {
        this->destination = get<Subscriber<T> *>(dest);
        Debug::debug("Subscriber -> using existing Subscriber");
      } catch (const exception &e) {
        this->destination = createSafeObserver<T>(dest);
        Debug::debug("Subscriber -> created new safe Observer");
      }

      // Set the overrides if they exist
      this->_nextOverride = overrides.next ?: nullopt;
      this->_errorOverride = overrides.error ?: nullptr;
      this->_completeOverride = overrides.complete ?: nullptr;
      this->_onFinalize = overrides.finalize ?: nullptr;

      // If there are overrides, set the callbacks to the override functions
      // otherwise, set the callbacks to the default functions.
      this->_next = this->_nextOverride ? this->overrideNext : this->_next;
      this->_error = this->_errorOverride ? this->overrideError : this->_error;
      this->_complete = this->_completeOverride ? this->overrideComplete : this->_complete;

      if (holds_alternative<Subscriber<T> *>(dest)) {
        Subscriber<T> *subscriber = get<Subscriber<T> *>(dest);
        if (Subscription *subscription = dynamic_cast<Subscription *>(subscriber)) {
          subscription->add(this);
        }
      }
    }

    NextFn<T> next = [this](Next<T> value) {
      if (this->isStopped)
        return;

      callNextOperation(this->_next, value);
    };

    ErrorFn error = [this](any err = NULL) {
      if (this->isStopped)
        return;
      this->isStopped = true;
      this->_error(err);
    };

    CompleteFn complete = [this]() {
      if (this->isStopped)
        return;
      this->isStopped = true;
      this->_complete();
    };

    UnsubscribeFn unsubscribe = [this]() {
      if (!this->closed) {
        this->isStopped = true;
        Subscription::unsubscribe();
        if (this->_onFinalize.has_value()) {
          this->_onFinalize.value()();
        }
      }
    };

  private:
    /**
     * The function to call when an override is set for the next function.
     */
    NextFn<T> overrideNext = [this](Next<T> value) {
      try {
        callNextOperation(this->_nextOverride.value(), value);
        Debug::debug("Subscriber::overrideNext -> next");
      } catch (const exception &e) {
        this->destination->error.value()(e);
        Debug::debug("Subscriber::overrideNext -> error");
      }
    };

    /**
     * The function to call when an override is set for the error function.
     */
    ErrorFn overrideError = [this](any err) {
      try {
        this->_errorOverride.value()(err);
      } catch (const exception &e) {
        this->destination->error.value()(e);
      }
      this->unsubscribe();
    };
    /**
     * The function to call when an override is set for the complete function.
     */
    CompleteFn overrideComplete = [this]() {
      try {
        this->_completeOverride.value()();
      } catch (const exception &e) {
        this->destination->error.value()(e);
      }
      this->unsubscribe();
    };
  };

  template <typename T>
  ConsumerObserver<T> *createSafeObserver(ObserverOrNext<T> observerOrNext) {
    Observer<T> *observer;
    try {
      observer = get<Observer<T> *>(observerOrNext);
      Debug::debug("createSafeObserver -> using existing Observer");
    } catch (const exception &e) {
      NextFn<T> next = []() {
        Debug::debug("createSafeObserver -> empty next function");
      };
      try {
        next = get<NextFn<T>>(observerOrNext);
        Debug::debug("createSafeObserver -> using next function");
      } catch (const exception &e) {
        Debug::debug("createSafeObserver -> no next function");
      }
      observer = new Observer<T>();
      observer->next = next;
    }
    Debug::debug("createSafeObserver -> returning consumer observer");
    return new ConsumerObserver<T>(observer);
  }
}
