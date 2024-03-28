CXXFLAGS = -fpermissive -O3 -Werror

HEADERS = ItemStorageBox.hpp ItemTools.hpp ItemTypes.hpp

default: storagebox

storagebox.o: main.cpp $(HEADERS)
	g++ -std=c++17 $(CXXFLAGS) -c main.cpp -o storagebox.o

storagebox: storagebox.o
	g++ -std=c++17 $(CXXFLAGS) storagebox.o -o storagebox

clean:
	-del /q storagebox.o
	-del /q storagebox.exe