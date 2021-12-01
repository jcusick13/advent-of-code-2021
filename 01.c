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
    for (i = 0; i < n; i++) {
        if (i == 0) {
            continue;
        }

        if (numbers[i] > numbers[i - 1]) {
            total++;
        }
    }

    printf("%d\n", total);

    return 0;
}
