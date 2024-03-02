#pragma once

namespace rx {

  class Unsubscribable {
  public:
    virtual void unsubscribe() = 0;
  };

}
