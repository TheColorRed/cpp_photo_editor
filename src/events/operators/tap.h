#pragma once

#include "../internal/observer.h"
#include "../types.h"

using namespace std;

namespace rx {

  template <typename T>
  using TapProject = NextFn<T>;

  template <typename T>
  MonoTypeOperatorFunction<T> tap(ObserverOrNext<T> project) {
    Observer<T>* tapObserver;

    return [project, tapObserver](Observable<T>* source) {
      return new Observable<T>([source, project, tapObserver](Subscriber<T>* destination) -> optional<TeardownLogic> {
        bool isUnsub = true;
        source->subscribe(
          operate<T>(
            destination,
            {.next = [project, tapObserver, destination](Next<T> value) {
              if (holds_alternative<NextFn<T>>(project)) {
                auto fn = get<NextFn<T>>(project);
                callNextOperation(fn, value);
              }
                // tapObserver->next(value);
                destination->next(value); },
             .error = [destination, isUnsub](auto err) mutable {
                isUnsub = false;
                destination->error(err); },
             .complete = [destination, isUnsub]() mutable {
                isUnsub = false;
                destination->complete(); },
             .finalize = [destination, isUnsub]() {
                printf("finalize\n");
                if (isUnsub) {

                } }
            }
          )
        );
        return nullopt;
      });
    };
  }
}
