#pragma once

#include <functional>
#include <variant>

#include "events.h"

template <typename T>
class Subscriber;
template <typename T>
class Subscription;
template <typename T>
class Observer;

template <typename T>
using TeardownLogic = variant<function<void()>, function<void(T)>, shared_ptr<Subscription<T>>>;
template <typename T>
using ObserverOrNext = variant<function<void()>, function<void(T)>, shared_ptr<Subscriber<T>>>;
template <typename T>
using Destination = variant<Observer<T>, ObserverOrNext<T>>;
template <typename T>
using Callable = variant<function<void()>, function<void(T)>>;
