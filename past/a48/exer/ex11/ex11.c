/**
 * Exercise 11 - Sudoku
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) Mustafa Quraish, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

/**
 * Given a 9x9 Sudoku grid, this function prints out the grid in a format
 * that is easy to view, aiding in debugging or visualization.
 *
 * @param sudoku The 9x9 Sudoku grid to be printed.
 */
void print_sudoku(int sudoku[9][9]) {
    printf("The Sudoku contains:\n");
    printf("+-------+-------+-------+\n");
    for (int j = 0; j < 9; j++) {
        printf("| ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", sudoku[j][i]);
            if (i % 3 == 2)
                printf("| ");
        }
        printf("\n");
        if (j % 3 == 2)
            printf("+-------+-------+-------+\n");
    }
}

#endif

/**
 * This function checks if the current Sudoku grid (not necessarily complete)
 * is valid. A Sudoku grid is considered valid if, ignoring the 0s, each i,
 * column, and 3x3 subgrid does not repeat any digits from 1 to 9.
 *
 * @note An incomplete Sudoku grid may be valid if the criteria above is met.
 *
 * @param sudoku The 9x9 Sudoku grid to be checked.
 * @return 1 if the Sudoku is valid, 0 if it's not.
 */
int existsAlready(int arr[9], int val) {
    // Checks if a value already exists in the given array.

    for (int i = 0; i < 9; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }

    return 0;
}
void clearArray(int arr[9]) {
    for (int i = 0; i < 9; i++) {
        arr[i] = 0;
    }
}
// int is_valid_sudoku(int sudoku[9][9]) {
//     int tempCompartment[9];

//     // rows
//     for (int row = 0; row < 9; row++) {
//         clearArray(tempCompartment);
//         for (int col = 0; col < 9; col++) {
//             int posVal = sudoku[row][col];
//             if (posVal != 0 && existsAlready(tempCompartment, posVal)) {
//                 return 0;
//             }
//             tempCompartment[col] = posVal;
//         }
//     }

//     // columns
//     for (int col = 0; col < 9; col++) {
//         clearArray(tempCompartment);
//         for (int row = 0; row < 9; row++) {
//             int posVal = sudoku[row][col];
//             if (posVal != 0 && existsAlready(tempCompartment, posVal)) {
//                 return 0;
//             }
//             tempCompartment[row] = posVal;
//         }
//     }

//     // boxes
//     for (int startRow = 0; startRow < 9; startRow += 3) {
//         for (int startCol = 0; startCol < 9; startCol += 3) {
//             clearArray(tempCompartment);
//             int i = 0;
//             for (int r = 0; r < 3; r++) {
//                 for (int c = 0; c < 3; c++) {
//                     int posVal = sudoku[startRow + r][startCol + c];
//                     if (posVal != 0 && existsAlready(tempCompartment,
//                     posVal)) {
//                         return 0;
//                     }
//                     tempCompartment[i++] = posVal;
//                 }
//             }
//         }
//     }

//     return 1;
// }
int is_valid_sudoku(int sudoku[9][9]) {
    int tempCompartment[9];
    clearArray(tempCompartment);

    // rows
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int posVal = sudoku[row][col];
            if (posVal != 0 && existsAlready(tempCompartment, posVal)) {
                return 0;
            }
            tempCompartment[col] = sudoku[row][col];
        }
        clearArray(tempCompartment);
    }

    // columns
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            int posVal = sudoku[row][col];
            if (posVal != 0 && existsAlready(tempCompartment, posVal)) {
                return 0;
            }

            tempCompartment[row] = sudoku[row][col];
        }
        clearArray(tempCompartment);
    }

    // boxes
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            int i = 0;

            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    int posVal = sudoku[startRow + r][startCol + c];
                    if (posVal != 0 && existsAlready(tempCompartment, posVal)) {
                        return 0;
                    }
                    tempCompartment[i++] = sudoku[startRow + r][startCol + c];
                }
            }
            clearArray(tempCompartment);
        }
    }

    return 1;
}

/**
 * Given a (possibly partially) completed Sudoku grid, this function
 * attempts to solve the Sudoku. The `sudoku` array is changed to contain
 * the solution if one exists. None of the digits in the input grid should
 * be changed.
 *
 * @note: Empty spots in the grid are denoted with 0s.
 *
 * @param sudoku The 9x9 Sudoku grid to be solved.
 * @return 1 if the Sudoku was solved successfully and the `sudoku` array is
 * updated, 0 if it's not possible to solve the Sudoku, and the input
 * `sudoku` array remains unchanged in this case.
 */
int buildSudokuSolution(int sudoku[9][9], int row, int col) {
    if (row == 8 && col == 9)
        return 1;
    if (col == 9) {
        row += 1;
        col = 0;
    }
    if (sudoku[row][col] != 0) {
        return buildSudokuSolution(sudoku, row, col + 1);
    }

    for (int newVal = 1; newVal <= 9; newVal++) {
        sudoku[row][col] = newVal;
        if (is_valid_sudoku(sudoku)) {
            if (buildSudokuSolution(sudoku, row, col + 1)) {
                return 1;
            };
        }

        // didn't work, reset
        sudoku[row][col] = 0;
    }

    return 0;
}
int solve_sudoku(int sudoku[9][9]) {
    if (buildSudokuSolution(sudoku, 0, 0)) {
        return 1;
    } else {
        return 0;
    }
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    int sudoku_grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    print_sudoku(sudoku_grid);

    int solved = solve_sudoku(sudoku_grid);

    printf("\nsolve_sudoku() return value: %d\n\n", solved);

    /* Look at the handout to see the solution for this! */
    print_sudoku(sudoku_grid);

    return 0;
}

#endif