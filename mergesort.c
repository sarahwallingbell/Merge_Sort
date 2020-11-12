# include <stdio.h>
#include <time.h>
void *malloc(size_t size);
int atoi(const char *str);
void srand(unsigned int seed);
int rand(void);
void free(void *ptr);
void mergesort(int* array, int* auxArray, int left, int right);
int *makeArray(int size);
void printArray(int *array, int size);
void copyArray(int *fromArray, int* toArray, int leftBound, int rightBound);
/**
 Sarah Walling-Bell
 September 5, 2018
 CS 281 Homework 1: Mergesort in C

 Mergesort.c creates an unsorted array of random numbers (ranging between 0 and size-1 of array) and perfoms mergesort to sort the array.
 If the array is of size <= 100, it prints the array before and after sorting.
 Regardless of array size, it prints the time taken to sort the array in ms.

@param argc argument count
@param argv the size of the array to be generated and sorted via mergesort.
 **/
int main(int argc, char **argv){
    //declare clock variables
    clock_t start, end, duration;

    //If no array size is input by the user, print error message and terminate.
    if(argc == 1){ //no command line arg passed, print out error message and terminate
        printf("Try again! Please input the size of the array to be sorted.\n");
    }
    //If user inputs array size, create such an array and sort it using mergesort.
    else{
        //parse argv into an int that is the size of the array to be created
        int size = atoi(argv[1]);

        //make an array with with specified input size
        int *unsortedArray = makeArray(size);

        //fill array with random numbers
        //seed random number generator
        srand(time(0));
        //popuate the unsorted array with random numbers
        for (int i = 0; i < size; i++){
            //generate random vals ranging from 0 to size-1 of the array and adds them to array
            unsortedArray[i] = rand()%size;
        }

        //make an auxiliary array that is half the size of the unsorted array
        int half = (int) size/2;
        int *auxArray = makeArray(half);

        //print a sorting statement indicating the size of the array being sorted
        printf("Sorting an array of size %d ...\n", size);

        //print the unsorted array if its size is 100 or less
        if(size <= 100){
            printf("Before: ");
            printArray(unsortedArray, size);
        }

        //get time before sorting
        start = clock();


        //call mergesort function to recursively sort the unsorted array
        mergesort(unsortedArray, auxArray, 0, size);

        //get time after sorting
        end = clock();

        //get duration of sorting in ms
        duration = (double)(end - start);
        //duration = (double)(end - start) / CLOCKS_PER_SEC * 1000;

        //print out sorted array if its size is 100 or less
        if(size <= 100){
            printf("After: ");
            printArray(unsortedArray, size);
        }

        //print elapsed sorting time
        printf("Time elapsed: %lu ms\n", duration);

        //delete the sorted and auxiliary array from heap
        free(unsortedArray);
        free(auxArray);

    }
}


/**
 Recursively divides the input array into left and right subarrays. Copies the left subarray into an auxiliary array, and merges the auziliary and right subarray together to create a single sorted array.

 @param array the list to be sorted
 @param auxArray the auxiliary array
 @param left the start index of the array
 @param right the end index of the array
 **/
void mergesort(int* array, int* auxArray, int left, int right){

    //get the midpoint of the array
    int midpoint = left + ((right - left) / 2);

    //recurse on left half of array
    if(midpoint - left > 1){
        mergesort(array, auxArray, left, midpoint);
    }

    //recurse on right half of array
    if(right - midpoint > 1){
        mergesort(array, auxArray, midpoint, right);
    }

    //copy the left array into auxiliary array
    copyArray(array, auxArray, left, midpoint);

    //merge auxiliary array and right half of unsorted array into the unsorted (now being sort) array
    int auxArraySize = midpoint-left;
    int j = midpoint;
    int k = left;
    int i = 0;
    //loop through auxArray and the unsorted array and compare their ith elements. Add the smaller element into the array being sorted.
    while (i < auxArraySize && j < right){
        if(auxArray[i] < array[j]){
            array[k] = auxArray[i];
            i++;
        }
        else{
            array[k] = array[j];
            j++;
        }
        k++;
    }

    //Add leftover int if arrays are uneven sized
    while (i < auxArraySize){
        array[k] = auxArray[i];
        i++;
        k++;
    }

    //Add leftover int if arrays are uneven sized
    while(j < right){
        array[k] = array[j];
        j++;
        k++;
    }

}


/**
 Creates an array with input size from the heap.

 @param size the size of the array to be created
 @return array created array
 **/
int *makeArray(int size){
    //allocate an array of length "size" from the heap
    int *array = (int *) malloc(size*sizeof(int));

    return array;
}

/**
 Prints an input array in brackets with element separated by commas.

 @param array the array to print out
 @param size the size of the array to print out
 **/
void printArray(int *array, int size){
    printf("[");
    for(int i = 0; i < size; i++){
        if (i!=0) printf(",");
        printf("%d", array[i]);
    }
    printf("]\n");
}

/**
 Copies array segment from one array into another target array.

 @param fromArray the array elements are copied from
 @param toArray the array elements are copied to
 @param leftBound the first element in fromArray to be copied
 @param rightBound is 1 + the last element in fromArray to be copied
 **/
void copyArray(int *fromArray, int* toArray, int leftBound, int rightBound){
    int j = 0;
    for(int i = leftBound; i < rightBound; i++){
        toArray[j] = fromArray[i];
        j++;
    }
}
