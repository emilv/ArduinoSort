#include "Arduino.h"
#include "ArduinoSort.cpp"

#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

template<typename AnyType> bool builtinLargerThan(AnyType first, AnyType second) {
  return first > second;
}

template<> bool builtinLargerThan(char* first, char* second) {
  return strcmp(first, second) > 0;
}

template<typename AnyType> void insertionSort(AnyType array[], size_t sizeOfArray, bool reverse, bool (*largerThan)(AnyType, AnyType)) {
  for (size_t i = 1; i < sizeOfArray; i++) {
    for (size_t j = i; j > 0 && (largerThan(array[j-1], array[j]) != reverse); j--) {
      SWAP(array[j-1], array[j], AnyType);
    }
  }
}

template<typename AnyType> void sortArray(AnyType array[], size_t sizeOfArray) {
	insertionSort(array, sizeOfArray, false, builtinLargerThan);
}

template<typename AnyType> void sortArrayReverse(AnyType array[], size_t sizeOfArray) {
	insertionSort(array, sizeOfArray, true, builtinLargerThan);
}

template<typename AnyType> void sortArray(AnyType array[], size_t sizeOfArray, bool (*largerThan)(AnyType, AnyType)) {
	insertionSort(array, sizeOfArray, false, largerThan);
}

template<typename AnyType> void sortArrayReverse(AnyType array[], size_t sizeOfArray, bool (*largerThan)(AnyType, AnyType)) {
	insertionSort(array, sizeOfArray, true, largerThan);
}
