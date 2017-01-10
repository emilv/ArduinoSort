# ArduinoSort

Easy sorting of arrays for Arduino, with focus on low memory footprint and ease of use.

## Why?

Sometimes you need to sort an array of numbers or strings. There is very little documentation on this for the Arduino and I could not find a good library to help out. So here it is!

There are som tutorials that use what is called a "bubble sort". This works great on the Arduino because it uses very little memory. This library uses an algorithm called "insertion sort" because I have learned that it is even smaller, and also a little bit faster.

I have built this library for the Arduino. I have tested it in the Arduino IDE, run it on an Arduino Pro Mini, and I focus on a small memory footprint. You don't want to waste those precious memory bytes! It will work great for arrays up to a few thousand elements, which is all you need on an Arduino.

## Let's get going!

### Easy

This is almost always what you want:

    sortArray(array, 10);
	
This will sort an array of 10 elements. Works with `int`, `float`, `bool`, `char`, `String` and `char*`.

To sort in reverse:

    sortArrayReverse(array, 10);

### Custom comparison function

You can build your own comparison function. The function should take as arguments two of your elements and return `true` if the first argument is considered larger than the second. Return `false` if the second argument is larger than the first, or if they are equal.

Your comparison function takes two elements. **Example**:

    bool firstIsLarger(int a, int b) {
      if (a > b) {
        return true;
      } else {
	    return false;
	  }
    }
    
    sortArray(array, 10, firstIsLarger);
	
To sort in reverse:

    sortArrayReverse(array, 10, firstIsLarger);

## Benchmarks

I ran this benchmarks on a 16 MHz Arduino Pro Mini. Sizes are estimates.

### 2 elements

sort2 is specialized for two-element arrays: it is a macro with a simple ìf` statement.

| Sorting method      | Compiled size |
+---------------------+---------------+
| Baseline, no sort   | 2 326 bytes   |
+---------------------+---------------+
| qsort, standard lib | 3 510 bytes   |
| gnome sort 2        | 2 388 bytes   |
| bubblesort          | 2 354 bytes   |
| sort2               | 2 344 bytes   |
| insertion sort      | 2 344 bytes   |

### 3 elements

sort3 is specialized for three-element arrays, similar to sort2

| Sorting method      | Compiled size |
+---------------------+---------------+
| Baseline, no sort   | 2 352 bytes   |
+---------------------+---------------+
| qsort, standard lib | 3 536 bytes   |
| gnome sort 2        | 2 448 bytes   |
| bubblesort          | 2 426 bytes   |
| sort3               | 2 416 bytes   |
| insertion sort      | 2 396 bytes   |

### 20 elements

| Sorting method      | Compiled size |
+---------------------+---------------+
| Baseline, no sort   | 2 322 bytes   |
+---------------------+---------------+
| qsort, standard lib | 3 504 bytes   |
| gnome sort 2        | 2 400 bytes   |
| bubblesort          | 2 370 bytes   |
| insertion sort      | 2 364 bytes   |

### Conclusion

According to the benchmark insertion sort is always smallest. This is great news! It means we can use it for everything. But why is it minimal? How can it be as small as a specialized sorting function? The reason is that the Arduino IDE optimizes the code. When it detects that we are rying to sort only a fixed number of elements (2, 3, ...) it removes code paths that are unused. These optimizations are based on decades of computer science research, some of them are very clever.

You can always use the `sortArray` function, for small or large arrays. It will always be optimal in size for your use case.

Insertion sort is pretty fast for elements up to a few hundred elements or so, maybe 1000. For really large arrays you might want to look into `qsort` instead. But such large arrays will not fit in the Arduino memory anyway so we don't care about that case.
