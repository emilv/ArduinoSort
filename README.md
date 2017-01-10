# ArduinoSort
Easy sorting functions for Arduino, with focus on low memory footprint.

**NOTE: THIS IS NOT DONE YET**

## Why?

Sometimes you need to sort an array of numbers or strings. There is very little documentation on this for the Arduino and I could not find a good library to help out.

A lot of tutorials use what is called a "bubble sort". This is a very inefficient algorithm, but it works for small arrays and is easy to understand. But I don't want to code a bubble sort every time I need to sort something. I want something I can reuse, and that I know will use as little memory as possible.

This library is specially built for the Arduino. I have tested it in the Arduino IDE, run it on an Arduino Pro Mini, and I focus on a small memory footprint. You don't want to waste those precious memory bytes! Most optimizations are for small datasets with less than 20 elements, but even for larger arrays we provide some functions that fall back to the (almost unknown!) quicksort that is shipped with Arduino.

## Let's get going!

There are multiple methods to choose from. Don't worry, only the ones you use will be uploaded to your Ardunio. The reason to have multiple methods is that they target slightly different use cases.

### Easy

Use this if you are unsure. It almost always works:

    sort(array, 10, int);
	
This will sort an int array of 10 elements. The last parameter is the name of your type. Works with `int`, `float`, `bool` and `String`.

To sort in reverse:

    sort_rev(array, 10, int);

### Small arrays, little memory

If you know that your array is small you can use a smaller but slower algorithm, because the speed will not matter. Use this if you have less than about 100 elements:

    sort_small(array, 42, String);
	
Works with `int`, `float`, `bool` and `String`.

To sort in reverse:

    sort_small_rev(array, 42, String);

### Known size, less memory

If you already know how large your array is, and it is at most 8 elements. There is a different function for each size of the array. These have very low memory footprint and are also very fast.

    sort2(array, float);
    sort3(array, float);
	sort4(array, float);
	sort5(array, float);
	sort6(array, float);
	sort7(array, float);
	sort8(array, float);
	
Works with `int`, `float`, `bool` and `String`.

To sort in reverse:

    sort2_rev(array, float);
	sort3_rev(array, float);
	sort4_rev(array, float);
	sort5_rev(array, float);
	sort6_rev(array, float);
	sort7_rev(array, float);
	sort8_rev(array, float);
	
### Sort arrays of char*

The Arduino typically uses the `String` type for strings. But there are some libraries and use cases where you use the type `char*` instead. These cannot be sorted by the above methods. Use this function to sort char*:

    sort_char(array, 13);
   
Works with `char*`.

To sort in reverse:

    sort_char_rev(array, 13);
	
### Sort strings with international characters such as å

This function lets you specify in what order each character should be sorted:

    sort_local(array, 32, String, "abcdefghijklmnopqrstuvwxyzåäö");
	
Works with `String` and `char*`.

To sort in reverse:

    sort_local_rev(array, 32, String, "abcdefghijklmnopqrstuvwxyzåäö");
	
### Multidimensional array

TBD

### Sort multiple arrays simultaneously by the first

TBD

### Custom comparison function

You can build your own comparison function. The function should take as arguments two of your elements and return a value indicating if one is smaller or larger than the other. It should return a value less than 0 if the first is smaller then the second, larger than 0 if the first is larger than the second, or 0 if they are equal.

There are multiple variations on this sort method, because you may have different needs.

#### Custom easy

Your comparison function takes two elements of a known type. Example:

    int compare_ints(int a, int b) {
      if (a > b) {
        return 1;
      }
      if (a < b) {
        return -1;
      }
      return 0;
    }
    
    usort_easy(array1, 10, int, compare_ints);

#### Custom, flexible, uses pointers

A more flexible version of the above that uses pointers instead of copying the elements. This is useful for your own types such as structs, but generally not for simple types such as `int` or `float`:

    int compare_intp(int* a, int* b) {
	  if (*a > *b) {
	    return 1;
	  }
      if (*a < *b) {
        return -1;
      }
      return 0;
    }
    
    usort_easy(array1, 10, int, compare_intp);



## Choosing a method

If you are sorting more than about five arrays you should choose one method that fits all the arrays. This is because "small" versions are actually copied right into where they are used. Having sort2, sort4, sort_small AND the regular sort is just wasteful. Choose sort_small if you have to sort in multiple places in your code.

## Benchmarks

I ran this benchmarks onz a 16 MHz Arduino Pro Mini. Sizes are estimates. Bubble sort included for comparison.

Columns: Name, Compiled size, Memory peak, Runtime (micros)


### 2 elements

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
