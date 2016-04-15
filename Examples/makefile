all: nestedStruct nDimensionalArray saveStruct nestedStructsAndCells saveVariable

nestedStruct: nestedStruct.o
	gcc -o nestedStruct nestedStruct.o -lmatio

nestedStruct.o: nestedStruct.cpp
	gcc -c nestedStruct.cpp

##################################################

nDimensionalArray: nDimensionalArray.o
	gcc -o nDimensionalArray nDimensionalArray.o -lmatio

nDimensionalArray.o: nDimensionalArray.cpp
	gcc -c nDimensionalArray.cpp

##################################################

saveStruct: saveStruct.o
	gcc -o saveStruct saveStruct.o -lmatio

saveStruct.o: saveStruct.cpp
	gcc -c saveStruct.cpp

##################################################

nestedStructsAndCells: nestedStructsAndCells.o
	gcc -o nestedStructsAndCells nestedStructsAndCells.o -lmatio

nestedStructsAndCells.o: nestedStructsAndCells.cpp
	gcc -c nestedStructsAndCells.cpp

##################################################

saveVariable: saveVariable.o
	gcc -o saveVariable saveVariable.o -lmatio

saveVariable.o: saveVariable.cpp
	gcc -c saveVariable.cpp
