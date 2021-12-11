#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputs/06.h"

void runTimestep(int **fish, int *n, int *array_size) {
    int fish_to_add = 0;
    for (int f = 0; f < *n; f++) {
        if ((*fish)[f] > 0) {
            (*fish)[f] -= 1;
            continue;
        }
        else {
            (*fish)[f] = 6;
            fish_to_add++;
        }
    }

    for (int i = 0; i < fish_to_add; i++) {
        if ((i + *n + 1) > *array_size) {
            *array_size *= 2;
            (*fish) = realloc((*fish), sizeof(int) * *array_size);
            assert((*fish) != NULL);
            for (int j = *array_size / 2; j < *array_size; j++) {
                (*fish)[j] = 0;
            }
        }
        (*fish)[*n + i] = 8;
    }
    *n += fish_to_add;
}

int main() {
    const unsigned char *s = input;
    int array_size = 2;
    int *fish;
    int n = 0;

    fish = malloc(sizeof(int) * array_size);
    assert(fish != NULL);
    memset(fish, 0, sizeof(int) * array_size);

    while (*s != '\0') {
        if ((n + 1) > array_size) {
            array_size *= 2;
            fish = realloc(fish, sizeof(int) * array_size);
            assert(fish != NULL);
            for (int i = array_size / 2; i < array_size; i++) {
                fish[i] = 0;
            }
        }

        // Read in existing lanternfish timings
        while (*s < '0' || *s > '9') s++;
        while (*s >= '0' && *s <= '9') {
            fish[n] = (fish[n] * 10) + (*s - '0');
            s++;
        }
        n++;
        if (*s == '\n') break;
    }

    printf("Final array: %d, final fish %d\n", array_size, n);
    

    for (int time = 0; time < 80; time++) {
        runTimestep(&fish, &n, &array_size);
    }

    printf("Total fish: %d\n", n);
    return 0;
}
