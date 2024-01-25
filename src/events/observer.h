#pragma once

#include <any>

using namespace std;

template <typename T>
class Observer {
public:
  Observer() {}
  virtual void next() = 0;
  virtual void next(T value) = 0;
  virtual void error() {}
  virtual void error(any err) {}
  virtual void complete() {}
};
