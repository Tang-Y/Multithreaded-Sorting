#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_INT 999
#define MAX_ARRAY_SIZE 500

// Structure to pass parameters to threads
typedef struct {
    int starting_index;
    int ending_index;
    int* array;
} ThreadParams;

// method declaration
void *sorter(void *params);
void *merger(void *params);

int unsortedArray[MAX_ARRAY_SIZE]; // unsorted array
int sortedArray[MAX_ARRAY_SIZE]; // sorted array
int total; // Total number of integers

int main() {
    FILE *file = fopen("IntegerList.txt", "r"); // open file in c
    if (file == NULL) {
        perror("Error opening the input file");
        return 1;
    }

    total = 0;
    char line[1000]; //store int values
    if (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ","); // split by comma
        while (token != NULL) {
            unsortedArray[total] = atoi(token);
            total++;
            token = strtok(NULL, ",");
        }
    }

    fclose(file);

    pthread_t sortingThread1, sortingThread2, mergingThread; // three thread ids

    // Divide the array into two sub-arrays
    int middle = total / 2;

    ThreadParams params1 = {0, middle - 1, unsortedArray}; // first thread paras
    ThreadParams params2 = {middle, total - 1, unsortedArray}; // second thread paras

    /* create the first sorting thread */
    pthread_create(&sortingThread1, NULL, sorter, &params1); 

    /* create the first sorting thread */
    pthread_create(&sortingThread2, NULL, sorter, &params2); 

    /* now wait for the 2 sorting threads to finish*/
    pthread_join(sortingThread1, NULL);
    pthread_join(sortingThread2, NULL);

    ThreadParams paramsMerge = {0, total - 1, unsortedArray}; // pass parameters

    // Create the merging thread
    pthread_create(&mergingThread, NULL, merger, &paramsMerge);

    // Wait for the merge thread to finish
    pthread_join(mergingThread, NULL);

    // Output the sorted array to a file
    FILE *outputFile = fopen("SortedIntegerList.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening the output file");
        return 1;
    }

    for (int i = 0; i < total; i++) {
        fprintf(outputFile, "%d", sortedArray[i]);
        if (i < total - 1) {
            fprintf(outputFile, ",");
        }
    }
    fprintf(outputFile, "\n");
    fclose(outputFile);

    return 0;
}

// insertion sort
// the sorting method to sort each sub-list
// the sorted array after is also on unsorted array that contains the two sub-sorted-list
void *sorter(void *params) {
    ThreadParams *param = (ThreadParams *)params;

    for (int i = param->starting_index + 1; i <= param->ending_index; i++) { // iterate each half and comparison
        int key = param->array[i];
        int j;
        for (j = i; j > param->starting_index && param->array[j - 1] > key; j--) {
            param->array[j] = param->array[j - 1];
        }
        param->array[j] = key;
    }
    pthread_exit(NULL); 
}

// the Merge method that merge two already sorted array
void *merger(void *params) {
    ThreadParams *param = (ThreadParams *)params;
    int* sortedSubArray = param->array; // unsorted array with two sorted-sub-list
    int middle = (param->starting_index + param->ending_index) / 2;
    int start1 = param->starting_index;
    int start2 = middle + 1;

    // final sorting
    for (int k = param->starting_index; k <= param->ending_index; k++) {
        if (start1 <= middle && (start2 > param->ending_index || sortedSubArray[start1] <= sortedSubArray[start2])) {
            sortedArray[k] = sortedSubArray[start1++]; // asign the sorted value to sorted array
        } else {
            sortedArray[k] = sortedSubArray[start2++]; // asign the sorted value to sorted array
        }
    }
    
    pthread_exit(NULL);
}
