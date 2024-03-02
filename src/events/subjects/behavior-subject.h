#pragma once

#include <functional>

#include "subject.h"

namespace rx {
  template <typename T>
  class Subject;

  template <typename T>
  class BehaviorSubject : public Subject<T> {
  private:
    Next<T> value;

  public:
    BehaviorSubject(Next<T> value) {
      this->value = value;
    }
    NextFn<T> next = [this](Next<T> value = nullptr) {
      this->value = value;
      Subject<T>::next(value);
    };
    /**
     * Subscribe to the BehaviorSubject.
     * On initial subscription, the callback will be called with the current value of the BehaviorSubject.
     */
    Subscription* subscribe(function<void(T)> callback) {
      return Subject<T>::subscribe([callback, this]() {
        callback(this->value);
      });
    }
    T getValue() {
      return value;
    }
  };
}
