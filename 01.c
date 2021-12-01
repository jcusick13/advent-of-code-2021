#include <stdio.h>
#include "inputs/01.h"

int main() {
    int numbers[10000] = {0};
    int n = 0;
    const unsigned char *s = input;

    while (*s != '\0') {
        while (*s >= '0' && *s <= '9') {
            numbers[n] = (numbers[n] * 10) + (*s - '0');
            s++;
        }

        if (*s == '\n') {
            s++;
        }
        n++;
    }

    int i;
    int total = 0;
    int window_a;
    int window_b;
    for (i = 0; i < n; i++) {
        if (i < 3) {
            continue;
        }
        
        window_a = numbers[i - 3] + numbers[i - 2] + numbers[i - 1];
        window_b = numbers[i - 2] + numbers[i - 1] + numbers[i];


        if (window_b > window_a) {
            total++;
        }
    }

    printf("%d\n", total);

    return 0;
}
