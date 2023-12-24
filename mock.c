#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALTERNATING_CAPS_PERCENT 90
#define PROGRAM_NAME "mock"

int randint(int min, int max) {
    int x;
    do {
        x = rand();
    } while (x >= (RAND_MAX - RAND_MAX % min));
    return x % (max - min + 1) + min;
}

int main(int argc, char *argv[]) {
    srand((unsigned int) time(NULL));
    FILE *fp;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "%s: %s: No such file or directory\n", PROGRAM_NAME, argv[1]);
            return 1;
        }
    } else {
        fp = stdin;
    }

    setvbuf(stdout, NULL, _IOFBF, 0);

    bool lowercase = true;
    char c;
    while ((c = (char) getc(fp)) != EOF) {
        if (isalpha(c)) {
            unsigned char cc = (unsigned char) c;
            putchar(lowercase ? tolower(cc) : toupper(cc));
            if (randint(1, 100) <= ALTERNATING_CAPS_PERCENT) {
                lowercase = !lowercase;
            }
        } else {
            if (c == '\n' && !lowercase) {
                lowercase = true;
            }
            putchar(c);
        }
    }

    if (argc > 1) {
        fclose(fp);
    }
    return 0;
}
