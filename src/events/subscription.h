#pragma once

#include <functional>
#include <map>
#include <variant>
#include <vector>

#include "events.h"

using namespace std;

template <typename T>
class Subscription {
private:
  vector<TeardownLogic<T>> finalizers = vector<TeardownLogic<T>>();

public:
  bool closed = false;

  Subscription() {}
  Subscription(TeardownLogic<T> callback) {
    this->add(callback);
  }
  void add(TeardownLogic<T> teardownLogic) {
    if (closed) {
      this->teardown();
    } else {
      finalizers.push_back(teardownLogic);
    }
  }
  void unsubscribe() {
    if (!closed) {
      closed = true;
      this->teardown();
    }
  }

private:
  void teardown() {
    for (auto finalizer : finalizers) {
      // auto idx = finalizer.index();
      // if (idx == 0)
      //   get<function<void()>>(finalizer)();
      // else if (idx == 1)
      //   get<function<void(T)>>(finalizer)(nullptr);
      // else if (idx == 2)
      //   get<Subscription<T>>(finalizer).unsubscribe();
    }
  }
};
