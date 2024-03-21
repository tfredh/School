/**
 * Exercise 10 - Floo-Fill
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
 *                (Updated by) Mustafa Quraish, 2020
 *             (Originally by) Francisco Estrada, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the image size we are using. This will remain constant.
#define SIZEX 50
#define SIZEY 50

// Include the functions to read / write the images
#include "imgUtils.c"

/**
 * Given the input image array representing the elevation maps of a newly
 * discovered planet and the initial position of the rover, this function finds
 * and marks the connected region around the initial position. Each element of
 * the input array has values 0-255 inclusive, where 0 represents black and 255
 * represents white.
 *
 * @note Because of how 2D arrays are stored in memory, we need to be careful
 * when trying to access the correct pixel. PGM images use the math convention
 * where the first index is the ROW, and the second index is the COLUMN. So, to
 * get the color of pixel (x, y), you will need to do: input[y][x]
 *
 * @param input The input image array representing the elevation maps.
 * @param px The initial position of the rover (x-coordinate).
 * @param py The initial position of the rover (y-coordinate).
 * @param output The output image array to store the marked connected region.
 * Output is initially empty (all pixels have colour 0).
 */
typedef struct ListNode {
    int coordinates[2];
    struct ListNode *next;
} ListNode;
ListNode *newVisitedNode(int px, int py) {
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->coordinates[0] = px;
    newNode->coordinates[1] = py;
    newNode->next = NULL;

    return newNode;
}
int hasBeenVisited(ListNode *visited, int px, int py) {
    /**
     * Returns boolean.
     */

    if (visited == NULL)
        return 0;

    ListNode *curr = visited;
    while (curr != NULL) {
        if (curr->coordinates[0] == px && curr->coordinates[1] == py)
            return 1;

        curr = curr->next;
    }

    return 0;
}
ListNode *addToVisited(ListNode *visited, int px, int py) {
    ListNode *newNode = newVisitedNode(px, py);

    // add to head
    newNode->next = visited;
    return newNode;

    // if (visited == NULL) {
    //     return newNode;
    // } else if (hasBeenVisited(visited, px, py)) {
    //     return visited;
    // }
    // newNode->next = visited;
    // return newNode;

    // ListNode *curr = visited;
    // while (curr->next) { // curr is not NULL at this point
    //     if (curr->coordinates[0] == px && curr->coordinates[1] == py)
    //         // already visited the node, no need to add again
    //         return;
    //     if (curr->next == NULL)
    //         // all nodes checked at this point, none are equal to new visited
    //         break;
    //     curr = curr->next;
    // }
    // // add to visited
    // curr->next = newNode;
}
void dfsFill(unsigned char inputGrid[SIZEY][SIZEX], int px, int py,
             unsigned char outputGrid[SIZEY][SIZEX], ListNode *visited,
             unsigned char elevation) {
    if (hasBeenVisited(visited, px, py) || (px < 0 || px >= SIZEX) ||
        (py < 0 || py >= SIZEY) || (inputGrid[py][px] != elevation)) {
        return;
    }
    printf("bruh (%d, %d)\n", px, py);

    // otherwise, fill in this in the output
    outputGrid[py][px] = elevation;
    visited = addToVisited(visited, px, py);

    // continue searching in each direction
    dfsFill(inputGrid, px - 1, py, outputGrid, visited, elevation);
    dfsFill(inputGrid, px + 1, py, outputGrid, visited, elevation);
    dfsFill(inputGrid, px, py - 1, outputGrid, visited, elevation);
    dfsFill(inputGrid, px, py + 1, outputGrid, visited, elevation);
}
void find_connected_region(unsigned char input[SIZEY][SIZEX], int px, int py,
                           unsigned char output[SIZEY][SIZEX]) {
    /**
     * Your task is to find all *connected* pixels that have the same
     elevation
     * as the one at (px,py) in `input`, and mark these pixels on `output`.
     *
     * For instance, if the initial coordinates are (px=5, py=10), your
     program
     * must check the elevation at input[10][5], then set the colour of all
     * connected pixels to white (255) in the levelset_map.
     *
     * Example with a very tiny sample image:
     *
     * input:
     *                       1    1    1    2    3    3
     *                       1    1    2    3    3    4
     *                       1    2    2    2    4    3
     *                       1    1    1    2    4    3
     *                       1    1    2    2    3    3
     *                       4    4    4    4    2    2
     *
     *
     * If we call the function with the `input` above, and initial
     coordinates
     * (1,1), it should produce
     *
     * output:
     *
     *                      255  255  255   0    0    0
     *                      255  255   0    0    0    0
     *                      255   0    0    0    0    0
     *                      255  255  255   0    0    0
     *                      255  255   0    0    0    0
     *                       0    0    0    0    0    0
     *
     * If we call the function with initial coordinates (4, 0) it will
     produce
     *
     * output:
     *
     *                       0    0    0    0   255  255
     *                       0    0    0   255  255   0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *
     * In effect, this function extracts the connected region in the image
     * array with the same elevation as that of the pixel at (px, py).
     *
     * NOTE: A pixel can be 'connected' to it's it's 4 neighbours above,
     below,
     *       to the left and right of it, if they have the same colour. In
     *       particular, we will NOT count pixels along the diagonal.
     Carefully
     *       look at the examples above to make sure you understand this.
     *
     * - You should NOT change the contents of the input array.
     *
     * There are many ways to approach this problem, you're free to choose
     * whatever makes more sense to you. Make reasonable assumptions where
     * needed, and solve the problem!
     */

    ListNode *visited = NULL;
    dfsFill(input, px, py, output, visited, input[py][px]);

    // free the visited list
    ListNode *curr = visited;
    while (curr != NULL) {
        ListNode *temp = curr;
        curr = curr->next;
        free(temp);
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
    unsigned char input[SIZEY][SIZEX];
    unsigned char output[SIZEY][SIZEX];

    // Initialize output array to have colour black (0)
    for (int y = 0; y < SIZEY; y++) {
        for (int x = 0; x < SIZEX; x++) {
            output[y][x] = 0;
        }
    }

    // --------------------------------------------------------------------------
    //                      Testing with floo-region-1.pgm
    //                     Output file will be output-1.pgm
    // --------------------------------------------------------------------------

    // Read the selected input image into input[][]
    readPGM("floo-region-1.pgm", &input[0][0]);

    // { // print
    //     for (int y = 0; y < SIZEY; y++) {
    //         printf("R#%d:\n", y);
    //         for (int x = 0; x < SIZEX; x++) {
    //             printf("%d\t", input[y][x]);
    //         }
    //         printf("\n");
    //         printf("\n");
    //     }
    //     int allzero = 0;
    //     for (int y = 0; y < SIZEY; y++) {
    //         for (int x = 0; x < SIZEX; x++) {
    //             if (input[y][x] != 0) {
    //                 allzero = 1;
    //                 break;
    //             }
    //         }
    //     }
    //     printf("looking for %d\n", input[16][24]);
    //     printf("all zero: %d\n\n\n", allzero);
    // }

    printf("Calling find_connected_region() on image 1...\n");
    find_connected_region(input, 24, 16,
                          output); // Staring position is (24, 16)

    // { // print
    //     for (int y = 0; y < SIZEY; y++) {
    //         printf("R#%d:\n", y);
    //         for (int x = 0; x < SIZEX; x++) {
    //             printf("%d\t", output[y][x]);
    //         }
    //         printf("\n");
    //         printf("\n");
    //     }
    //     int allzero = 0;
    //     for (int y = 0; y < SIZEY; y++) {
    //         for (int x = 0; x < SIZEX; x++) {
    //             if (output[y][x] != 0) {
    //                 allzero = 1;
    //                 break;
    //             }
    //         }
    //     }
    // }

    // Write the connected region to the output image
    writePGM("output-1.pgm", &output[0][0]);

    // --------------------------------------------------------------------------
    //                      Testing with floo-region-2.pgm
    //                     Output file will be output-2.pgm
    // --------------------------------------------------------------------------

    // // Read the selected input image into input[][]
    // readPGM("floo-region-2.pgm", &input[0][0]);

    // // Don't forget to reset the output array!
    // for (int y = 0; y < SIZEY; y++) {
    //     for (int x = 0; x < SIZEX; x++) {
    //         output[y][x] = 0;
    //     }
    // }

    // printf("Calling find_connected_region() on image 2...\n");
    // find_connected_region(input, 4, 35, output); // Staring position is (4,
    // 35)

    // // Write the connected region to the output image
    // writePGM("output-2.pgm", &output[0][0]);

    printf("Done!\n");
    return 0;
}

#endif
