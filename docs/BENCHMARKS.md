# Benchmarks

To make ArduinoSort I ran a series of tests to find the smallest sort algorithm. You do not need to read this to use ArduinoSort.

I ran these benchmarks on a 16 MHz Arduino Pro Mini. Sizes are estimates.

## 2 elements

sort2 is specialized for two-element arrays: it is a macro with a simple ìf` statement.

| Sorting method      | Compiled size |
| ------------------- | ------------- |
| Baseline, no sort   | 2 326 bytes   |
| qsort, standard lib | 3 510 bytes   |
| gnome sort 2        | 2 388 bytes   |
| bubblesort          | 2 354 bytes   |
| sort2               | 2 344 bytes   |
| insertion sort      | 2 344 bytes   |

## 3 elements

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
