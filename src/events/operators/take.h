#pragma once

#include "../internal/observable.h"
#include "../types.h"

namespace rx {
  template <typename T>
  MonoTypeOperatorFunction<T> take(int count) {
    // return count <= 0
    //        ? [](auto source) -> optional<TeardownLogic> { return EMPTY<T>; }
    //        :
    return [count](Observable<T>* source) {
      return new Observable<T>([count, source](Subscriber<T>* destination) -> optional<TeardownLogic> {
        int seen = 0;
        Subscriber<T>* operatorSubscriber;
        operatorSubscriber = operate<T>(
          destination,
          {.next = [destination, seen, count, operatorSubscriber](Next<T> value) mutable {
            if (++seen < count) {
              callNextOperation(destination->next, value);
            } else {
              operatorSubscriber->unsubscribe();
              callNextOperation(destination->next, value);
              destination->complete();
            }
          }}
        );
        source->subscribe(operatorSubscriber);
        return nullopt;
      });
    };
  }
}
