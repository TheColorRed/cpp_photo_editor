#pragma once

#include "../types.h"

using namespace std;

namespace rx {
  class Finalizer {
  private:
    TeardownLogic teardownLogic;

  public:
    Finalizer(rx::TeardownLogic teardown);
    /**
     * Runs the teardown logic for this Finalizer.
     */
    void teardown();

    virtual ~Finalizer() = default;
  };
}
