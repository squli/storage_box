#ifndef _ITEM_TYPES_HPP_
#define _ITEM_TYPES_HPP_

#include "ItemTools.hpp"

namespace DefaultItemTypes {

/// @brief Bool example
template <bool kDefault>
class BooleanSetting : public ItemInsideStructure::SingleItem {
public:
  using Storage = bool;
  static constexpr auto default_value = kDefault;

  static std::optional<bool> Validate(bool value) { return value; }

  static constexpr bool Min() { return false; }
  static constexpr bool Max() { return true; }
};

/// @brief Integer example
struct ItemUint8 : public ItemInsideStructure::SingleItem,
                   public ItemValidator::CheckedAndClamped<uint8_t, 0, 100> {
  using Storage = uint8_t;
  static constexpr Storage default_value = '0';
};

/// @brief Integer array example
struct ItemUint8Array
    : public ItemInsideStructure::ArrayItem<size_t, 12>,
      public ItemValidator::CheckedAndClamped<uint8_t, 0, 250> {
  using Storage = uint8_t;
  static constexpr Storage default_value = {'0'};
};
} // namespace DefaultItemTypes

std::ostream &operator<<(std::ostream &out,
                         std::array<DefaultItemTypes::ItemUint8Array::Storage,
                                    DefaultItemTypes::ItemUint8Array::kCount>
                             q) {
  out << "[ ";
  for (auto i = 0; i < DefaultItemTypes::ItemUint8Array::kCount - 1; i++) {
    out << q[i] << ", ";
  }
  out << q[DefaultItemTypes::ItemUint8Array::kCount - 1] << " ]";
  return out;
}

namespace ExampleItemTypes {

/// @brief Possible enum type
enum class ExampleEnumType {
  kDefault = 0,
  kLithium,
  kLeadAcid,
  kLithiumPolymer,
  kNickelCadmium,
  kNickelIron,
  kNickelMetalHydride,
  kNickelZinc,
  kCount,
};

/// @brief Enum example
struct ExampleEnumItemType
    : public ItemInsideStructure::SingleItem,
      public ItemValidator::CheckedAndClamped<
          ExampleEnumType, ExampleEnumType::kDefault, ExampleEnumType::kCount> {
  using Storage = ExampleEnumType;
  static constexpr Storage default_value = ExampleEnumType::kDefault;
  static constexpr auto name = "ExampleEnum type";
};

/// @brief Possible custom class type
struct ExampleCustomClassType {
  uint32_t data;
  uint64_t data64;
};

bool operator!=(const ExampleCustomClassType &lhs,
                const ExampleCustomClassType &rhs) {
  return lhs.data != rhs.data || lhs.data64 != rhs.data64;
}

/// @brief Custom class example
struct ExampleCustomClassItemType : public ItemInsideStructure::SingleItem,
                                    public ItemValidator::Unchecked {
  using Storage = ExampleCustomClassType;
  static constexpr Storage default_value = {1, 1};
};

/// @brief Custom class array example
struct ExampleCustomClassItemArrayType
    : public ItemInsideStructure::ArrayItem<size_t, 4>,
      public ItemValidator::Unchecked {
  using Storage = ExampleCustomClassType;
  static constexpr Storage default_value = {1, 1};
};
}; // namespace ExampleItemTypes

std::ostream &operator<<(std::ostream &out,
                         ExampleItemTypes::ExampleEnumItemType::Storage q) {
  return out << static_cast<uint64_t>(q);
}

std::ostream &
operator<<(std::ostream &out,
           ExampleItemTypes::ExampleCustomClassItemType::Storage q) {
  return out << "data=" << q.data << ", data64=" << q.data64;
}

std::ostream &operator<<(
    std::ostream &out,
    std::array<ExampleItemTypes::ExampleCustomClassItemArrayType::Storage,
               ExampleItemTypes::ExampleCustomClassItemArrayType::kCount>
        q) {
  out << std::endl << "[ " << std::endl;
  for (auto i = 0;
       i < ExampleItemTypes::ExampleCustomClassItemArrayType::kCount; i++) {
    out << "\t" << q[i] << std::endl;
  }
  out << " ]";
  return out;
}

#endif