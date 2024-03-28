# Storage box
## _An adapter for std::tuple._

### How does it work:
```
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
  std::cout << storage;

  return 0;
}
```

### To build it:
> src/make

### To test it:
> src/storagebox.exe

### You will see:

```
src>storagebox.exe
Default values:
N16DefaultItemTypes14BooleanSettingILb1EEE: 1
N16DefaultItemTypes9ItemUint8E: 0
N16DefaultItemTypes14ItemUint8ArrayE: [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ]
N16ExampleItemTypes19ExampleEnumItemTypeE: 0
N16ExampleItemTypes26ExampleCustomClassItemTypeE: data=1, data64=1
N16ExampleItemTypes31ExampleCustomClassItemArrayTypeE:
[
        data=1, data64=1
        data=1, data64=1
        data=1, data64=1
        data=1, data64=1
 ]
Changed values:
N16DefaultItemTypes14BooleanSettingILb1EEE: 0
N16DefaultItemTypes9ItemUint8E: 7
N16DefaultItemTypes14ItemUint8ArrayE: [ 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0 ]
N16ExampleItemTypes19ExampleEnumItemTypeE: 4
N16ExampleItemTypes26ExampleCustomClassItemTypeE: data=33, data64=55
N16ExampleItemTypes31ExampleCustomClassItemArrayTypeE:
[
        data=1, data64=1
        data=1, data64=1
        data=33, data64=55
        data=1, data64=1
 ]
```