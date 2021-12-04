#include <math.h>
#include <stdio.h>
#include <string.h>
#include "inputs/03.h"

#define N_BITS 5
#define N_ROWS 12

struct Counter {
    int zero, one;
};

int initEmptyCounter(struct Counter *counter) {
    counter->zero = 0;
    counter->one = 0;

    return 0;
};

int binaryToDecimal(int binary[], int n) {
    int decimal = 0;
    int base = 1;
    for (int i = (n - 1); i >= 0; i--) {
        decimal += binary[i] * base;
        base *= 2;
    }
    
    return decimal;
}

struct Counter * countBitFreqs(int report[N_ROWS][N_BITS]){
    /* Create array of length `N_BITS` with a `Counter`
     * struct in each cell
     */

    // Establish array of `Counter`s with zeroed starting values
    static struct Counter bit_counts[N_BITS];
    for (int i = 0; i < N_BITS; i++) {
        initEmptyCounter(&bit_counts[i]);
    }

    // Tally all input data per bit-column
    for (int row = 0; row < N_ROWS; row++) {
        for (int bit = 0; bit < N_BITS; bit++) {
            if (report[row][bit] == 0) {
                bit_counts[bit].zero += 1;
            }
            else if (report[row][bit] == 1) {
                bit_counts[bit].one += 1;
            }
            else continue;
        }
    }

    return bit_counts;
}

int powerConsumption(int report[N_ROWS][N_BITS]) {
    struct Counter *bit_counts;
    bit_counts = countBitFreqs(report);

    // Build up gamma and epsilon as arrays
    int binary_gamma[N_BITS];
    int binary_epsilon[N_BITS];
    for (int i = 0; i < N_BITS; i++) {
        if (bit_counts[i].zero > bit_counts[i].one) {
            binary_gamma[i] = 0;
            binary_epsilon[i] = 1;
        }
        else {
            binary_gamma[i] = 1;
            binary_epsilon[i] = 0;
        }
    }

    int gamma = binaryToDecimal(binary_gamma, N_BITS);
    int epsilon = binaryToDecimal(binary_epsilon, N_BITS);
    int power_consumption = gamma * epsilon;

    return power_consumption;
}

int main() {
    const unsigned char *s = input;
    int report[N_ROWS][N_BITS];
    int cell = 0;

    // Read inputs into 2d array as integers
    int row;
    while (*s != '\0') {
        if (*s == '\n') s++;
        row = (int)floor(cell / N_BITS);
        report[row][cell % N_BITS] = (*s - '0');
        cell++;
        s++;
    }

    int power_consumption = powerConsumption(report);
    printf("Power consumption: %d\n", power_consumption);

    return 0;
}
