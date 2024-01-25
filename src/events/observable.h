#pragma once

#include <array>
#include <string>
#include <vector>

#include "events.h"

using namespace std;

template <typename T>
class Observable {
protected:
  vector<T> values = vector<T>();

  virtual TeardownLogic<T> _subscribe(shared_ptr<Subscriber<T>> subscriber) {
    printf("Observable::_subscribe\n");
    return []() {};
  };

public:
  Observable() {}
  Observable(function<void(Subscriber<T>)> subscribe) {
    this->_subscribe = subscribe;
  }
  shared_ptr<Subscription<T>> subscribe(ObserverOrNext<T> observerOrNext) {
    shared_ptr<Subscriber<T>> subscriber;
    try {
      subscriber = get<shared_ptr<Subscriber<T>>>(observerOrNext);
      printf("Observable::subscribe with Subscriber\n");
    } catch (const exception& e) {
      subscriber = shared_ptr<Subscriber<T>>(new Subscriber<T>(observerOrNext));
      printf("Observable::subscribe with Observer\n");
    }

    subscriber->add(this->_subscribe(subscriber));
    return subscriber;
  }
  void complete() {
    // for (auto value : *values) {
    //   subscriber(value);
    // }
  }
};
