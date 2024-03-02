#pragma once

#include <functional>

#include "../types.h"

namespace rx {

  using namespace std;

  template <typename T>
  MonoTypeOperatorFunction<T> finalize(function<void()> callback) {
    return [callback](auto source) -> Observable<T>* {
      return new Observable<T>([source, callback](auto subscriber) -> optional<TeardownLogic> {
        source->subscribe(subscriber);
        subscriber->add(callback);
        return nullopt;
      });
    };
  }
}
