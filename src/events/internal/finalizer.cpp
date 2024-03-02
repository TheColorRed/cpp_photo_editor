#include "finalizer.h"

#include "observable.h"
#include "subscription.h"

using namespace rx;
using namespace std;

rx::Finalizer::Finalizer(TeardownLogic teardown) {
  this->teardownLogic = teardown;
}

void rx::Finalizer::teardown() {
  visit(
    overload{
      [](function<void()> p) {
        Debug::debug("Finalizer::teardown -> using function<void()>");
        p();
      },
      [](Unsubscribable *unsub) {
        Debug::debug("Finalizer::teardown -> using Unsubscribable");
        unsub->unsubscribe();
      },
      []() { Debug::debug("Finalizer::teardown -> no teardown logic"); }
    },
    this->teardownLogic
  );
}
