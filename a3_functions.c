/*****************
    Student Name 	= Jacob Hubbard
    Student Number	= 101348462
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ctype.h> // for tolower() function
#include "a3_nodes.h"
#include "a3_functions.h"

// Your solution goes here

#define USERNAME_MAX_LENGTH 32
#define PASSWORD_MAX_LENGTH 17
#define POST_MAX_LENGTH 252
/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
   Assumes password is at least 8 characters.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    char *username_lowered = malloc(strlen(username + 1));
    assert(username_lowered);
    strcpy(username_lowered, username);
    convert_to_lower(username_lowered);
    if (!users)
    {
        user_t* new_user = malloc(sizeof(user_t));
        assert(new_user);
        new_user->next = NULL;
        for (int i = 0; i < strlen(username_lowered); i++)
        {
            new_user->username[i] = username_lowered[i];
        }
        new_user->username[strlen(username_lowered)] = '\0';
        for (int i = 0; i < strlen(password); i++)
        {
            new_user->password[i] = password[i];
        }
        new_user->friends = NULL;
        new_user->posts = NULL;
        return new_user;
    }
    else if (find_user(users, username_lowered))
    {
        printf("ERROR: User provided already exists\n");
    }
    else
    {
        // Loop through the linked list of users
        for (user_t *curr = users; curr->next; curr = curr->next)
        {
            if (strcmp(curr->next->username, username_lowered) > 0)
            {
                user_t* new_user = malloc(sizeof(user_t));
                assert(new_user);
                new_user->next = curr->next;
                curr->next = new_user;
                for (int i = 0; i < strlen(username_lowered); i++)
                {
                    new_user->username[i] = username_lowered[i];
                }
                for (int i = 0; i < strlen(password); i++)
                {
                    new_user->password[i] = password[i];
                }
                new_user->friends = NULL;
                new_user->posts = NULL;
            }
        }
        
    }
    free(username_lowered);
    username_lowered = NULL;
    return users;
}

/*
   Function that searches if the user is available in the database 
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
    if (users != NULL)
    {
        // Loop through the linked list of users
        for (user_t *curr = users; curr; curr = curr->next)
        {
            if (strcmp(curr->username, username) == 0)
            {
                return curr;
            }
            else printf(" a ");
        }
    }
    return NULL;
}


/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{

}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{

}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{

}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{

}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{

}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{

}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{

}


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{

}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *users, int number)
{

}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{

}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
    printf("***********************************************\n");
    printf("                 MAIN MENU:\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("2. Manage a user's posts (add/remove)\n");
    printf("2. Manage a user's friends (add/remove)\n");
    printf("2. Display a user's posts\n");
    printf("6. Exit\n\n");
    printf("Enter your choice:\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and should be used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

void convert_to_lower(char *str)
{
    if (str == NULL)
    {
        printf("ERROR: CANNOT LOWER NULL STRING\n");
        return;
    }
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}