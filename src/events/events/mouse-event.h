#pragma once

#include <any>

#include "event.h"

using namespace std;

class MouseEvent : public Event<any> {
  int button = 0;
  int buttons[3] = {-1, -1, -1};
  int clientX = 0;
  int clientY = 0;
  bool ctrlKey = false;
  bool shiftKey = false;
  bool altKey = false;
  int pageX = 0;
  int pageY = 0;
  int screenX = 0;
  int screenY = 0;
  int x = 0;
  int y = 0;
};
