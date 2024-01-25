#pragma once

#include "app/classes/file.h"
#include "events/events.h"

class File;

class Subjects {
public:
  static Subject<File *> *fileAdded;
  // static Subject<void> *filesUpdated;
};
