# Implementation details

This section is advanced reading. You do not need to understand this to use ArduinoSort.

## The black magic behind the scenes!

[Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) is:

* a [stable](https://en.wikipedia.org/wiki/Sorting_algorithm#Stability) sort, which means that elements that are equal will not be swapped
* faster in practice than [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
* small in size when compiled for Arduino ([benchmarks](BENCHMARKS.md))

This library is implemented entirely in the file `ArduinoSort.h`. The reason is that we want to keep code size down, and including a `.cpp` file would have made the size larger. The long explanation is that if we used a .cpp file we would need to compile the sort functions for all data types, even for those that are not used in your program. By putting everything in the .h file and use templating we give the compiler more control over what to include in the final binary.

The `sortArray` and `sortArrayReverse` functions are implemented as function templates. This means that they can be used to sort any type of data (in my code I call this the `AnyType`). When your program needs to sort values of the type `int` you will automatically get a function that can sort `int`s, and when you need to sort `String` values you will get a function that can sort `String`s.

The actual sorting function, `ArduinoSort::insertionSort`, takes a comparison function as last argument. Yes, you can send functions as argument to other functions! This is because C++ have [first-class functions](https://en.wikipedia.org/wiki/First-class_function). As you can see in the code, this actually makes the code quite easy to read. We can have a single version of `insertionSort` and just send in different comparison functions. There are two built-in comparison functions, one for everything that supports the `>` operator and one for `char*`. You can build your own comparison functions too, which is described above under the ehadline "Custom comparison function".

Last but not least, I use overloading so that the same function can take different number of arguments, or arguments of different types. You can call `sortArray` with or without a custom cmoparison function and it will work out of the box! The C++ compiler will automatically choose the right function for you.

## Smallest

I have made multiple claims that ArduinoSort is the smallest sorting function. But why is it minimal? How can it be as small as a specialized sorting function? The reason is that the Arduino IDE optimizes the code. When it detects that we are trying to sort only a fixed number of elements (2, 3, ...) it removes code paths that are unused. These optimizations are based on decades of computer science research, some of them are very clever. You can learn more about this on Wikipedia on [Optimizing compiler](https://en.wikipedia.org/wiki/Optimizing_compiler)

## Faster than bubble sort? But both are in O(n^2)

Some people point out that *insertion sort* and *bubble sort* both run in `O(n^2)` time. This is true. But that does *not* mean they are equally fast! It only means that for large arrays they behave similarly when you add more elements. *Bubble sort* will loop over portions of the array that we know are already sorted. *Insertion sort* keeps track of what portion is already sorted and will only loop over the non-sorted part. This means that insertion sort speeds up when the sorted part grows. The speed-up is not asymptotic, but it is a speed-up in **[wall-clock time](https://en.wikipedia.org/wiki/Wall-clock_time)**.

If you have very large arrays you might want to look towards `qsort` that is included by default in `Arduino.h` (or rather in `stdlib.h`). But you will only benefit from `qsort` if you have somewhere around 2000 elements or more, and `qsort` is much larger than ArduinoSort.
