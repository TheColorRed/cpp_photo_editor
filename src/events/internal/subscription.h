#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "../debug.h"
#include "../types.h"
#include "finalizer.h"
#include "overload.h"
#include "unsubscribable.h"

namespace rx {
  using namespace std;

  class Subscription : public Unsubscribable {
  private:
    vector<Finalizer *> finalizers = vector<Finalizer *>();
    optional<Finalizer *> initialTeardown = {};

  public:
    bool closed = false;
    /**
     * Create a Subscription without any teardown logic.
     */
    Subscription() {}
    /**
     * Create a Subscription with a given initial teardown logic.
     * @param initalTeardown The initial teardown logic to add to the Subscription.
     */
    Subscription(function<void()> initalTeardown) {
      this->initialTeardown = new Finalizer(initalTeardown);
    }
    /**
     * Adds additional teardown logic to the existing Subscription if it is not closed.
     * If the Subscription is closed, the teardown logic will be executed immediately.
     * @param teardown The teardown logic to add to the Subscription.
     */
    void add(optional<TeardownLogic> teardown = nullopt) {
      TeardownLogic teardownLogic;
      // TeardownLogic teardownLogic = teardown.value_or(nullptr);
      Subscription *subscription = this->tryGetTeardownSubscription(teardownLogic);
      bool hasTeardown = teardown.has_value();
      bool isSubscription = subscription != nullptr;

      if (hasTeardown && subscription != this) {
        Finalizer *finalizer = new Finalizer(teardownLogic);
        if (this->closed) {
          Debug::debug("Subscription::add -> executing finalizer");
          this->execFinalizer(finalizer);
        } else {
          if (isSubscription) {
            Debug::debug("Subscription::add -> adding finalizer to subscription");
            subscription->add([this, finalizer]() {
              this->remove(finalizer);
            });
          }
          Debug::debug("Subscription::add -> adding finalizer to finalizer list");
          this->finalizers.push_back(finalizer);
        }
      }
    }

    void remove(Finalizer *finalizer) {
      auto idx = find(this->finalizers.begin(), this->finalizers.end(), finalizer);
      if (idx != this->finalizers.end()) {
        this->finalizers.erase(idx);
      }
    }

    void unsubscribe() {
      if (!this->closed) {
        this->closed = true;
        if (this->initialTeardown.has_value()) {
          Finalizer *finalizer = this->initialTeardown.value();
          finalizer->teardown();
        }

        if (finalizers.size() > 0) {
          for (Finalizer *finalizer : finalizers) {
            this->execFinalizer(finalizer);
          }
          this->finalizers.clear();
        }
      }
    }

  private:
    /**
     * Tries to get a Subscription from the teardown value.
     * @param teardownLogic The value to try to get a Subscription from.
     * @return A Subscription if the teardown value is a Subscription, otherwise nullptr.
     */
    Subscription *tryGetTeardownSubscription(TeardownLogic teardownLogic) {
      // Try to get a Subscription from the teardown value
      Subscription *subscription = nullptr;
      visit(
        overload{
          [subscription](Subscription *s) mutable { subscription = s; },
          [](auto) {}
        },
        teardownLogic
      );
      return subscription;
    }
    /**
     * Tries to get a function from the teardown value.
     * @param teardownLogic The value to try to get a function from.
     * @return A function if the teardown value is a function, otherwise nullptr.
     */
    function<void()> tryGetTeardownFunction(TeardownLogic teardownLogic) {
      // Try to get a function from the teardown value
      try {
        return get<function<void()>>(teardownLogic);
      } catch (const exception &e) {
        return nullptr;
      }
    }

    void execFinalizer(Finalizer *finalizer) {
      printf("execFinalizer\n");
      finalizer->teardown();
    }
  };
}
