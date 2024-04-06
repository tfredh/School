/**
 * Assignment 3 - Wacky Marketing
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
#include "marketing.c"
#include <assert.h>

/**
 * You may modify this file however you wish as it will not be submitted on
 * Quercus. Please ensure that your code still works and does not depend on this
 * file as the automarker will be using a different main().
 */

int main() {
    // Create new users
    User *william = create_user("William");
    User *angela = create_user("Angela");
    User *mustafa = create_user("Mustafa");
    User *brian = create_user("Brian");

    printf("\nTest 1 - Users printed in alphabetical order\n");
    FriendNode *t = allUsers;
    int idx = 0;
    while (t != NULL && t->next != NULL) {
        if (strcmp(t->user->name, t->next->user->name) > 0) {
            printf("Test 1 failed. Users are not sorted.\n");
            exit(1);
        }

        idx++;
        t = t->next;
    }

    if (idx != 3) {
        printf("Test 1 failed. Users were not inserted.\n");
        exit(1);
    }

    printf("Test 1 passed.\n");

    printf("\nTest 2 - Angela adds Brian as a friend\n");
    add_friend(angela, brian);

    // Expect to see Angela with her friend Brian & see Brian with his friend
    // Angela
    if (!in_friend_list(angela->friends, brian) ||
        !in_friend_list(brian->friends, angela)) {
        printf("Test 2 failed. Friend connection was not made.\n");
        exit(1);
    }

    printf("Test 2 passed.\n");

    // // MINE: test deleting user
    // {
    //     printf("Names: ");
    //     for (FriendNode *f = allUsers; f != NULL; f = f->next) {
    //         printf("%s\t", f->user->name);
    //     }
    //     delete_user(mustafa);
    //     printf("\nNames after delete: ");
    //     for (FriendNode *f = allUsers; f != NULL; f = f->next) {
    //         printf("%s\t", f->user->name);
    //     }
    //     printf("\nDelete successful\n");
    // }

    // // MINE: TEST removing friendship
    // {
    //     printf("\n");
    //     printf("angela friend 1: %s\n", angela->friends->user);
    //     assert(strcmp(angela->friends->user->name, "Brian") == 0);
    //     printf("brian friend 1: %s\n", brian->friends->user);
    //     assert(strcmp(brian->friends->user->name, "Angela") == 0);

    //     remove_friend(angela, brian);

    //     printf("angela friend 1: %s\n", angela->friends); // should be (null)
    //     assert(angela->friends == NULL);
    //     printf("brian friend 1: %s\n", brian->friends); // should be (null)
    //     assert(brian->friends == NULL);

    //     printf("Removal friendhsip succ\n");
    // }

    // {
    //     // MINE: follow brand test
    //     printf("\n");
    //     printf("angela brand 1: %s\n", angela->brands);
    //     assert(angela->brands == NULL);

    //     printf("[following brands]\n");
    //     follow_brand(angela, "brandZero");
    //     follow_brand(angela, "brandzOne");
    //     printf("angela brand 1: %s\n", angela->brands->brand_name);
    //     assert(strcmp(angela->brands->brand_name, "brandZero") == 0);
    //     printf("angela brand 2: %s\n", angela->brands->next);
    //     assert(strcmp(angela->brands->next->brand_name, "brandzOne") == 0);

    //     // MINE: test unfollow_brand
    //     printf("[unfollowing brands]\n");
    //     unfollow_brand(angela, "brandzOne");
    //     printf("angela brand 1: %s\n", angela->brands->brand_name);
    //     printf("angela brand 2: %s\n", angela->brands->next);
    //     assert(strcmp(angela->brands->brand_name, "brandZero") == 0);
    //     assert(angela->brands->next == NULL);

    //     unfollow_brand(angela, "brandZero");
    //     printf("Unfollowing all brands\n");
    //     printf("angela brand 1: %s\n", angela->brands);
    //     assert(angela->brands == NULL);
    // }

    printf("\nTest 3 - Degree of connection between Angela and Brian is 1\n");
    int angela_and_brian = get_degrees_of_connection(angela, brian);

    if (angela_and_brian != 1) { // Expect 1
        printf("Test 3 failed. Friend connection was not made.\n");
        exit(1);
    }

    // // MINE: further connection degree checks
    // {
    //     // add more friends
    //     add_friend(brian, william);
    //     add_friend(william, mustafa);
    //     add_friend(mustafa, angela);
    //     // check connection degrees
    //     int angela_and_william = get_degrees_of_connection(angela, william);
    //     int angela_and_mustafa = get_degrees_of_connection(angela, mustafa);
    //     int angela_and_angela = get_degrees_of_connection(angela, angela);
    //     printf("Angela and William: %d\n", angela_and_william);
    //     printf("Angela and Mustafa: %d\n", angela_and_mustafa);
    //     printf("Angela and Angela: %d\n", angela_and_angela);
    //     assert(angela_and_william == 2);
    //     assert(angela_and_mustafa == 1);
    //     assert(angela_and_angela == 0);
    //     int angela_and_brian = get_degrees_of_connection(angela, brian);
    //     printf("Angela and Brian: %d\n", angela_and_brian);
    // }
    {
        // test #2, add more friends
        // add_friend(angela, brian); -- already done in previous provided test
        add_friend(brian, mustafa);
        add_friend(mustafa, william);

        // all 1st connections
        assert(get_degrees_of_connection(angela, brian) == 1);
        assert(get_degrees_of_connection(brian, mustafa) == 1);
        assert(get_degrees_of_connection(mustafa, william) == 1);
        assert(get_degrees_of_connection(william, mustafa) == 1);

        // all 2nd connections
        assert(get_degrees_of_connection(angela, mustafa) == 2);
        assert(get_degrees_of_connection(brian, william) == 2);

        // all 3rd connections
        assert(get_degrees_of_connection(angela, william) == 3);
        assert(get_degrees_of_connection(william, angela) == 3);

        printf("[MINE]: All connection degrees correct\n");
    }

    // printf("Test 3 passed.\n");

    // printf("\nTest 4 - Angela follows Brand 'brandonRufino'\n");
    // populate_brand_matrix("brands.txt");
    // follow_brand(angela, "brandonRufino");

    // // Angela should now follow brandonRufino.
    // if (!in_brand_list(angela->brands, "brandonRufino")) {
    //     printf("Test 4 failed. Brand connection was not made.\n");
    //     exit(1);
    // }

    // printf("Test 4 passed.\n");

    // printf("\nTest 5 - Connect Brands 'brandZero' and 'brandTwo'\n");
    // connect_similar_brands("brandZero", "brandTwo");
    // int zeroIdx = get_brand_index("brandZero");
    // int twoIdx = get_brand_index("brandTwo");

    // if (brand_adjacency_matrix[zeroIdx][twoIdx] != 1 ||
    //     brand_adjacency_matrix[twoIdx][zeroIdx] != 1) {
    //     printf("Test 5 failed. Brand connection was not made.\n");
    //     exit(1);
    // }

    // printf("Test 5 passed.\n");

    // printf("\nTest 6 - William and Brian have Angela as a mutual friend\n");
    // add_friend(angela, william);
    // int mutuals_brian_will = get_mutual_friends(brian, william);

    // if (mutuals_brian_will != 1) { // Expect 1
    //     printf("Test 6 failed. Mutual friends of Brian and William should be "
    //            "1.\n");
    //     exit(1);
    // }

    // printf("Test 6 passed.\n");

    // printf("\nTest 7 - Brian is suggested 1 friend\n");
    // User *brianSuggested = get_suggested_friend(brian);

    // if (brianSuggested != william) { // We should see Will here again
    //     printf("Test 7 failed. Brian was not suggested William.\n");
    //     exit(1);
    // }

    // printf("Test 7 passed.\n");

    // printf("\nTest 8 - Mustafa adds 2 suggested friends\n");

    // add_friend(angela, mustafa);
    // add_suggested_friends(mustafa, 2);

    // // Expect to see Mustafa with friends Angela, Brian, and Will
    // if (!in_friend_list(mustafa->friends, brian) ||
    //     !in_friend_list(mustafa->friends, william)) {
    //     printf(
    //         "Test 8 failed. Mustafa was not suggested 2 friends correctly.\n");
    //     exit(1);
    // }

    // printf("Test 8 passed.\n");

    // printf("\nTest 9 - Mustafa follows 1 suggested brand\n");
    // follow_brand(william, "brandTwo");
    // follow_brand(mustafa, "brandZero");
    // follow_suggested_brands(mustafa, 1);

    // // Mustafa should now also follow brandonRufino. A tie is broken against
    // // brandTwo.
    // if (!in_brand_list(mustafa->brands, "brandonRufino")) {
    //     printf(
    //         "Test 9 failed. Mustafa did not follow brand 'brandonRufino'.\n");
    //     exit(1);
    // }

    // printf("Test 9 passed.\n");

    // printf("\nAll basic test cases passed. :)\n");
}
