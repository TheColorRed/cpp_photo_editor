#pragma once

using namespace std;

template <typename T>
struct Event {
  T target;

  bool cancelable = true;

  void preventDefault() {
    if (this->cancelable) {
    }
  }
};
