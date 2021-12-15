#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputs/07.h"

void addElement(int** array, int element, int* n, int* array_size) {
    if ((*n + 1) > *array_size) {
        *array_size *= 2;
        (*array) = realloc((*array), sizeof(int) * *array_size);
        assert((*array) != NULL);

        for (int i = *array_size / 2; i < *array_size; i++) {
            (*array)[i] = 0;
        }
    }

    (*array)[*n] = element;
    *n += 1;
}


int compare(const void* a, const void* b) {
     int int_a = * ((int*)a);
     int int_b = * ((int*)b);

     if (int_a == int_b) return 0;
     else if (int_a < int_b) return -1;
     else return 1;
}

int median(int** array, int n) {
    qsort((*array), n, sizeof(int), compare);
    
    // Avoid averaging middle two numbers
    return (*array)[n / 2];
}


int main() {
    const unsigned char *s = input;
    int array_size = 2;
    int *crabs;
    int n_crabs = 0;

    crabs = malloc(sizeof(int) * array_size);
    assert(crabs != NULL);
    memset(crabs, 0, sizeof(int) * array_size);

    // Read in crab locations
    while (*s != '\0') {
        int value = 0;
        //while (*s < '0' || *s > '9') s++;
        while (*s >= '0' && *s <= '9') {
            value = (value * 10) + (*s - '0');
            s++;
        }
        addElement(&crabs, value, &n_crabs, &array_size);
        if (*s == '\n') break;
        s++;
    }

    int center;
    center = median(&crabs, n_crabs);
    printf("Center: %d\n", center);

    int total_fuel = 0;
    for (int i = 0; i < n_crabs; i++) {
        total_fuel += abs(crabs[i] - center);
    }

    printf("Central crab: %d, Total fuel: %d\n", center, total_fuel);
    return 0;
}
