#include <math.h>
#include <stdio.h>
#include <string.h>
#include "inputs/03.h"

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

int main() {
    const unsigned char *s = input;
    int n_rows = 1000;
    int n_bits = 12;
    int report[n_rows][n_bits];
    int cell = 0;

    // Read inputs into 2d array as integers
    int row;
    while (*s != '\0') {
        if (*s == '\n') s++;
        row = (int)floor(cell / n_bits);
        report[row][cell % n_bits] = (*s - '0');
        cell++;
        s++;
    }

    // Establish array of `Counter`s with zeroed starting values
    struct Counter bit_counts[n_bits];
    for (int i = 0; i < n_bits; i++) {
        initEmptyCounter(&bit_counts[i]);
    }

    // Tally all input data per bit-column
    for (int row = 0; row < n_rows; row++) {
        for (int bit = 0; bit < n_bits; bit++) {
            if (report[row][bit] == 0) {
                bit_counts[bit].zero += 1;
            }
            else if (report[row][bit] == 1) {
                bit_counts[bit].one += 1;
            }
            else {
                return -1;
            }
        }
    }

    // Build up gamma and epsilon as arrays
    int binary_gamma[n_bits];
    int binary_epsilon[n_bits];
    for (int i = 0; i < n_bits; i++) {
        if (bit_counts[i].zero > bit_counts[i].one) {
            binary_gamma[i] = 0;
            binary_epsilon[i] = 1;
        }
        else {
            binary_gamma[i] = 1;
            binary_epsilon[i] = 0;
        }
    }

    int gamma = binaryToDecimal(binary_gamma, n_bits);
    int epsilon = binaryToDecimal(binary_epsilon, n_bits);
    int power_consumption = gamma * epsilon;

    printf("%d\n", gamma);
    printf("%d\n", epsilon);
    printf("%d\n", power_consumption);

    return 0;
}
