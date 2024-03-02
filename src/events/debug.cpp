#include "debug.h"

#include <iostream>
#include <string>

namespace rx {

  LogLevel Debug::level = LogLevel::INFO;

  void Debug::setLogLevel(LogLevel level) {
    Debug::level = level;
  }

  void Debug::error(string message) {
    Debug::write(LogLevel::ERROR, "\033[0;31m%s", message);
  }

  void Debug::error(exception e) {
    Debug::error(string("What: ") + e.what());
  }

  void Debug::warn(string message) {
    Debug::write(LogLevel::WARN, "\033[0;33m%s", message);
  }

  void Debug::fatal(string message) {
    Debug::write(LogLevel::FATAL, "\033[0;31m%s", message);
  }

  void Debug::fatal(exception e) {
    Debug::fatal(string("What: ") + e.what());
  }
}
