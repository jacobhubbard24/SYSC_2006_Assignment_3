/********* main.c ********
    Student Name 	= Jacob Hubbard
    Student Number	= 101348462
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a3_nodes.h"
#include "a3_functions.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    
    printf("Testing find_users\n");
    printf("Test 1: looking for arthurhermione\n");
    if (find_user(users, "arthurhermione") != NULL)
    {
        printf("Passed!\n");
    }
    else printf("Failed\n");
    printf("Test 2: looking for malfoygilderoy\n");
    if (find_user(users, "malfoygilderoy") != NULL)
    {
        printf("Passed!\n");
    }
    else printf("Failed\n");

    printf("\nTesting add_users\n");
    printf("Test 1: adding shrek\n");
    users = add_user(users, "shrek", "banana");
    if (find_user(users, "shrek") != NULL)
    {
        printf("Passed!\n");
    }
    else printf("Failed\n");
    printf("Test 2: adding SHREK. Should cause error\n");
    users = add_user(users, "SHREK", "yomama");
    printf("Test 3: adding shrek. Should cause error\n");
    users = add_user(users, "shrek", "123");
    
    

    fclose(csv_file);
 

}
