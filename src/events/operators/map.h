#pragma once

#include <functional>
#include <optional>
#include <variant>

#include "../internal/observable.h"
#include "../types.h"

namespace rx {

  template <typename T, typename R>
  using MapProject = variant<function<R(T, int)>, function<R(T)>, function<R()>>;
  using namespace std;

  template <typename T, typename R>
  OperatorFunction<T, R> map(MapProject<T, R> project) {
    return [project](auto source) {
      return new Observable<R>([source, project](auto destination) -> optional<TeardownLogic> {
        auto index = 0;
        source->subscribe(
          operate<T, R>(
            destination,
            {.next = [project, index, destination](auto value) mutable {
              index++;
              visit(
                overload{
                  [value, index, destination](function<R(T, int)> p) {
                    Debug::debug("map -> using function<R(T, int)>");
                    //  destination->next(p(value, index));
                  },
                  [value, destination](function<R(T)> p) {
                    Debug::debug("map -> using function<R(T)>");
                    //  destination->next(p(value));
                  },
                  [value, destination](function<R()> p) {
                    Debug::debug("map -> using function<R()>");
                    //  destination->next(p());
                  }
                },
                project
              );
              // try {
              //   auto p = get<function<R(T, int)>>(project);
              //   Debug::debug("map -> using function<R(T, int)>");
              //   destination->next(p(value, index));
              // } catch (const exception &e) {
              //   try {
              //     auto p = get<function<R(T)>>(project);
              //     Debug::debug("map -> using function<R(T)>");
              //     destination->next(p(value));
              //   } catch (const exception &e) {
              //     try {
              //       auto p = get<function<R()>>(project);
              //       Debug::debug("map -> using function<R()>");
              //       destination->next(p());
              //     } catch (const exception &e) {
              //     }
              //   }
              // }
            }}
          )
        );
        return nullopt;
      });
    };
  }
}
