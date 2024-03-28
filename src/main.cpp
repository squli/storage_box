#include <functional>
#include <iostream>
#include <optional>
#include <stdint.h>
#include <tuple>

#include "ItemStorageBox.hpp"

using MyStorage =
    StorageBox<DefaultItemTypes::BooleanSetting<true>,
               DefaultItemTypes::ItemUint8, DefaultItemTypes::ItemUint8Array,
               ExampleItemTypes::ExampleEnumItemType,
               ExampleItemTypes::ExampleCustomClassItemType,
               ExampleItemTypes::ExampleCustomClassItemArrayType>;

int main() {
  MyStorage storage;

  std::cout << "Default values:" << std::endl;
  std::cout << storage;

  storage.Set<DefaultItemTypes::ItemUint8>('7');
  storage.Set<DefaultItemTypes::BooleanSetting<true>>(false);
  storage.Set<DefaultItemTypes::ItemUint8Array>(5, '3');
  storage.Set<ExampleItemTypes::ExampleEnumItemType>(
      ExampleItemTypes::ExampleEnumType::kNickelCadmium);
  storage.Set<ExampleItemTypes::ExampleCustomClassItemType>({33, 55});
  storage.Set<ExampleItemTypes::ExampleCustomClassItemArrayType>(2, {33, 55});

  std::cout << "Changed values:" << std::endl;
  ;
  std::cout << storage;

  return 0;
}
