/*
    Tutorial Week 2
*/

/*	1) Getting Started

    To write:
    - use whatever text editor (Notepad++ preferred)

    To compile:
    - in your terminal, go to the correct folder (cd)
    - do gcc filename.c

    To run:
    - ./a.out or ./a.exe

    2) Content Overview Questions

    2.a) Variables

        type0 var_name;

    e.g.
*/

// ***********************************************

#include <stdio.h>
#include <math.h>

// int main()
// {
//     // main body

//     float area = area_of_circle(2.0);
//     printf("area = %f\n", area);

//     return 0;
// }

// ***********************************************

/*	2.b) Functions

        type0 func_name(type1 param1, type2 param2)
        {
            type0 val;

            // code body

            return val;
        }

    e.g.
*/

// ***********************************************

// code here
float area_of_circle(float radius)
{
    float pi = 3.0;
    float area = pi * pow(radius, 2);
    return area;
}

// ***********************************************

/*	2.c) Loops
    - for loops
    - while loops

    e.g.
*/

// ***********************************************

// code here
// int main()
// {
//     for (float i = 2.3; i < 42; i += 3)
//     {
//         printf("r = %.2f\narea = %.2f\n\n", i, area_of_circle(i));
//     }
// }

// ***********************************************

/*	2.d) Conditionals

*/

// ***********************************************

// code here

// ***********************************************

/*	3) TUTORIAL WORK (TO HAND IN)

    Note: It is NOT marked for correctness.
          It DOES need to compile and run.

*/

// ***********************************************

// code here

int main()
{
    float pi = 3.14;

    // for (int x = 0; x <= 2 * pi; x++)
    // {
    //     printf("x = %.3f\tsin(x) = %.3f\n", x, sin(x));
    // }

    // 0.5 <= sin(x) <= 0.75 or -0.75 <= sin(x) <= -0.5
    for (float x = 0; x <= 2 * pi; x += 0.3)
    {
        // print only vals between .5 and .75 positive and negative
        if ((sin(x) >= 0.5 && sin(x) <= 0.75) ||
            (sin(x) >= -0.75 && sin(x) <= -0.5))
        {
            printf("x = %.3f\tsin(x) = %.3f\n", x, sin(x));
        }
    }

    // terminate when all positives printed
    // for (float x = 0; x <= 2 * pi; x += 0.3)
    // {
    //     const float sinResult = sin(x);
    //     if (sinResult < 0)
    //     {
    //         break;
    //     }

    //     printf("x = %.3f\tsin(x) = %.3f\n", x, sinResult);
    // }
}

// ***********************************************
/*
x = 0.000	sin(x) = 0.000
x = 0.841	sin(x) = 0.000
x = 0.909	sin(x) = -0.000
x = 0.141	sin(x) = 0.140
x = -0.757	sin(x) = -0.001
x = -0.959	sin(x) = 0.000
x = -0.279	sin(x) = 0.278
*/