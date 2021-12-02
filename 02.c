#include <stdio.h>
#include "inputs/02.h"

int main() {
    int horizontal = 0;
    int vertical = 0;
    const unsigned char *s = input;

    while (*s != '\0') {

        if (*s == 'f') {
            // Skip over rest of letters, including final space
            while (*s != ' ') s++;
            s++;

            horizontal += (*s - '0');
        }
        if (*s == 'd') {
            while (*s != ' ') s++;
            s++;

            vertical += (*s - '0');
        }
        if (*s == 'u') {
            while (*s != ' ') s++;
            s++;

            vertical -= (*s - '0');
        }
        s++;
    }

    int answer = horizontal * vertical;
    printf("%d\n", answer);

    return 0;
}
