#pragma once

#include <array>
#include <initializer_list>
#include <optional>
#include <type_traits>
#include <vector>

#include "../debug.h"
#include "../types.h"
#include "overload.h"
#include "subscriber.h"
#include "subscription.h"

namespace rx {

  using namespace std;

  template <typename T>
  class Observable {
  protected:
    vector<T> values = vector<T>();
    vector<Observable<any> *> operations = vector<Observable<any> *>();

    function<optional<TeardownLogic>(Subscriber<T> *)> _subscribe = [](Subscriber<T> *subscriber) {
      Debug::debug("Observable::_subscribe -> default logic");
      return nullopt;
    };

  public:
    using ObservableSubscribe = variant<monostate, function<void()>, function<void(Subscriber<T>)>>;
    /**
     * Create an Observable without a subscribe function.
     */
    Observable() {}
    /**
     * Create an Observable with a given subscribe function.
     * @param subscribe How the Observable will be subscribed to.
     */
    Observable(function<optional<TeardownLogic>(Subscriber<T> *)> subscriber) {
      this->_subscribe = subscriber;
    }
    /**
     * Subscribes to the Observable.
     * @param observerOrNext The Observer or Next function to subscribe to the Observable.
     * @return A Subscription that can be used to unsubscribe from the Observable.
     */
    Subscription *subscribe(ObserverOrNext<T> observerOrNext = monostate()) {
      Subscriber<T> *subscriber;
      visit(
        overload{
          [this, &subscriber](Subscriber<T> *s) {
            subscriber = s;
            Debug::debug("Observable::subscribe -> using existing Subscriber");
          },
          [this, &subscriber](auto o) {
            subscriber = new Subscriber<T>(o);
            Debug::debug("Observable::subscribe -> creating new Subscriber");
          }
        },
        observerOrNext
      );
      optional<TeardownLogic> v = this->_subscribe(subscriber);
      subscriber->add(v);
      return subscriber;
    }

    void complete() {
      // for (auto value : *values) {
      //   subscriber(value);
      // }
    }

    Observable<T> *pipe() {
      return this;
    }

    template <typename In>
    In pipe(UnaryFunction<Observable<T> *, In> op1) {
      return pipeReducer<Observable<T> *, In>(op1);
    }

    template <typename In, typename Out>
    Out pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2) {
      return pipeReducer<In, Out>(op1, op2);
    }

    template <typename In, typename Out, typename C>
    C pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3) {
      return pipeReducer<In, C>(op1, op2, op3);
    }

    template <typename In, typename Out, typename C, typename D>
    D pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4) {
      return pipeReducer<In, D>(op1, op2, op3, op4);
    }

    template <typename In, typename Out, typename C, typename D, typename E>
    E pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4, UnaryFunction<D, E> op5) {
      return pipeReducer<In, E>(op1, op2, op3, op4, op5);
    }

    template <typename In, typename Out, typename C, typename D, typename E, typename F>
    F pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4, UnaryFunction<D, E> op5, UnaryFunction<E, F> op6) {
      return pipeReducer<In, F>(op1, op2, op3, op4, op5, op6);
    }

    template <typename In, typename Out, typename C, typename D, typename E, typename F, typename G>
    G pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4, UnaryFunction<D, E> op5, UnaryFunction<E, F> op6, UnaryFunction<F, G> op7) {
      return pipeReducer<In, G>(op1, op2, op3, op4, op5, op6, op7);
    }

    template <typename In, typename Out, typename C, typename D, typename E, typename F, typename G, typename H>
    H pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4, UnaryFunction<D, E> op5, UnaryFunction<E, F> op6, UnaryFunction<F, G> op7, UnaryFunction<G, H> op8) {
      return pipeReducer<In, H>(op1, op2, op3, op4, op5, op6, op7, op8);
    }

    template <typename In, typename Out, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
    I pipe(UnaryFunction<Observable<T> *, In> op1, UnaryFunction<In, Out> op2, UnaryFunction<Out, C> op3, UnaryFunction<C, D> op4, UnaryFunction<D, E> op5, UnaryFunction<E, F> op6, UnaryFunction<F, G> op7, UnaryFunction<G, H> op8, UnaryFunction<H, I> op9) {
      return pipeReducer<In, I>(op1, op2, op3, op4, op5, op6, op7, op8, op9);
    }

  private:
    template <typename In, typename Out, typename... Args>
    Out pipeReducer(Args &&...args) {
      Observable<T> *prev = this;
      auto list = {args...};
      for (auto fn : list) {
        prev = fn(prev);
      }
      return prev;
    }
  };

  template <typename In, typename Out>
  Subscriber<In> *operate(Subscriber<Out> *destination, SubscriberOverrides<In> overrides = {}) {
    return new Subscriber<In>(destination, overrides);
  }

  template <typename T>
  void callNextOperation(NextFn<T> fn, Next<T> value) {
    visit(
      overload{
        [value](function<void(Next<T>)> callable) {
          Debug::debug("callNextOperation -> function<void(Next<T>)>");
          callable(value);
        },
        [](function<void()> callable) {
          Debug::debug("callNextOperation -> function<void()>");
          callable();
        }
      },
      fn
    );
  }

  template <typename T>
  const Observable<T> *EMPTY = new Observable<T>([](auto subscriber) -> optional<TeardownLogic> {
    subscriber->complete();
    return nullopt;
  });
}
