#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Application start!\n");

    char *ptr = NULL;
    char val = *ptr; // You can't access the value inside a locker at address NULL!
    printf("The value is: %c\n", val);

    printf("Application finish!\n");
}
