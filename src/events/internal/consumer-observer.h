#pragma once

#include <any>

#include "observable.h"
#include "observer.h"

using namespace std;

namespace rx {
  template <typename T>
  class ConsumerObserver : public Observer<T> {
  private:
    Observer<T> *partialObserver;

  public:
    ConsumerObserver(Observer<T> *partialObserver) {
      this->partialObserver = partialObserver;
      Debug::debug("ConsumerObserver::ConsumerObserver");
    }

    ~ConsumerObserver() {
      Debug::debug("ConsumerObserver::~ConsumerObserver");
      delete this->partialObserver;
    }

    NextFn<T> next = [this](Next<T> value) {
      try {
        NextFn<T> next = this->partialObserver->next.value();
        callNextOperation(next, value);
        Debug::debug("ConsumerObserver::next -> next");
      } catch (const exception &error) {
        Debug::debug("ConsumerObserver::next -> no next operation defined");
      }
    };

    ErrorFn error = [this](any err) {
      if (this->partialObserver->error) {
        try {
          partialObserver->error.value()(err);
        } catch (const exception &error) {
          // reportUnhandledError(error);
        }
      } else {
        // reportUnhandledError(err);
      }
    };

    CompleteFn complete = [this]() {
      if (this->partialObserver->complete) {
        try {
          this->partialObserver->complete.value()();
        } catch (const exception &error) {
          // reportUnhandledError(error);
        }
      }
    };
  };
}
