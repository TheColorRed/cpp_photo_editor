#pragma once

#include <iomanip>
#include <type_traits>

template <typename T, typename = void>
struct is_iterable : std::false_type {};

// this gets used only when we can call std::begin() and std::end() on that type
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T&>())),
                                  decltype(std::end(std::declval<T&>()))> > : std::true_type {};

// template <typename T>
// constexpr bool IsIterable = is_iterable<T>::value;
