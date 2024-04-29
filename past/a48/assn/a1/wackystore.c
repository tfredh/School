/**
 * Assignment 1 - The Wacky Store
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 1024

typedef struct ItemNode ItemNode;
struct ItemNode {
    char name[MAX_NAME_LENGTH];
    int count;
    ItemNode *next;
};

typedef struct Customer Customer;
struct Customer {
    char name[MAX_NAME_LENGTH];
    ItemNode *cart;
};

typedef struct CheckoutLaneNode CheckoutLaneNode;
struct CheckoutLaneNode {
    Customer *customer;

    CheckoutLaneNode *front;
    CheckoutLaneNode *back;
};

typedef struct CheckoutLane CheckoutLane;
struct CheckoutLane {
    CheckoutLaneNode *first;
    CheckoutLaneNode *last;
};

/**
 * Function: new_item_node
 * -----------------------
 * Allocate a new ItemNode. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided. Assume that
 * count will always be greater than 0.
 */
ItemNode *new_item_node(char *name, int count) {
    ItemNode *newItem = (ItemNode *)malloc(sizeof(ItemNode));

    strcpy(newItem->name, name);
    newItem->count = count;
    newItem->next = NULL;

    return newItem;
}

/**
 * Function: new_customer
 * ----------------------
 * Allocate a new Customer. Allocation must be done manually (with malloc or
 * calloc). Initialize all variables using the arguments provided.
 */
Customer *new_customer(char *name) {
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));

    strcpy(newCustomer->name, name);
    newCustomer->cart = NULL;

    return newCustomer;
}

/**
 * Function: free_customer
 * -----------------------
 * Release all memory associated with a Customer back to the system. This
 * includes any items they may have had in their cart.
 */
void free_customer(Customer *customer) {
    ItemNode *currItem = customer->cart;

    while (currItem != NULL) {
        ItemNode *nextItem = currItem->next;
        free(currItem);
        currItem = nextItem;
    }

    free(customer);
}

/**
 * Function: open_new_checkout_line
 * --------------------------------
 * Allocate a new empty checkout lane. Allocation must be done manually (with
 * malloc or calloc).
 */
CheckoutLane *open_new_checkout_line() {
    CheckoutLane *newCheckoutLane =
        (CheckoutLane *)malloc(sizeof(CheckoutLane));

    newCheckoutLane->first = NULL;
    newCheckoutLane->last = NULL;

    return newCheckoutLane;
}

/**
 * Function: new_checkout_node
 * ---------------------------
 * Allocate a new CheckoutLaneNode. Allocation must be done manually (with
 * malloc or calloc). Initialize all variables using the arguments provided. Do
 * not allocate a new customer; instead copy the existing reference over.
 */
CheckoutLaneNode *new_checkout_node(Customer *customer) {
    CheckoutLaneNode *newCheckoutNode =
        (CheckoutLaneNode *)malloc(sizeof(CheckoutLaneNode));

    newCheckoutNode->customer = customer;
    newCheckoutNode->front = NULL;
    newCheckoutNode->back = NULL;

    return newCheckoutNode;
}

/**
 * Function: add_item_to_cart
 * --------------------------
 * Add an item to a customer's cart, given its name and amount.
 *
 * If the given amount is 0 or less, do nothing.
 *
 * IMPORTANT: The items in a customer's cart should always be arranged in
 * lexicographically smallest order based on the item names. Consider the use of
 * the ASCII strcmp() function from <string.h>.
 *
 * No two ItemNodes in a customer's cart can have the same name.
 * If the customer already has an ItemNode with the same item name in their
 * cart, increase the node's count by the given amount instead.
 */
void add_item_to_cart(Customer *customer, char *item_name, int amount) {
    if (customer == NULL || item_name == NULL || amount <= 0)
        return;

    ItemNode *dummy = new_item_node("", 0);
    dummy->next = customer->cart;
    ItemNode *prev = dummy;
    ItemNode *curr = customer->cart;

    ItemNode *newItem = new_item_node(item_name, amount);
    // if starting cart is already empty
    if (customer->cart == NULL) {
        customer->cart = newItem;
        return;
    }

    while (curr != NULL) {
        if (strcmp(curr->name, item_name) == 0) {
            curr->count += amount;
            break;
            // when the new item should be before (including the very first item
            // in the list)
        } else if (strcmp(curr->name, item_name) > 0) {
            prev->next = newItem;
            newItem->next = curr;
            break;
            // edge case: when the new item should be the last in the list
        } else if (curr->next == NULL) {
            curr->next = newItem;
            break;
        }

        prev = prev->next;
        curr = curr->next;
    }

    customer->cart = dummy->next;
    free(dummy);
}

/**
 * Function: remove_item_from_cart
 * -------------------------------
 * Attempt to reduce the quantity of an item in a customer's cart, given its
 * name and amount.
 *
 * If no ItemNode in the customer's cart match the given item name, or the
 * amount given is <= 0, do nothing.
 *
 * If the quantity is reduced to a value less than or equal to 0, remove the
 * ItemNode from the customer's cart. This means you will need to do memory
 * cleanup as well.
 */
void remove_item_from_cart(Customer *customer, char *item_name, int amount) {
    if (customer == NULL || item_name == NULL || amount <= 0)
        return;

    ItemNode *dummy = new_item_node("", 0);
    dummy->next = customer->cart;
    ItemNode *prev = dummy;
    ItemNode *curr = customer->cart;

    while (curr != NULL) {
        if (strcmp(curr->name, item_name) == 0) {
            curr->count -= amount;

            // remove the item
            if (curr->count <= 0) {
                prev->next = curr->next;
                free(curr);
            }

            break;
        }

        prev = prev->next;
        curr = curr->next;
    }

    customer->cart = dummy->next;
    free(dummy);
}

/**
 * Function: total_number_of_items
 * -------------------------------
 * Count the total number of items in a customer's cart by summing all
 * ItemNodes and their associated quantities.
 */
int total_number_of_items(Customer *customer) {
    ItemNode *currItem = customer->cart;

    int total = 0;
    while (currItem != NULL) {
        total += currItem->count;
        currItem = currItem->next;
    }

    return total;
}

/**
 * Function: queue
 * ---------------
 * A customer has finished shopping and wishes to checkout. Add the given
 * customer to the end of the given checkout lane.
 */
void queue(Customer *customer, CheckoutLane *lane) {
    CheckoutLaneNode *newCustomer = new_checkout_node(customer);

    if (lane->first == NULL) {
        lane->first = newCustomer;
        lane->last = newCustomer;

        // when there's only one customer in the lane
    } else if (lane->first == lane->last) {
        lane->first->back = newCustomer;
        newCustomer->front = lane->first;
        lane->last = newCustomer;
    } else {
        lane->last->back = newCustomer;
        newCustomer->front = lane->last;
        lane->last = newCustomer;
    }
}

/**
 * Function: process
 * -----------------
 * Serve the customer at the head of the checkout lane and return the
 * total_number_of_items() the customer had in their cart.
 *
 * The customer leaves the store after being processed. Therefore, you must
 * also free any memory associated with them.
 *
 * If this function is called on an empty lane, return 0.
 */
int process(CheckoutLane *lane) {
    if (lane == NULL || lane->first == NULL)
        return 0;

    CheckoutLaneNode *checkingOut = lane->first;
    int totalItems = total_number_of_items(checkingOut->customer);

    if (lane->first == lane->last) {
        lane->first = NULL;
        lane->last = NULL;
    } else {
        lane->first = checkingOut->back;
        lane->first->front = NULL;
    }

    free_customer(checkingOut->customer);
    free(checkingOut);

    return totalItems;
}

/**
 * Function: balance_lanes
 * -----------------------
 * Move a single customer from the end of the most busy checkout lane to the
 * end of the least busy checkout lane.
 *
 * Busyness is defined as the total number of customers in a checkout lane.
 *
 * If multiple lanes have the same busyness, select the lane that comes
 * first in the CheckoutLane* array.
 *
 * If the difference between the MAX and MIN checkout lanes is <= 1, do
 * nothing.
 *
 * If there are less than 2 lanes, do nothing.
 *
 * Return true if and only if a customer was moved; otherwise false.
 */
int get_lane_size(CheckoutLane *lane) {
    // helper for balance_lanes
    int size = 0;

    CheckoutLaneNode *curr = lane->first;
    while (curr != NULL) {
        size += 1;
        curr = curr->back;
    }

    return size;
}
bool balance_lanes(CheckoutLane *lanes[], int number_of_lanes) {
    if (number_of_lanes < 2)
        return false;

    CheckoutLane *shortest = NULL;
    int shortest_size = __INT_MAX__;
    CheckoutLane *longest = NULL;
    int longest_size = -__INT_MAX__;

    for (int i = 0; i < number_of_lanes; i++) {
        CheckoutLane *lane = lanes[i];
        int lane_size = get_lane_size(lane);
        // printf("name %s\n", lane->first->customer->name);

        if (lane_size > longest_size) {
            longest = lane;
            longest_size = lane_size;
        }
        if (lane_size < shortest_size) {
            shortest = lane;
            shortest_size = lane_size;
        }
        // separated `if`s for edge cases.
        // 1. if first value is smallest, it gets wrongly added as `longest`
        // 2. potentially leaving a lane NULL and failing difference check later
    }

    // printf("shortest %s, longest %s\n", shortest->first->customer->name,
    //        longest->first->customer->name);

    // edge cases: abs(a, b) <= 1, longest lane already empty or size 1)
    if (longest_size - shortest_size <= 1 || longest->first == NULL) {
        return false;
    } else {
        CheckoutLaneNode *oldLast = longest->last;
        CheckoutLaneNode *newLast = longest->last->front;

        // remove customer from longest line
        newLast->back = NULL;
        longest->last = newLast;

        // add customer to shortest line
        queue(oldLast->customer, shortest);

        return true;
    }
}

/**
 * Function: process_all_lanes
 * ---------------------------
 * Given an array of CheckoutLane*, process() each CheckoutLane a single
 * time and return the the sum of the result.
 */
int process_all_lanes(CheckoutLane *lanes[], int number_of_lanes) {
    int sum = 0;

    for (int i = 0; i < number_of_lanes; i++) {
        sum += process(lanes[i]);
    }

    return sum;
}

/**
 * Function: close_store
 * ---------------------
 * It's closing time. Given an array of CheckoutLane*, free all memory
 * associated with them. Any customers still left in the queue is kicked out
 * and also freed from memory.
 */
void close_store(CheckoutLane *lanes[], int number_of_lanes) {
    for (int i = 0; i < number_of_lanes; i++) {
        CheckoutLane *lane = lanes[i];

        CheckoutLaneNode *currLaneNode = lane->last;
        while (currLaneNode != NULL) {
            // printf("freeing %s\n", currLaneNode->customer->name);

            CheckoutLaneNode *laneNodeAfter = currLaneNode->front;
            free_customer(currLaneNode->customer);
            free(currLaneNode);

            // don't need to set the new last node's ->back value to NULL
            // since it's being removed as well anyways

            currLaneNode = laneNodeAfter;
        }

        free(lane);
    }
}
