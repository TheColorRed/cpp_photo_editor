#pragma once

#include <functional>
#include <optional>

#include "../types.h"

namespace rx {
  using namespace std;

  template <typename T>
  struct Observer {
    optional<NextFn<T>> next = {};
    optional<ErrorFn> error = {};
    optional<CompleteFn> complete = {};
    virtual ~Observer() = default;
  };

  template <typename T>
  struct SubscriberOverrides {
    optional<NextFn<T>> next = {};
    optional<ErrorFn> error = {};
    optional<CompleteFn> complete = {};
    optional<FinalizeFn> finalize = {};
  };
}
