/**
 * Exercise 2 - Functions
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function: is_leap_year
 * ----------------------
 * A year is considered a leap year if it is exactly divisible by 4 but not 100.
 *
 * For example, 2024 is a leap year, but 2000 is not.
 *
 * NOTE: This is not the real defination of a leap year.
 * However, this is the defination we will be using.
 *
 * year: the year
 * returns: a boolean of whether or not 'year' is a leap year
 */
bool is_leap_year(int year)
{
    // TODO: Complete this function.
    return year % 4 == 0 && year % 100 != 0;
}

/**
 * Function: count_leap_years
 * --------------------------
 * Count the number of leap years between a given start and end year
 * (inclusive).
 *
 * start_year: the year to start counting
 * end_year: the year to end counting
 * returns: the number of leap years in the given inclusive interval
 */
int count_leap_years(int start_year, int end_year)
{
    // TODO: Complete this function.
    int count = 0;

    for (int year = start_year; year < end_year + 1; year++)
    {
        if (is_leap_year(year))
        {
            count++;
        }
    }

    return count;
}

/**
 * Function: number_of_days_in_month
 * ---------------------------------
 * Computes the number of days in a given month of a year.
 *
 * For example:
 *  - 1 (January) 2024 has 31 days.
 *  - 2 (February) 2023 has 28 days.
 *
 * If the given month is invalid, return -1 instead.
 *
 * month: the month of the year, starting with Janurary as 01
 * year: the year
 * returns: the number of days in the given (month, year)
 */
int number_of_days_in_month(int month, int year)
{
    // TODO: Complete this function.

    const int leap_year = is_leap_year(year);

    if (month == 2)
    {
        return leap_year ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main()
{
    if (is_leap_year(2024) != true)
    {
        printf("2024 is a leap year.\n");
        exit(1);
    }

    if (is_leap_year(2000) != false)
    {
        printf("2000 is not a leap year.\n");
        exit(1);
    }

    if (count_leap_years(2005, 2023) != 4)
    {
        printf("There are 4 leap years between 2005 and 2023.\n");
        exit(1);
    }

    if (number_of_days_in_month(1, 2024) != 31)
    {
        printf("January 2024 has 31 days.\n");
        exit(1);
    }

    if (number_of_days_in_month(2, 2023) != 28)
    {
        printf("February 2023 has 28 days.\n");
        exit(1);
    }

    // more tests for number_of_days_in_month
    if (
        number_of_days_in_month(2, 2024) != 29 ||
        number_of_days_in_month(2, 1996) != 29 ||
        number_of_days_in_month(4, 2021) != 30 ||
        number_of_days_in_month(6, 2021) != 30 ||
        number_of_days_in_month(9, 2021) != 30 ||
        number_of_days_in_month(11, 2021) != 30 ||
        number_of_days_in_month(1, 2021) != 31 ||
        number_of_days_in_month(3, 2021) != 31 ||
        number_of_days_in_month(5, 2021) != 31 ||
        number_of_days_in_month(7, 2021) != 31 ||
        number_of_days_in_month(8, 2021) != 31 ||
        number_of_days_in_month(10, 2021) != 31)
    {
        printf("FAIL\n");
        exit(1);
    }

    printf("Your solution passed all provided test cases.\n");
    return 0;
}

#endif
