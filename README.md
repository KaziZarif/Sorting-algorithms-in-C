# Sort
Some sorting algorithms I created in C

Supports merge sort, parallelized merge sort, insertion sort, selection sort and bubble sort. 

Merge sort is an O(n log n) comparison-based sorting algorithm. It uses a divide and conquer approach to effi

To use - 
Include "sort.h" at the top of your program and,

merge_sort(array, array length);   for merge sort
insertion_sort(array, ARRAY_SIZE);  for insertion sort
selection_sort(array, ARRAY_SIZE); for selection sort 


For sequential merge sort, comment out the parallel part in merge_sort_recursion function and uncomment the sequential part. 

Compiling: 
gcc -o yourProgram yourProgram.c sort.c -lpthread