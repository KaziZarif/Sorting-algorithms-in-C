# Sort
Some sorting algorithms I created in C

Supports merge sort, parallelized merge sort, insertion sort, selection sort and bubble sort. 

Merge sort is an O(n log n) comparison-based sorting algorithm. It uses a divide and conquer approach to effi

## Features
- Merge sort
- Parallelized merge sort
- Insertion sort
- Selection sort
- Bubble sort

## Usage
To use the sorting algorithms, include `sort.h` at the top of your program and call the desired sorting function:

```c
#include "sort.h"

// Example usage
int array[] = {5, 3, 8, 4, 2};
int length = sizeof(array) / sizeof(array[0]);

merge_sort(array, length);          // Merge sort
insertion_sort(array, length);      // Insertion sort
selection_sort(array, length);      // Selection sort
bubble_sort(array, length);         // Bubble sort


## Compilation

gcc -o yourProgram yourProgram.c sort.c -lpthread