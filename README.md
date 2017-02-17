# ArduinoSort

Easy sorting of arrays for Arduino, with focus on low memory footprint.

* Easy to use
* Small. Less program storage space than bubble sort or qsort!
* Fast
* Works with most data types, including `int`, `float`, `String` and `bool`
* Advanced users can add their own comparison function!

## Why?

Sometimes you need to sort an array. For example if you have multiple sensor readings and want the middle one. This library helps you sort in increasing order:

    12, 1, 5, 2, 6 --> 1, 2, 5, 6, 12
    
or in reverse:

    12, 1, 5, 2, 6 --> 12, 6, 5, 2, 1
    
ArduinoSort compiles to smaller code than most other sort functions, saving precious program space on your Arduino.

![Arduino sketch using 12% storage space](docs/storage1.png?raw=true "Small on storage space")

## Let's get going!

### Install

1. Go to [releases](https://github.com/emilv/ArduinoSort/releases) and download the latest `ArduinoSort.zip`.
2. Follow the [tutorial](https://www.arduino.cc/en/Guide/Libraries#toc4) on how to install a .ZIP library.
3. Done!
   * You can now use the library by going to *Sketch* -> *ArduinoSort*.
   * There are examples under *File* -> *Examples* -> *ArduinoSort*

### Easy

This is almost always what you want:

    sortArray(nameOfYourArray, 10);
	
This will sort an array of 10 elements. Works with `int`, `float`, `bool`, `char`, `String` and `char*`.

To sort in reverse (larger values first):

    sortArrayReverse(nameOfYourArray, 10);
    
The first argument is your array. The second argument is the number of values in your array.


### Custom comparison function

You can build your own comparison function. This is useful if you need to sort `struct`s  or multidimensional arrays. The function should take as arguments two of your elements and return `true` if the first argument is considered larger than the second. Return `false` if the second argument is larger than the first, or if they are equal.

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

Ask on the official [Arduino forum](http://forum.arduino.cc/), on [Arduino StackExchange](http://arduino.stackexchange.com/), or on [Reddit /r/arduino](https://www.reddit.com/r/arduino/). Don't forget to google your question first! It might have been answered by someone else already.


## How does it work?

ArduinoSort uses an algorithm called [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort). It repeatadly compares two elements to each other to find out which is the larger one. If swaps the two elements if it needs to. Then it compares two other elements, and so on, until it knows all the elements are in the right order.

There are other sorting functions too. The most popular one for Arduino is [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort), which is very easy to understand. Then you have more advanced algorithms such as [merge sort](https://en.wikipedia.org/wiki/Merge_sort) and [quicksort](https://en.wikipedia.org/wiki/Quicksort).  The difference between these algorithms are in what order they choose elements to compare, and it turns out that the order affects how many comparisons you need to make.

I have chosen *insertion sort* because my [benchmarks](docs/BENCHMARKS.md) show that is smallest in program storage space and it uses very little memory.

For deeper knowledge, read about the [implementation details](docs/IMPLEMENTATION.md). There I also explain why ArduinoSort is faster than bubble sort!

## Do you want to help me?

If you have ideas for improvements, open an issue here on Github and let us discuss it! I do accept contributions and pull requests, but please ask first.

Things that I am always happy for:

* Suggestions on how to make things easy to use
* Improvements to this README that makes it easier to read and understand
* Have you found a way to save a few bytes? Open an issue!
