#include <math.h>
#include <stdio.h>
#include <string.h>
#include "inputs/03.h"

#define N_BITS 12
#define N_ROWS 1000

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

struct Counter * countBitFreqs(int report[], int arr_len){
    /* Create array of length `N_BITS` with a `Counter`
     * struct in each cell
     */

    // Establish array of `Counter`s with zeroed starting values
    static struct Counter bit_counts[N_BITS];
    for (int i = 0; i < N_BITS; i++) {
        initEmptyCounter(&bit_counts[i]);
    }

    for (int j = 0; j < arr_len; j++) {
        if (report[j] == 0) {
            bit_counts[j % N_BITS].zero += 1;
        }
        else if (report[j] == 1) {
            bit_counts[j % N_BITS].one += 1;
        }
        else continue;
    }

    return bit_counts;
}

int powerConsumption(int report[N_ROWS * N_BITS]) {
    struct Counter *bit_counts;
    bit_counts = countBitFreqs(report, N_ROWS * N_BITS);

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


int lifeSupportRating(int report[N_ROWS * N_BITS], int rating_type) {
    /* Set `rating_type` to 0 for oxygen generator, 1 for CO2 scrubber*/
    int starting_n = N_ROWS * N_BITS;
    int *rating_n = &starting_n;
    int _rating_n = 0;

    int *rating[*rating_n];
    int _rating[*rating_n];
    int rating_bit;

    // Copy inital inputs into rating-specifc arrays
    for (int i = 0; i < (*rating_n); i++) {
        rating[i] = &report[i];
    }

    for (int bit = 0; bit < N_BITS; bit++) {

        // Determine most common bits in each slot
        struct Counter *rating_bit_counts;
        rating_bit_counts = countBitFreqs(*rating, *rating_n);

        if (rating_type == 0){
            // Oxygen generator
            if (rating_bit_counts[bit].zero > rating_bit_counts[bit].one) {
                rating_bit = 0;
            }
            else {
                rating_bit = 1;
            }
        }
        else {
            // CO2 scrubber
            if (rating_bit_counts[bit].zero > rating_bit_counts[bit].one) {
                rating_bit = 1;
            }
            else {
                rating_bit = 0;
            }

        }

        _rating_n = 0;
        for (int cell = 0; cell < (*rating_n); cell++) {
            if ((int)(cell % N_BITS) != bit) continue;
            if (*rating[cell] != rating_bit) continue;

            // Match found, copy entire entry to new candidate set
            for (int j = (bit * -1); j < (N_BITS - bit); j++) {
                _rating[_rating_n] = *rating[cell + j];
                _rating_n++;
            }
        }

        *rating_n = _rating_n;
        for (int k = 0; k < (*rating_n); k++) {
            rating[k] = &_rating[k];
        }
    }

    int output_rating = binaryToDecimal(*rating, N_BITS);

    return output_rating;
}

/*
int lifeSupportRatingCo2(int report[N_ROWS * N_BITS]) {
    int starting_n = N_ROWS * N_BITS;
    int *co2_n = &starting_n;
    int _co2_n = 0;

    int *co2[*co2_n];
    int _co2[*co2_n];
    int co2_bit;

    // Copy inital inputs into rating-specifc arrays
    for (int i = 0; i < (*co2_n); i++) {
        co2[i] = &report[i];
    }

    for (int bit = 0; bit < N_BITS; bit++) {

        // Determine most common bits for each set rating values
        struct Counter *co2_bit_counts;
        co2_bit_counts = countBitFreqs(*co2, *co2_n);

        if (co2_bit_counts[bit].zero > co2_bit_counts[bit].one) {
            co2_bit = 1;
        }
        else {
            co2_bit = 0;
        }

        _co2_n = 0;
        for (int cell = 0; cell < (*co2_n); cell++) {
            if ((int)(cell % N_BITS) != bit) continue;
            if (*co2[cell] != co2_bit) continue;

            // Match found, copy entire entry to new candidate set
            for (int j = (bit * -1); j < (N_BITS - bit); j++) {
                _co2[_co2_n] = *co2[cell + j];
                _co2_n++;
            }
        }

        *co2_n = _co2_n;
        for (int k = 0; k < (*co2_n); k++) {
            co2[k] = &_co2[k];
        }
    }

    int co2_rating = binaryToDecimal(*co2, N_BITS);
    printf("CO2 rating: %d\n", co2_rating);

    return co2_rating;
}
*/


int main() {
    const unsigned char *s = input;
    const int n_cells = N_ROWS * N_BITS;
    int report[n_cells];
    int cell = 0;

    while (*s != '\0') {
        if (*s == '\n') s++;
        report[cell] = (*s - '0');
        cell++;
        s++;
    }

    int power_consumption = powerConsumption(report);
    printf("Power consumption: %d\n", power_consumption);

    int rating_value;
    rating_value = 0;
    int oxygen_generator_rating = lifeSupportRating(report, rating_value);

    rating_value = 1;
    int co2_scrubber_rating = lifeSupportRating(report, rating_value);

    int life_support_rating = oxygen_generator_rating * co2_scrubber_rating;
    printf("Life support rating: %d\n", life_support_rating);
    return 0;
}
