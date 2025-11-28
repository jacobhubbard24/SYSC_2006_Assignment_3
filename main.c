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
#define POST_MAX_LENGTH 252
#define NUM_POSTS_DISPLAYED_INITIALLY 3

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

    
    int user_choice = 0;
    
    // for (user_t *curr = users; curr; curr = curr->next)
    // {
        // // if (!(curr))
        // // {
        // //     printf("NULL   ");
        // // }
        // // else
        // // {
        // //     printf("%s   ", curr->username);
    //     // }
    // }

    do
    {
        // Local username, password, post and friend are initialized each run-through in order to clear them
        char username[USERNAME_MAX_LENGTH];
        char password[PASSWORD_MAX_LENGTH];
        char post[POST_MAX_LENGTH];
        char friend[USERNAME_MAX_LENGTH];

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
                        strcpy(find_user(users, username)->password, password); 
                        printf("Password updated successfully!\n");
                    }
                    else
                    {
                        printf("------------------------------------------\n           Password incorrect.\n------------------------------------------\n");
                    }
                }
                else
                {
                    printf("------------------------------------------\n             User not found.\n------------------------------------------\n");
                }
                break;
            case 3:
                get_username(username, "Enter a username to manage their posts: ");
                if (find_user(users, username))
                {
                    int user_choice_posts = 0;
                    do 
                    {
                        printf("------------------------------------------\n          Managing %s's posts.\n------------------------------------------\n", username);
                        // Display note if the user has no posts
                        if (!find_user(users, username)->posts)
                        {
                            printf("Note: No posts available for %s\n", username);
                        }
                        printf("1. Add a new post\n2. Remove a post\n3. Return to main menu\n");
                        scanf("%d", &user_choice_posts);
                        switch (user_choice_posts)
                        {
                            case 1:
                                get_post(post);
                                add_post(find_user(users, username), post);
                                display_all_user_posts(find_user(users, username));
                                break;
                            case 2:
                                if (delete_post(find_user(users, username)))
                                {
                                    display_all_user_posts(find_user(users, username));
                                }
                                else 
                                {
                                    printf("------------------------------------------\n             No posts to delete.\n------------------------------------------\n");
                                }
                                user_choice_posts = 3;
                                break;
                            default:
                                printf( "Invalid choice. Please try again.\n");
                        }
                    }while (user_choice_posts != 3);                    
                }
                break;
            case 4:
                get_username(username, "Enter a username to update their friends: ");
                if (find_user(users, username))
                {
                    int user_choice_friends = 0;
                    do 
                    {
                        printf("------------------------------------------\n          Managing %s's Friends.\n------------------------------------------\n", username);
                        // Display note if the user has no friends
                        if (!find_user(users, username)->friends)
                        {
                            printf("Note: %s is lonely and has no friends :(\n", username);
                        }
                        printf("1. Add a new friend\n2. Remove a friend\n3. Return to main menu\n");
                        scanf("%d", &user_choice_friends);
                        switch (user_choice_friends)
                        {
                            case 1:
                                get_friend(friend, "Enter a new friend's name: ");
                                add_friend(find_user(users, username), friend);
                                break;
                            case 2:
                                display_user_friends(find_user(users, username));
                                get_friend(friend, "Enter a friend's name to delete: ");
                                if (delete_friend(find_user(users, username), friend))
                                {
                                    user_choice_friends = 3;
                                }
                                break;
                            default:
                                printf( "Invalid choice. Please try again.\n");
                        }
                    }while (user_choice_friends != 3);
                }
                break;
            case 5:
                get_username(username, "Enter a username to display their posts: ");
                if (find_user(users, username))
                {
                    char *user_choice_yn;
                    do 
                    {
                        display_posts_by_n(find_user(users, username), NUM_POSTS_DISPLAYED_INITIALLY);
                        if (find_user(users, username)->posts)
                        {
                            printf("Enter whether you would like to display more posts (Y/N): ");
                            scanf("%s", user_choice_yn);
                            convert_to_lower(user_choice_yn);
                        }
                        else 
                        {
                            printf("------------------------------------------\n      All posts have been displayed.\n------------------------------------------\n");
                            strcpy(user_choice_yn, "n");
                        }
                    } while (strcmp("n", user_choice_yn) != 0);
                    
                }
                else 
                {
                    printf("------------------------------------------\n             User not found.\n------------------------------------------\n");
                }
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        // Print the whole list of users for debugging purposes
        // for (user_t *curr = users; curr; curr = curr->next)
        // {
        //     if (!(curr))
        //     {
        //         printf("NULL   ");
        //     }
        //     else
        //     {
        //         printf("%s   ", curr->username);
        //     }
        // }
        printf("\n");
    } while (user_choice != 6);

    teardown(users);
    fclose(csv_file);
}
