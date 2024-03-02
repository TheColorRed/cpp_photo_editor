#pragma once

#include "../observable.h"

using namespace std;

namespace rx {
  /**
   * Emits a value after a specified delay, and then emits another value every specified period.
   * @param delay The initial delay before emitting the first value, in milliseconds.
   * @param interval The period to wait between emitting subsequent values, in milliseconds.
   */
  template <typename T>
  Observable<T>* timer(int delay, int interval) {
    return new Observable<T>([widget, sig](Subscriber<T>* subscriber) -> optional<TeardownLogic> {
      int c = 0;

      return nullopt;
    });
  }
  /**
   * Emits a value every specified period.
   * @param interval The period to wait between emitting subsequent values, in milliseconds.
   */
  template <typename T>
  Observable<T>* timer(int interval) {
    return new Observable<T>([widget, sig](auto subscriber) -> optional<TeardownLogic> {
      return nullopt;
    });
  }
}
