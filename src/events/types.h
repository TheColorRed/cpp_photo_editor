#pragma once

#include <any>
#include <functional>
#include <variant>

namespace rx {

  class Subscription;
  template <typename T>
  class Subscriber;
  template <typename T>
  class Observer;
  template <typename T>
  class Observable;

  class Unsubscribable;

  using namespace std;

  // using Unsubscribable = variant<function<void()>, Subscription*>;
  using TeardownLogic = variant<function<void()>, Subscription*, Unsubscribable*>;

  template <typename T>
  using Callable = variant<monostate, function<void()>, function<void(T)>>;

  template <typename T>
  using Next = variant<monostate, T, T*>;
  template <typename T>
  using NextFn = variant<function<void(Next<T>)>, function<void()>>;
  using ErrorFn = function<void(any)>;
  using CompleteFn = function<void()>;
  using FinalizeFn = function<void()>;
  using UnsubscribeFn = function<void()>;

  template <typename T>
  using ObserverOrNext = variant<
    monostate,
    NextFn<T>,
    Observer<T>*,
    Subscriber<T>*>;

  template <typename T, typename R>
  using UnaryFunction = function<R(T)>;

  template <typename T, typename R>
  using OperatorFunction = UnaryFunction<Observable<T>*, Observable<R>*>;

  template <typename T>
  using MonoTypeOperatorFunction = OperatorFunction<T, T>;
}
