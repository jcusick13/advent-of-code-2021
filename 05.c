#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "inputs/05.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SIZE 1000
#define N_COORDS 4

int** generateCoords(int x1, int y1, int x2, int y2, int *n) {

    // Create array of pointer-to-pointer-to-int
    int **coord_pairs;
    int n_pairs = 0;
    int array_size = 1;
    coord_pairs = malloc(sizeof(int *) * n_pairs);
    assert(coord_pairs != NULL);

    // Allocate initial length-2 arrays for individual coords
    for (int i = 0; i < array_size; i++) {
        coord_pairs[i] = malloc(sizeof(int) * 2);
        assert(coord_pairs[i] != NULL);
        coord_pairs[i][0] = -1;
        coord_pairs[i][1] = -1;
    }

    if (x1 != x2 && y1 != y2) {
        int range = abs(y1 - y2);
        int start_x, start_y, end_x, x_mult;
        // Determine lowest point on grid and which x direction to travel
        if (y1 > y2) {
            start_x = x1;
            end_x = x2;
            start_y = y1;
        }
        else {
            start_x = x2;
            end_x = x1;
            start_y = y2;
        }
        if (start_x > end_x) {
            x_mult = -1;
        }
        else {
            x_mult = 1;
        }

        int cell = 0;
        for (int increment = 0; increment <= range; increment++) {
            if ((cell + 1) > array_size) {
                array_size *= 2;
                coord_pairs = realloc(coord_pairs, sizeof(int *) * array_size);
                assert(coord_pairs != NULL);
                for (int i = (array_size / 2); i < array_size; i++) {
                    coord_pairs[i] = malloc(sizeof(int) * 2);
                    assert(coord_pairs[i] != NULL);
                }
            }
            coord_pairs[cell][0] = start_x + (increment * x_mult);
            coord_pairs[cell][1] = start_y - increment;
            n_pairs++;
            cell++;
        }
    }

    if (x1 == x2) {
        int range = abs(y1 - y2);
        int start = MIN(y1, y2);
        int cell = 0;
        for (int y = start; y <= (start + range); y++) {
            if ((cell + 1) > array_size) {
                array_size *= 2;
                coord_pairs = realloc(coord_pairs, sizeof(int *) * array_size);
                assert(coord_pairs != NULL);
                for (int i = (array_size / 2); i < array_size; i++) {
                    coord_pairs[i] = malloc(sizeof(int) * 2);
                    assert(coord_pairs[i] != NULL);
                }
            }
            coord_pairs[cell][0] = x1;
            coord_pairs[cell][1] = y;
            n_pairs++;
            cell++;
        }
    }

    if (y1 == y2) {
        int range = abs(x1 - x2);
        int start = MIN(x1, x2);
        int cell = 0;
        for (int x = start; x <= (start + range); x++) {
            if ((cell + 1) > array_size) {
                // Expand size `coord_pairs`
                array_size *= 2;
                coord_pairs = realloc(coord_pairs, sizeof(int *) * array_size);
                assert(coord_pairs != NULL);
                for (int i = (array_size / 2); i < array_size; i++) {
                    coord_pairs[i] = malloc(sizeof(int) * 2);
                    assert(coord_pairs[i] != NULL);
                }
            }
            coord_pairs[cell][0] = x;
            coord_pairs[cell][1] = y1;
            n_pairs++;
            cell++;
        }
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

        // Draw line onto board
        int **coord_pairs;
        int x, y;
        int n_pairs = 0;
        coord_pairs = generateCoords(x1, y1, x2, y2, &n_pairs);
        for (int i = 0; i < n_pairs; i++) {
            x = coord_pairs[i][0];
            y = coord_pairs[i][1];
            if (x == -1 && y == -1) continue;
            board[x][y]++;
        }
    }

    int overlaps = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] >= 2) overlaps++;
        }
    }

    printf("%d overlaps\n", overlaps);

    return 0;
}
