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

#define USERNAME_MAX_LENGTH 32
#define PASSWORD_MAX_LENGTH 17

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

    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    int user_choice = 0;
    
    // printf("Testing find_users\n");
    // printf("Test 1: looking for arthurhermione\n");
    // if (find_user(users, "arthurhermione") != NULL)
    // {
    //     printf("Passed!\n");
    // }
    // else printf("Failed\n");
    // printf("Test 2: looking for malfoygilderoy\n");
    // if (find_user(users, "malfoygilderoy") != NULL)
    // {
    //     printf("Passed!\n");
    // }
    // else printf("Failed\n");
    // printf("\nTesting add_users\n");
    // printf("Test 1: adding shrek\n");
    // users = add_user(users, "shrek", "banana");
    // if (find_user(users, "shrek") != NULL)
    // {
    //     printf("Passed!\n");
    // }
    // else printf("Failed\n");
    // printf("Test 2: adding shrek. Should cause error\n");
    // users = add_user(users, "shrek", "yomama");
    // printf("Test 3: adding shrek. Should cause error\n");
    // users = add_user(users, "shrek", "123");
    
    for (user_t *curr = users; curr; curr = curr->next)
    {
        if (!(curr))
        {
            printf("NULL   ");
        }
        else
        {
            printf("%s   ", curr->username);
        }
    }

    do
    {
        //system("clear");// Since supposed to be always running on Ubuntu, this works to clear the screen before displaying the main menu
        print_menu();
        scanf("%d", &user_choice);
        while(getchar() != '\n');
        switch(user_choice)
        {
            case 1:
                get_username(username, "Enter a username: ");
                get_password(password);
                users = add_user(users, username, password);
                break;
            case 2:
                get_username(username, "Enter a username to update their password: ");
                if (find_user(users, username))
                {
                    check_password(password);
                    if (strcmp(password, find_user(users, username)->password) == 0)
                    {
                        get_password(password);
                    }
                }
                else
                {
                    printf("------------------------------------------\n             User not found.\n------------------------------------------\n");
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        // Print the whole list of users for debugging purposes
        for (user_t *curr = users; curr; curr = curr->next)
        {
            if (!(curr))
            {
                printf("NULL   ");
            }
            else
            {
                printf("%s   ", curr->username);
            }
        }
        printf("\n");
    } while (user_choice != 6);

    fclose(csv_file);
 

}
