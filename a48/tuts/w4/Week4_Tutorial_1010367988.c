#include <stdio.h>
#include <string.h>

float arr_min(float *arr, int len) {
    if (len == 0) {
        return -1.0;
    }

    float min = arr[0];
    for (int i = 0; i < len; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    return min;
}

float arr_max(float *arr, int len) {
    if (len == 0) {
        return -1.0;
    }

    float max = arr[0];
    for (int i = 0; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

float arr_avg(float *arr, int len) {
    if (len == 0) {
        return 0.0;
    }

    float sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }

    return sum / len;
}

int main() {
    // declare and initialize an array of 10 values
    float arr[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    float min = arr_min(arr, 10);
    float max = arr_max(arr, 10);
    float avg = arr_avg(arr, 10);

    printf("min: %f\n", min);
    printf("max: %f\n", max);
    printf("avg: %f\n", avg);

    return 0;
}