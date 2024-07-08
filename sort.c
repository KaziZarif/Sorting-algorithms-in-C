#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 4

typedef struct {
    int *a;
    int left;
    int right;
} ThreadArgs;

pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 0;


void *merge_sort_thread(void *args);
void merge_sort_recursion(int a[], int left, int right);
void merge_sorted_arrays(int a[], int left, int middle, int right);

void insertion_sort(int a[], int length);
void selection_sort(int a[], int length);
void bubble_sort(int a[], int length);



//merge sort
void merge_sort(int a[], int length) {
    merge_sort_recursion(a, 0, length - 1);
}

//merge sort with threads
void* merge_sort_thread(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    merge_sort_recursion(targs->a, targs->left, targs->right);
    free(targs);

    pthread_mutex_lock(&thread_count_mutex);
    thread_count--;
    pthread_mutex_unlock(&thread_count_mutex);

    return NULL;
}

void merge_sort_recursion(int a[], int left, int right) {
    
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    //parallel part
    pthread_t left_thread, right_thread;
    ThreadArgs* left_args = NULL;
    ThreadArgs* right_args = NULL; 
    int create_left_thread = 0;
    int create_right_thread = 0;
    
    pthread_mutex_lock(&thread_count_mutex);
    if (thread_count < MAX_THREADS) {
        left_args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        if (left_args == NULL) {
            printf("memory allocation failed\n");
            exit(1);
        }
        thread_count++;
        create_left_thread = 1;
        left_args->a = a;
        left_args->left = left;
        left_args->right = middle;
    }   
    if (thread_count < MAX_THREADS) {
        right_args = (ThreadArgs*)malloc(sizeof(ThreadArgs));
        if (right_args == NULL) {
            printf("memory allocation failed\n");
            exit(1);
        }
        thread_count++;
        create_right_thread = 1;
        right_args->a = a;
        right_args->left = middle + 1;
        right_args->right = right;
    }
    pthread_mutex_unlock(&thread_count_mutex);

    if (create_left_thread) {
        if(pthread_create(&left_thread, NULL, merge_sort_thread, left_args) != 0) {
            printf("pthread create error\n");
            exit(1);
        }
    } else{
        merge_sort_recursion(a, left, middle);
    }

    if (create_right_thread) {
        if(pthread_create(&right_thread, NULL, merge_sort_thread, right_args) != 0) {
            printf("pthread create error\n");
            exit(1);
        }
    } else {
        merge_sort_recursion(a, middle + 1, right);
    }

    if (create_left_thread) {
        pthread_join(left_thread, NULL);
    }   

    if (create_right_thread) {
        pthread_join(right_thread, NULL); 
    }

    //sequential part
    // merge_sort_recursion(a, left, middle);
    // merge_sort_recursion(a, middle + 1, right);

    merge_sorted_arrays(a, left, middle, right);
}


void merge_sorted_arrays(int a[], int left, int middle, int right) {
    int left_length = middle - left + 1;
    int right_length = right - middle;

    int *temp_left = (int*)malloc(left_length * sizeof(int));
    int *temp_right = (int*)malloc(right_length * sizeof(int));

    if (temp_left == NULL || temp_right == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int i, j, k;

    for (i = 0; i < left_length; i++) {
        temp_left[i] = a[left + i];
    }

    for(int i = 0; i < right_length; i++) {
        temp_right[i] = a[middle + 1 + i];
    }

    for (i = 0, j = 0, k = left; k <= right; k++) {
        if ( (i < left_length) && (j >= right_length || temp_left[i] <= temp_right[j]) ) {
            a[k] = temp_left[i];
            i++;
        } else {
            a[k] = temp_right[j];
            j++;
        }
    }

    free(temp_left);
    free(temp_right);
}


//insertion sort
void insertion_sort(int a[], int length) {

    for (int i = 1; i < length; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

//selection_sort
void selection_sort(int a[], int length) {

    for (int i = 0; i < length - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < length; j++) {
            if (a[j] < a[min_index]) {
                min_index = j;
            }
        }
        int temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}


void bubble_sort(int a[], int length) {

    for(int i = 0; i < length - 1; i++) {
        for(int j = 0; j < length - i - 1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}