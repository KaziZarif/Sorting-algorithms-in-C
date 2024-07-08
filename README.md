# Merge sort and other algorithms
Some sorting algorithms I created in C

Includes merge sort with multithreading

Merge sort is an efficient, stable, comparison-based sorting algorithm with a time complexity of O(n log n). It uses a divide and conquer approach to efficiently sort an array.

1. **Divide**: Split the array into two halves.
2. **Conquer**: Recursively sort each half.
3. **Combine**: Merge the two sorted halves into a single sorted array.

The conquer step can be parallelized to significantly speed up the sorting process, especially for large datasets. The parallelized version uses multiple threads to sort the subproblems concurrently.

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

```
You can change the number of threads utilized depending on your CPU by modifying this number 

```c 
#define MAX_THREADS 4
```

If you want to use the sequential version of merge sort, comment out the parallel section in the merge_sort_recursion function 
and uncomment the sequential part.

```c
//sequential part
merge_sort_recursion(a, left, middle);
merge_sort_recursion(a, middle + 1, right);

```


## Compilation

To compile your program with the sorting functions, use the following command:

```sh
gcc -o yourProgram yourProgram.c sort.c -lpthread