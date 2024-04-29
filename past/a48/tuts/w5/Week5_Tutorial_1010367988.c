#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef ERROR
#define ERROR 0.000001
#endif

void marcelonacci(double arr[], int len, double alpha) {
    // TODO: Implement this function.

    for (int i = 3; i < len; i++) {
        arr[i] = arr[i - 1] + alpha * (arr[i - 2] + arr[i - 3]);
    }
}

bool is_close_enough(double a, double b) {
    double c = a - b;
    return c <= ERROR && c >= -ERROR;
}

int last_close_index_of(double arr_to_search[], int search_len,
                        double arr_to_find[], int find_len) {
    int last = -1;
    for (int i = 0; i <= search_len - find_len; i++) {
        int same = 0;
        for (int j = 0; j < find_len; j++) {
            if (!is_close_enough(arr_to_search[i + j], arr_to_find[j]))
                break;
            same += 1;
        }

        if (same == find_len)
            last = i;
    }

    return last;
}

#ifndef __testing__

#define MARCELO_ARR1_LEN 6

int main() {
    double marcelo_arr1[MARCELO_ARR1_LEN];
    marcelo_arr1[0] = 0.3;
    marcelo_arr1[1] = 0.5;
    marcelo_arr1[2] = 0.4;
    marcelonacci(marcelo_arr1, MARCELO_ARR1_LEN, 0.314);

    double expected_marcelo_arr1[MARCELO_ARR1_LEN] = {
        0.3, 0.5, 0.4, 0.6512, 0.9338, 1.2638768};
    for (int i = 0; i < MARCELO_ARR1_LEN; i++) {
        if (!is_close_enough(marcelo_arr1[i], expected_marcelo_arr1[i])) {
            printf("Expected %f at marcelo_arr1[%d], but got %f\n",
                   expected_marcelo_arr1[i], i, marcelo_arr1[i]);
            exit(1);
        }
    }
    printf("marcelonacci() test case #1 passed.\n");

    double marcelo_arr2[MARCELO_ARR1_LEN] = {-1, -2, -3, 0, 0, 0};
    marcelonacci(marcelo_arr2, MARCELO_ARR1_LEN, 1.5);

    double expected_marcelo_arr2[MARCELO_ARR1_LEN] = {-1,   -2,    -3,
                                                      -7.5, -15.0, -30.75};
    for (int i = 0; i < MARCELO_ARR1_LEN; i++) {
        if (!is_close_enough(marcelo_arr2[i], expected_marcelo_arr2[i])) {
            printf("Expected %.4f at marcelo_arr2[%d], but got %.4f\n",
                   expected_marcelo_arr2[i], i, marcelo_arr2[i]);
            return 1;
        }
    };
    printf("marcelonacci() test case #2 passed.\n");

    double marcelo_arr3[MARCELO_ARR1_LEN] = {3, 5, 7, 0, 0, 0};
    marcelonacci(marcelo_arr3, MARCELO_ARR1_LEN, 2);

    double expected_marcelo_arr3[MARCELO_ARR1_LEN] = {3, 5, 7, 23, 47, 107};
    for (int i = 0; i < MARCELO_ARR1_LEN; i++) {
        if (!is_close_enough(marcelo_arr3[i], expected_marcelo_arr3[i])) {
            printf("Expected %.4f at marcelo_arr3[%d], but got %.4f\n",
                   expected_marcelo_arr3[i], i, marcelo_arr3[i]);
            return 1;
        }
    }
    printf("marcelonacci() test case #3 passed.\n");
    printf("All marcelonacci() test cases passed.\n\n");

    double arr_to_search1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double arr_to_find1[3] = {6, 7.000000001, 8};
    int idx1 = last_close_index_of(arr_to_search1, 10, arr_to_find1, 3);
    int expected_idx1 = 5;
    if (idx1 != expected_idx1) {
        printf("Expected to find array at %d, got %d\n", expected_idx1, idx1);
        exit(1);
    }
    printf("last_close_index_of() test case #1 passed.\n");

    double arr_to_search2[10] = {1, 2, 3, 1, 2, 3};
    double arr_to_find2[3] = {1, 2, 3};
    int idx2 = last_close_index_of(arr_to_search2, 10, arr_to_find2, 3);
    int expected_idx2 = 3;
    if (idx2 != expected_idx2) {
        printf("Expected to find array at %d, got %d\n", expected_idx2, idx2);
        exit(1);
    }
    printf("last_close_index_of() test case #2 passed.\n");

    double arr_to_search3[3] = {1, 2, 3};
    double arr_to_find3[0] = {};
    int idx3 = last_close_index_of(arr_to_search3, 3, arr_to_find3, 0);
    int expected_idx3 = 3;
    if (idx3 != expected_idx3) {
        printf("Expected to find array at %d, got %d\n", expected_idx3, idx3);
        exit(1);
    }
    printf("last_close_index_of() test case #3 passed.\n");

    double arr_to_search4[0] = {};
    double arr_to_find4[0] = {};
    int idx4 = last_close_index_of(arr_to_search4, 0, arr_to_find4, 0);
    int expected_idx4 = 0;
    if (idx4 != expected_idx4) {
        printf("Expected to find array at %d, got %d\n", expected_idx4, idx4);
        exit(1);
    }
    printf("last_close_index_of() test case #4 passed.\n");

    double arr_to_search5[8] = {1.0001, 2.0002, 3.0003, 4.0004,
                                5.0005, 6.0006, 7.0007, 8.0008};
    double arr_to_find5[4] = {4.0004, 5.0005, 6.0006, 7.0007};
    int idx5 = last_close_index_of(arr_to_search5, 8, arr_to_find5, 4);
    int expected_idx5 = 3;
    if (idx5 != expected_idx5) {
        printf("Expected to find array at %d, got %d\n", expected_idx5, idx5);
        exit(1);
    }
    printf("last_close_index_of() test case #5 passed.\n");

    double arr_to_search6[7] = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
    double arr_to_find6[4] = {2.49, 3.49, 4.49, 5.49};
    int idx6 = last_close_index_of(arr_to_search6, 7, arr_to_find6, 4);
    int expected_idx6 = -1;
    if (idx6 != expected_idx6) {
        printf("Expected to find array at %d, got %d\n", expected_idx6, idx6);
        exit(1);
    }
    printf("last_close_index_of() test case #6 passed.\n");
    printf("All last_close_index_of() test cases passed.\n");

    return 0;
}

#endif
