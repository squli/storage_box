#ifndef _ITEM_STORAGE_BOX_HPP_
#define _ITEM_STORAGE_BOX_HPP_

#include <array>
#include <iostream>
#include <stdint.h>
#include <type_traits>
#include <variant>

#include "ItemTypes.hpp"
namespace Detail {
/// @brief Get index by type in tuple
/// @return index
template <typename T, typename First, typename... Ts>
constexpr size_t GetStorageIndex() {
  if constexpr (std::is_same_v<T, First>) {
    return 0;
  } else {
    return 1 + GetStorageIndex<T, Ts...>();
  }
}

/// @brief Element of tuple to store
/// @tparam TupleItemClassT
template <typename TupleItemClassT> struct TupleItem {
  using TupleItemDataStorageType =
      typename std::array<typename TupleItemClassT::Storage,
                          TupleItemClassT::kCount>;
};
} // namespace Detail

/// @brief Adapter class for tuple
/// @tparam ...Ts
template <typename... Ts> class StorageBox {
public:
  /// @brief Constructor, all parameters are initialized to the default value.
  StorageBox() {
    (Init<Ts>(), ...);
  }
  StorageBox(const StorageBox &) = delete;
  void operator=(const StorageBox &) = delete;

  /// @brief Reads the current value of the @p T parameter for SingleItem
  /// @tparam T The parameter.
  /// @returns Current value of the parameter.
  /// @note This function can only be used for parameters with \p kCount == 1.
  template <typename T, typename = std::enable_if_t<T::kCount == 1>>
  typename T::Storage Get() const {
    static_assert(T::kCount == 1);
    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    return std::get<storage_index>(_storage)[0];
  }

  /// @brief Reads the current value of the @p T parameter.
  /// @tparam T The parameter.
  /// @param index The index.
  /// @returns Current value of the parameter.
  /// @note This function can only be used for parameters with \p kCount > 1.
  template <typename T> typename T::Storage Get(typename T::Index index) const {
    static_assert(T::kCount > 1);
    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    return std::get<storage_index>(_storage)[static_cast<size_t>(index)];
  }

  /// @brief Reads the current value of the @p T parameter.
  /// @tparam T The parameter.
  /// @param index The index.
  /// @returns Current value of the parameter.
  /// @note This function can only be used for parameters with \p kCount > 1.
  template <typename T, typename = std::enable_if<
                            std::is_constructible<typename T::Index>::value>>
  typename Detail::TupleItem<T>::TupleItemDataStorageType Get() const {
    static_assert(T::kCount > 1);
    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    return std::get<storage_index>(_storage);
  }

  /// @brief Tries to set the value of the @p T parameter.
  /// @tparam T The parameter.
  /// @param value The value.
  template <typename T, typename = std::enable_if_t<T::kCount == 1>>
  void Set(typename T::Storage value) {
    static_assert(T::kCount == 1);

    if (auto checked_value = T::Validate(value)) {
      Save<T>(*checked_value);
    }
  }

  /// @brief Tries to set the value of the @p T parameter.
  /// @tparam T The parameter.
  /// @param index The index for the value.
  /// @param value The value.
  /// @note This function can only be used for parameters with \p kCount > 1.
  template <typename T>
  void Set(typename T::Index index, typename T::Storage value) {
    static_assert(T::kCount > 1);
    if (static_cast<size_t>(index) >= T::kCount) {
      return;
    }

    if (auto checked_value = T::Validate(value)) {
      Save<T>(index, *checked_value);
    }
  }

  /// @brief Tries to set the values of the @p T parameter.
  /// @tparam T The parameter.
  /// @param values The values to set.
  template <typename T, typename = std::enable_if_t<(T::kCount > 1)>>
  void Set(const Detail::TupleItem<T> &values) {
    static_assert(T::kCount > 1);
    auto index = 0;
    for (auto &&value : values) {
      Set<T>(static_cast<typename T::Index>(index++), value);
    }
  }

private:
  /// @brief Sets the default value for \p T 
  template <typename T> void Init() {
    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    std::get<storage_index>(_storage).fill(T::default_value);
  }

  /// @brief Set a new value in the storage if new one is not equal the previous
  template <typename T> void Save(typename T::Storage value) {
    static_assert(T::kCount == 1);

    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    auto &stored_value = std::get<storage_index>(_storage)[0];
    if (stored_value != value) {
      stored_value = value;
    }
  }

  /// @brief Set a new indexed value in the storage.
  template <typename T>
  void Save(typename T::Index index, typename T::Storage value) {
    static_assert(T::kCount > 1);

    constexpr auto storage_index = Detail::GetStorageIndex<T, Ts...>();
    auto &stored_value =
        std::get<storage_index>(_storage)[static_cast<size_t>(index)];
    if (stored_value != value) {
      stored_value = value;
    }
  }

  /// @brief The storage tuple
  std::tuple<typename Detail::TupleItem<Ts>::TupleItemDataStorageType...> _storage;
};

/// @brief Debug print for this class
/// @tparam ...Ts
/// @param out
/// @param q
/// @return
template <typename... Ts>
std::ostream &operator<<(std::ostream &out, StorageBox<Ts...> &q) {
  return ((out << typeid(Ts).name() << ": " << (q.template Get<Ts>()) << "\n"),
          ...);
}

#endif