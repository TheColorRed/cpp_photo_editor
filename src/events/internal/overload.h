#pragma once

namespace rx {
  template <class... Ts>
  struct overload : Ts... {
    using Ts::operator()...;
  };
}
