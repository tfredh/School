#include <stdio.h>
#include <math.h>

// prime number checker function
int is_prime(int num)
{
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    // check primes
    printf("2 is prime: %d\n", is_prime(2));
    printf("3 is prime: %d\n", is_prime(3));
    printf("4 is prime: %d\n", is_prime(4));
    printf("5 is prime: %d\n", is_prime(5));
}