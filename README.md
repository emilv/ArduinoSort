# ArduinoSort

Easy sorting of arrays for Arduino, with focus on low memory footprint and ease of use.

## Why?

Sometimes you need to sort an array of numbers or strings. There is very little documentation on this for the Arduino and I could not find a good library to help out. So here it is!

There are som tutorials that use what is called a [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort). This works great on the Arduino because it uses very little memory. This library uses an algorithm called [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) because I have learned that it is even smaller, and also a little bit faster.

I have built this library for the Arduino. I have tested it in the Arduino IDE, run it on an Arduino Pro Mini, and I focus on a small memory footprint. You don't want to waste those precious memory bytes! It will work great for arrays up to a few thousand elements, which is all you need on an Arduino.

## Let's get going!

### Easy

This is almost always what you want:

    sortArray(nameOfYourArray, 10);
	
This will sort an array of 10 elements. Works with `int`, `float`, `bool`, `char`, `String` and `char*`.

To sort in reverse (larger values first):

    sortArrayReverse(nameOfYourArray, 10);
    
The first argument is your array. The second argument is the number of values in your array.


### Custom comparison function

You can build your own comparison function. The function should take as arguments two of your elements and return `true` if the first argument is considered larger than the second. Return `false` if the second argument is larger than the first, or if they are equal.

Your comparison function takes two elements. **Example**:

    bool firstIsLarger(int first, int second) {
      if (first > second) {
        return true;
      } else {
	    return false;
	  }
    }
	
    sortArray(nameOfYourArray, 10, firstIsLarger);
	
To sort in reverse:

    sortArrayReverse(nameOfYourArray, 10, firstIsLarger);
    
## Do you need help?

Ask on the official Arduino forum or on Arduino StackExchange. Don't forget to google your question first! It might have been answered by someone else already.


## Benchmarks

To make ArduinoSort I ran a series of tests to find the smallest sort algorithm. You do not need to read this to use ArduinoSort.

I ran these benchmarks on a 16 MHz Arduino Pro Mini. Sizes are estimates.

### 2 elements

sort2 is specialized for two-element arrays: it is a macro with a simple ìf` statement.

| Sorting method      | Compiled size |
| ------------------- | ------------- |
| Baseline, no sort   | 2 326 bytes   |
| qsort, standard lib | 3 510 bytes   |
| gnome sort 2        | 2 388 bytes   |
| bubblesort          | 2 354 bytes   |
| sort2               | 2 344 bytes   |
| insertion sort      | 2 344 bytes   |

### 3 elements

sort3 is specialized for three-element arrays, similar to sort2

| Sorting method      | Compiled size |
| ------------------- | ------------- |
| Baseline, no sort   | 2 352 bytes   |
| qsort, standard lib | 3 536 bytes   |
| gnome sort 2        | 2 448 bytes   |
| bubblesort          | 2 426 bytes   |
| sort3               | 2 416 bytes   |
| insertion sort      | 2 396 bytes   |

### 20 elements

| Sorting method      | Compiled size |
| ------------------- | ------------- |
| Baseline, no sort   | 2 322 bytes   |
| qsort, standard lib | 3 504 bytes   |
| gnome sort 2        | 2 400 bytes   |
| bubblesort          | 2 370 bytes   |
| insertion sort      | 2 364 bytes   |

### Conclusion

According to the benchmark insertion sort is always smallest. This is great news! It means we can use it for everything. But why is it minimal? How can it be as small as a specialized sorting function? The reason is that the Arduino IDE optimizes the code. When it detects that we are trying to sort only a fixed number of elements (2, 3, ...) it removes code paths that are unused. These optimizations are based on decades of computer science research, some of them are very clever.

You can always use the `sortArray` function, for small or large arrays. It will always be optimal in size for your use case. You can learn more about this on Wikipedia on [Optimizing compiler](https://en.wikipedia.org/wiki/Optimizing_compiler).

Insertion sort is pretty fast for elements up to a few hundred elements or so, maybe 1000. For really large arrays you might want to look into `qsort` instead. But such large arrays will not fit in the Arduino memory anyway so we don't care about that case.


## Implementation details

This section is advanced reading. You do not need to understand this to use ArduinoSort. Learn about the magic behind the scenes!

[Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) is:

* a [stable](https://en.wikipedia.org/wiki/Sorting_algorithm#Stability) sort, which means that elements that are equal will not be swapped
* faster in practice than [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
* small in size when compiled for Arduino (see benchmarks above)

This library is implemented entirely in the file `ArduinoSort.h`. The reason is that we want to keep code size down, and including a `.cpp` file would have made the size larger. The long explanation is that if we used a .cpp file we would need to compile the sort functions for all data types, even for those that are not used in your program. By putting everything in the .h file and use templating we give the compiler more control over what to include in the final binary.

The `sortArray` and `sortArrayReverse` functions are implemented as function templates. This means that they can be used to sort any type of data (in my code I call this the `AnyType`). When your program needs to sort values of the type `int` you will automatically get a function that can sort `int`s, and when you need to sort `String` values you will get a function that can sort `String`s.

The actual sorting function, `ArduinoSort::insertionSort`, takes a comparison function as last argument. Yes, you can send functions as argument to other functions! This is because C++ have [first-class functions](https://en.wikipedia.org/wiki/First-class_function). As you can see in the code, this actually makes the code quite easy to read. We can have a single version of `insertionSort` and just send in different comparison functions. There are two built-in comparison functions, one for everything that supports the `>` operator and one for `char*`. You can build your own comparison functions too, which is described above under the ehadline "Custom comparison function".

Last but not least, I use overloading so that the same function can take different number of arguments, or arguments of different types. You can call `sortArray` with or without a custom cmoparison function and it will work out of the box! The C++ compiler will automatically choose the right function for you.


## Do you want to help me?

If you have ideas for improvements, open an issue here on Github and let us discuss it! I do accept contributions and pull requests, but please ask first.

Things that I am always happy for:

* Suggestions on how to make things easy to use
* Improvements to this README that makes it easier to read and understand
* Have you found a way to save a few bytes? Open an issue!
