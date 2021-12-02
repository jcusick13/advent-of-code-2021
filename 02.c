#include <stdio.h>
#include "inputs/02.h"

int main() {
    int aim = 0;
    int horizontal = 0;
    int depth = 0;
    const unsigned char *s = input;

    while (*s != '\0') {

        if (*s == 'f') {
            // Skip over rest of letters, including final space
            while (*s != ' ') s++;
            s++;

            horizontal += (*s - '0');
            if (aim) {
                depth += (aim * (*s - '0'));
            }
        }
        if (*s == 'd') {
            while (*s != ' ') s++;
            s++;

            aim += (*s - '0');
        }
        if (*s == 'u') {
            while (*s != ' ') s++;
            s++;

            aim -= (*s - '0');
        }
        s++;
    }

    int answer = horizontal * depth;
    printf("%d\n", answer);

    return 0;
}
