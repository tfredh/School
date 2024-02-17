#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STANZAS 2000

const char *poem = "Quantum computers may at first sight seem\n"
                   "To be impossible. How dare we dream\n"
                   "Of solving problems that else would take more time\n"
                   "Than has passed since the primeval Big Bang!\n"
                   "\n"
                   "But is there any reason to believe\n"
                   "The universe computes the way we do?\n"
                   "Nature is profligate with galaxies.\n"
                   "Why shouldn't her extravagance hold true\n"
                   "For other things? Why mightn't she achieve\n"
                   "Prodigious feats of computation, too.\n";

char *new_stanza(const char *s) {
    char *newStanza = (char *)malloc(strlen(s) + 1);
    strncpy(newStanza, s, strlen(s));
    newStanza[strlen(s)] = '\0';

    return newStanza;
}

int read_stanzas(const char *poem, char *stanzas[]) {
    int start = 0;
    int stanzaCount = 0;

    for (int i = 0; i < strlen(poem); i++) {
        if (poem[i] == '\n') {
            char *line = (char *)malloc(i - start + 1);

            for (int j = start; j < i; j++) {
                line[j - start] = poem[j];
            }
            line[i - start] = '\0';

            stanzas[stanzaCount] = new_stanza(line);
            stanzaCount++;
            start = i + 1;
        }
    }

    // printf("stanzaCount: %d\n", stanzaCount);
    return stanzaCount;
}

void print_stanzas(char *stanzas[], const int N) {
    for (int i = 0; i < N; i++) {
        printf("%s\n", stanzas[i]);
    }
}

void print_stanzas_reverse(char *stanzas[], const int N) {
    for (int i = N - 1; i >= 0; i--) {
        printf("%s\n", stanzas[i]);
    }
}

int main() {
    /* Declare an array of pointers to strings. */
    char *stanzas[50];

    /* Get the list of pointers.  */
    int stanzasCount = read_stanzas(poem, stanzas);

    /* Print the stanzas in forward order. */
    print_stanzas(stanzas, stanzasCount);
    printf("---\n\n");

    /* Print the stanzas in reverse order. */
    print_stanzas_reverse(stanzas, stanzasCount);
    printf("---\n\n");
}