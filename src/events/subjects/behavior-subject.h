#pragma once

#include "../events.h"

template <typename T>
class Subject;

template <typename T>
class BehaviorSubject : public Subject<T> {
private:
  T value;

public:
  BehaviorSubject(T value) {
    this->value = value;
  }
  void next(T value) override {
    this->value = value;
    Observable<T>::next();
  }
  void subscribe(function<void(T)> callback) {
    Subject<T>::subscribe([callback, this]() {
      callback(this->value);
    });
  }
  T getValue() {
    return value;
  }
};
