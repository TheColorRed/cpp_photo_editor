#pragma once

#include <functional>
#include <vector>

#include "../debug.h"
#include "../internal/observable.h"
#include "../internal/observer.h"
#include "../internal/subscriber.h"

namespace rx {
  template <typename T>
  class Observable;

  template <typename T>
  class Subject : public Observable<T> {
    using CurrentObservers = vector<Observer<T>*>;

  private:
    CurrentObservers* currentObservers = CurrentObservers();
    bool closed = false;

  protected:
    TeardownLogic _subscribe(Subscriber<T>* subscriber) override {
      Debug::debug("Subject::_subscribe");
      this->currentObservers.push_back(subscriber);
      return subscriber;
    }

  public:
    NextFn<T> next = [this](Next<T> value = monostate()) {
      if (this->closed)
        return;

      auto observers = this->currentObservers.get();
      for (int i = 0; i < observers->size(); i++) {
        auto observer = observers->at(i);
        observer->next(value);
      }
    };

    ErrorFn error = [this](any err) {
      if (this->closed)
        return;

      for (auto observer : currentObservers)
        observer.error(err);

      this->currentObservers.clear();
    };

    CompleteFn complete = [this]() {
      if (this->closed)
        return;

      for (auto observer : currentObservers)
        observer.complete();

      this->currentObservers.clear();
    };

    UnsubscribeFn unsubscribe = [this]() {
      this->closed = true;
      this->currentObservers.clear();
    };

    Observable<T>* asObservable() {
      return new Observable<T>(new Observable<T>([this](Subscriber<T> subscriber) {
        return this->subscribe(subscriber);
      }));
    }
  };
}
