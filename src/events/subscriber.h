#pragma once

#include "events.h"

template <typename T>
class Subscriber : public Subscription<T>, public Observer<T> {
private:
  Callable<T> _next = []() {};

public:
  Subscriber(ObserverOrNext<T> destination) {
    try {
      this->_next = get<function<void(T)>>(destination);
      printf("Subscriber::Subscriber with value\n");
    } catch (const exception& e) {
      try {
        this->_next = get<function<void()>>(destination);
        printf("Subscriber::Subscriber with no value\n");
      } catch (const exception& e) {
        throw e;
      }
    }
  }

  void next() override {
    printf("Subscriber::next\n");
    if (this->closed)
      return;

    try {
      get<function<void()>>(this->_next)();
    } catch (const exception& e) {
      throw e;
    }
  }

  void next(T value) override {
    printf("Subscriber::next %s\n", value);
    if (this->closed)
      return;
    try {
      get<function<void(T)>>(this->_next)(value);
    } catch (const exception& e) {
      throw e;
    }
  }
};
