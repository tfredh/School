#include <stdio.h>
#include <string.h>

// Declares a string in main(), you can fill that string with any test you wish, for example:
// “Now I know how to program in C!”
// - Write a function that takes as input the character array for the string, and reverses the
//  string. Mind the fact that the length of the string may be different than the size of the
//  array, and that the reversing process should not mess with the end-of-string delimiter.
// - Have your code print the reversed string
void reverse_str(char *str)
{
    int len = strlen(str);

    printf("len %d /2 %d\n", len, len / 2);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    printf("%s\n", str);
}

// Write a function that takes as input the character array for the string, a query character,
//  and a target character, then goes over the string using pointers and offsets to replace
//  any occurrence of the query character with the target character
void search_and_replace(char *str, char query, char target)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == target)
        {
            *(str + i) = query;
        }
    }

    printf("%s\n", str);
}

int main()
{
    char str[] = "Now I know how to program in C!";
    search_and_replace(str, 'a', 'o');
    // reverse_str(str);
}
