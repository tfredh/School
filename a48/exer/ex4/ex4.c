/**
 * Exercise 4 - Strings & POinters
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// #############################################################################
// # READ THIS! READ THIS! READ THIS!
// #############################################################################
// No additional imports are allowed. You can make helper functions if you wish.
// Importing other header files will result in an automatic fail.
// Using any array notations "[]" outside of main() will result in an automatic
// fail.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: reverse
 * -----------------
 * Reverse a given string in-place. This means that the reversed string should
 * replace the original.
 *
 * string: the string to reverse
 */

int myStrlen(char *string) {
    int len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}

void reverse(char *string) {
    int len = myStrlen(string);

    // printf("len %d /2 %d\n", len, len / 2);
    for (int i = 0; i < len / 2; i++) {
        char temp = string[i];
        string[i] = string[len - 1 - i];
        string[len - i - 1] = temp;
    }
}

/**
 * Function: replace_all
 * -----------------
 * Given a source string, replace all occurrences of a specified substring with
 * another string and write the resulting string to the destination.
 *
 * source: the input string to be replaced
 * dest: the location to write the replaced string to
 * find: the substring to be replaced
 * replace: the string to replace occurrences of "find" with
 */
void replace_all(char *source, char *dest, char *find, char *replace) {
    // clear dest: has garbage stored at the start, and garbage gets
    // accumulated in empty memory for each change in another the 'dest'
    // unless there's already something in that place
    // use \0 as a string-neutral character
    for (int i = 0; i < 1024; i++) {
        dest[i] = '\0';
    }

    int sourceLen = myStrlen(source);
    int findLen = myStrlen(find);
    int replaceLen = myStrlen(replace);

    for (int i = 0; i < sourceLen; i++) {
        int found = 1;
        for (int j = 0; j < findLen; j++) {
            if (source[i + j] != find[j]) {
                found = 0;
                break;
            }
        }
        // printf("found %d\n", found);

        if (found) {
            for (int k = 0; k < replaceLen; k++) {
                // printf("len dest %d, dest %s\n", myStrlen(dest), dest);

                dest[myStrlen(dest)] = replace[k];
            }

            i += findLen - 1;
        } else {
            dest[myStrlen(dest)] = source[i];
        }
    }

    // printf("%s\n", source);
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

void test_reverse() {
    char string[1024] =
        "!dekrow evah yam noitcnuf ruoy ekil skooL ?ylraelc siht daer uoy naC";
    printf("String: %s\n", string);

    reverse(string);

    // "Can you read this clearly? Looks like your function may have worked!"
    printf("Reversed String: %s\n", string);
}

void test_replace_all() {
    char source[1024] = "the quick brown fox jumps over the lazy dog";
    printf("Source: %s\n", source);

    char dest[1024];
    replace_all(source, dest, "the", "a");

    // "a quick brown fox jumps over a lazy dog"
    printf("Dest: %s\n", dest);
}

int main() {
    // Testing reverse() function.
    printf("Calling test_reverse() ...\n");
    test_reverse();

    // Testing test_replace_all() function.
    printf("Calling test_replace_all() ...\n");
    test_replace_all();
    return 0;
}

#endif
