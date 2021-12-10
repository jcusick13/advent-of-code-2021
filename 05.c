#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputs/05.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SIZE 10
#define N_COORDS 4

int** generateCoords(int x1, int y1, int x2, int y2, int *n) {

    // Create array of pointer-to-pointer-to-int
    int **coord_pairs;
    int n_pairs = 0;
    int array_size = 1;
    coord_pairs = malloc(sizeof(int *) * n_pairs);
    assert(coord_pairs != NULL);
    printf("Created coord pairs array\n");

    // Allocate initial length-2 arrays for individual coords
    for (int i = 0; i < array_size; i++) {
        coord_pairs[i] = malloc(sizeof(int) * 2);
        assert(coord_pairs[i] != NULL);
        coord_pairs[i][0] = -1;
        coord_pairs[i][1] = -1;
    }
    printf("Allocated values for each row of coord pairs\n");

    if (x1 != x2 && y1 != y2) {
        printf("Neither X or Y equal\n");
        return coord_pairs;
    }

    if (x1 == x2) {
        printf("X's equal\n");
        int range = abs(y1 - y2);
        int start = MIN(y1, y2);
        int cell = 0;
        for (int y = start; y <= (start + range); y++) {
            if ((cell + 1) > array_size) {
                // Expand size `coord_pairs
                array_size *= 2;
                printf("Reallocating array of Xs to %d pairs\n", array_size);
                coord_pairs = realloc(coord_pairs, sizeof(int *) * array_size);
                assert(coord_pairs != NULL);
                for (int i = (array_size / 2); i < array_size; i++) {
                    coord_pairs[i] = malloc(sizeof(int) * 2);
                    assert(coord_pairs[i] != NULL);
                }
            }
            printf("Adding coords (%d, %d)...", x1, y);
            coord_pairs[cell][0] = x1;
            coord_pairs[cell][1] = y;
            n_pairs++;
            cell++;
            printf(" Finished\n");
        }
        printf("Finished coord pairs\n");
    }

    if (y1 == y2) {
        printf("Y's equal\n");
        int range = abs(x1 - x2);
        int start = MIN(x1, x2);
        int cell = 0;
        for (int x = start; x <= (start + range); x++) {
            if ((cell + 1) > array_size) {
                // Expand size `coord_pairs
                array_size *= 2;
                printf("Reallocating array of Ys to %d pairs\n", array_size);
                coord_pairs = realloc(coord_pairs, sizeof(int *) * array_size);
                assert(coord_pairs != NULL);
                for (int i = (array_size / 2); i < array_size; i++) {
                    coord_pairs[i] = malloc(sizeof(int) * 2);
                    assert(coord_pairs[i] != NULL);
                }
            }
            printf("Adding coords (%d, %d)...", x, y1);
            coord_pairs[cell][0] = x;
            coord_pairs[cell][1] = y1;
            n_pairs++;
            cell++;
            printf(" Finished\n");
        }
        printf("Finished coord pairs\n");
    }

    *n = n_pairs;
    return coord_pairs;
}


int main() {
    const unsigned char *s = input;
    int board[SIZE][SIZE];
    int coords[N_COORDS];
    int n = 0;
    int x1, y1, x2, y2;

    // Initialize board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }

    while (*s != '\0') {
        // Reset coordinate tracker
        for (int i = 0; i < N_COORDS; i++) {
            coords[i] = 0;
        }

        // Read input coordinates for a single line
        while (*s != '\n') {
            while (*s < '0' || *s > '9') s++;
            while (*s >= '0' && *s <= '9') {
                coords[n % N_COORDS] = (coords[n % N_COORDS] * 10) + (*s - '0');
                s++;
            }
            n++;
        }
        s++;

        x1 = coords[0];
        y1 = coords[1];
        x2 = coords[2];
        y2 = coords[3];

        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) break;

        printf("\nProcessing (%d, %d) -> (%d, %d)\n", x1, y1, x2, y2);
        // TODO: Avoid writing last entry of (0, 0) -> (0, 0)


        // Draw line onto board
        int **coord_pairs;
        int x, y;
        int n_pairs = 0;
        coord_pairs = generateCoords(x1, y1, x2, y2, &n_pairs);
        printf("%d pairs available to add to board\n", n_pairs);
        for (int i = 0; i < n_pairs; i++) {
            x = coord_pairs[i][0];
            y = coord_pairs[i][1];
            if (x == -1 && y == -1) continue;
            printf("Adding (%d, %d) to the board\n", x, y);
            board[x][y]++;
        }
    }
    printf("Done adding coords to the board\n");

    int overlaps = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] >= 2) overlaps++;
        }
    }

    printf("%d overlaps\n", overlaps);

    return 0;
}
