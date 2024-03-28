#ifndef _ITEM_TOOLS_HPP_
#define _ITEM_TOOLS_HPP_

#include <algorithm>
#include <optional>
#include <stdint.h>

namespace ItemValidator {

constexpr auto enable_range_checks = true;

void OnRangeViolation() {
  while (1)
    ;
}

template <typename T, T kMin, T kMax> class CheckedAndClamped {
public:
  static std::optional<T> Validate(T value) {
    if constexpr (enable_range_checks) {
      if (value < kMin || value > kMax) {
        OnRangeViolation();
      }
    }
    return std::clamp(value, kMin, kMax);
  }

  static constexpr T Min() { return kMin; }

  static constexpr T Max() { return kMax; }
};

class Unchecked {
public:
  template <typename T> static std::optional<T> Validate(T value) {
    return value;
  }
};
} // namespace ItemValidator

namespace ItemInsideStructure {
class SingleItem {
public:
  static constexpr size_t kCount = 1;
};

template <typename index_type, size_t elements_count> struct ArrayItem {
  using Index = index_type;
  static constexpr size_t kCount = elements_count;
};
} // namespace ItemInsideStructure

#endif