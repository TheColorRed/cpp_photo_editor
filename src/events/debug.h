#pragma once

#include <string>

namespace rx {
  using namespace std;
  /**
   * The level of a log message.
   */
  enum class LogLevel {
    /** Debugging information. This is the lowest level, and is not logged in release builds. */
    DEBUG = 0,
    /** Informational messages. This is the default level. */
    INFO = 1,
    /** Warnings. These are messages that indicate potential problems. */
    WARN = 2,
    /** Errors. These are messages that indicate problems. */
    ERROR = 3,
    /** Fatal errors. These are messages that indicate a problem that will cause the program to crash. */
    FATAL = 4
  };

  class Debug {
  private:
    /**
     * The current log level. Defaults to INFO.
     */
    static LogLevel level;
    /**
     * Write a message to the console at a given level.
     * If the level is lower than the current log level, the message will not be logged.
     * @param level The log level.
     * @param message The message to log.
     * @param args The arguments to format the message with.
     */
    template <typename... Args>
    static void write(LogLevel level, string message, Args... args) {
#ifdef NDEBUG
      if (level >= Debug::level && level != LogLevel::DEBUG) {
        printf((message + "\n").c_str(), args...);
      }
#else
      // printf("Debug::level: %d -- %d\n", Debug::level, level);
      if (level >= Debug::level) {
        printf((message + "\n").c_str(), args...);
      }
#endif
    }

  public:
    /**
     * Set the log level.
     * Lower levels are more important.
     * @param level The log level. Anything below this level will not be logged.
     */
    static void setLogLevel(LogLevel level);
    /**
     * Log a message to the console using a log level of DEBUG.
     * @param message The message to log.
     * @param args The arguments to format the message with.
     */
    template <typename... Args>
    static void debug(string message, Args... args) {
      Debug::write(LogLevel::DEBUG, message, args...);
    }
    // static void debug(string message);
    /**
     * Log a message to the console using a log level of INFO.
     * @param message The message to log.
     * @param args The arguments to format the message with.
     */
    template <typename... Args>
    static void info(string message, Args... args) {
      Debug::write(LogLevel::INFO, message, args...);
    }
    /**
     * Logs an error to the console using a log level of ERROR.
     * @param message The error message to log.
     */
    static void error(string message);
    /**
     * Logs an exception to the console using a log level of ERROR.
     * @param e The exception to log.
     */
    static void error(exception e);
    /**
     * Logs a warning to the console using a log level of WARN.
     * @param message The warning message to log.
     */
    static void warn(string message);
    /**
     * Logs a fatal error to the console using a log level of FATAL.
     * @param message The fatal error message to log.
     */
    static void fatal(string message);
    /**
     * Logs a fatal exception to the console using a log level of FATAL.
     * @param e The fatal exception to log.
     */
    static void fatal(exception e);
  };
}
