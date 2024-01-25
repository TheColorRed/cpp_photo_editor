#pragma once

#include <functional>
#include <vector>

#include "../events.h"

template <typename T>
class Observable;

template <typename T>
class Subject : public Observable<T> {
  using CurrentObserver = vector<shared_ptr<Observer<T>>>;

private:
  unique_ptr<CurrentObserver> currentObservers = make_unique<CurrentObserver>();
  bool closed = false;

protected:
  TeardownLogic<T> _subscribe(shared_ptr<Subscriber<T>> subscriber) override {
    printf("Subject::_subscribe\n");
    this->currentObservers->push_back(subscriber);
    return subscriber;
  }

public:
  void next(T value) {
    if (this->closed)
      return;

    auto observers = this->currentObservers.get();
    for (int i = 0; i < observers->size(); i++) {
      auto observer = observers->at(i);
      observer->next(value);
    }
  }

  void error(any err) {
    if (this->closed)
      return;

    for (auto observer : currentObservers)
      observer.error(err);

    this->currentObservers.clear();
  }

  void complete() {
    if (this->closed)
      return;

    for (auto observer : currentObservers)
      observer.complete();

    this->currentObservers.clear();
  }

  void unsubscribe() {
    this->closed = true;
    this->currentObservers.clear();
  }

  Observable<T>* asObservable() {
    return new Observable<T>([this](Subscriber<T> subscriber) {
      return this->subscribe(subscriber);
    });
  }
};
