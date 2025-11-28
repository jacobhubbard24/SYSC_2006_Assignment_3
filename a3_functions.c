/*****************
    Student Name 	= Jacob Hubbard
    Student Number	= 101348462
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a3_nodes.h"
#include "a3_functions.h"

// Your solution goes here

#define USERNAME_MAX_LENGTH 32
#define PASSWORD_MAX_LENGTH 17
#define PASSWORD_MIN_LENGTH 8
#define POST_MAX_LENGTH 252

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
   Assumes password is at least 8 characters.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    //Username already exists in list
    if (find_user(users, username))
    {
        printf("ERROR: User provided already exists\n");
    }
    else
    {
        user_t* new_user = malloc(sizeof(user_t));
        assert(new_user);
        new_user->next = NULL;
        new_user->friends = NULL;
        new_user->posts = NULL;
        strcpy(new_user->username, username);
        strcpy(new_user->password, password);
        users = insert_user(users, new_user);
    }
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
    friend_t *new_friend = malloc(sizeof(friend_t));
    assert(new_friend);
    new_friend->next = NULL;
    strcpy(new_friend->username, username);
    return new_friend;
}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    friend_t *new_friend = create_friend(friend);
    friend_t *prev = NULL;
    for (friend_t *curr = user->friends; curr; curr = curr->next)
    {
        if (strcmp(curr->username, new_friend->username) > 0)
        {
            
            if (prev == NULL)
            {
                new_friend->next = user->friends;
                user->friends = new_friend;
                return;
            }
            else
            {
                prev->next = new_friend;
                new_friend->next = curr;
                return;
            }
        }
        else if (curr->next == NULL)
        {
            curr->next = new_friend;
            new_friend->next = NULL;
            return;
        }
        prev = curr;
    }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    friend_t *prev = NULL;
    for (friend_t *curr = user->friends; curr; curr = curr->next)
    {
        if (strcmp(friend_name, curr->username) == 0)
        {
            prev->next = curr->next;
            free(curr);
            curr = NULL;
            return true;
        }
        prev = curr;
    }
    return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post);
    strcpy(new_post->content, text);
    new_post->next = NULL;
    return new_post;
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
    post_t *new_post = create_post(text);
    new_post->next = user->posts;
    user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
    if (user->posts)
    {
        post_t *temp = user->posts;
        user->posts = user->posts->next;
        free(temp);
        temp = NULL;
    }
    return false;
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
    printf("------------------------------------------\n             %s's posts.\n------------------------------------------\n", user->username);

    int i = 1;
    for (post_t *curr = user->posts; curr; curr = curr->next)
    {
        printf("%d- %s\n", i, curr->content);
    }
    printf("------------------------------------------\n");

}


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
    if (user)
    {
        int i = 1;
        printf("List of %s's friends:\n", user->username);
        for (friend_t *curr = user->friends; curr; curr = curr->next, i++)
        {
            printf("%d- %s\n", i, curr->username);
        }
    }
    else printf("User does not exist.\n");
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns. 
*/
void display_posts_by_n(user_t *user, int number)
{
    post_t *curr = user->posts;
    for (int i = 1; i <= number; i++)
    {
        if (curr + i)
        {
            printf("%d- %s\n", i, (curr + i)->content);
        }
        else 
        {
            i = number + 1; // End the loop if no more posts available
        }
    }
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    // Free all users
    while (users)
    {
        user_t *next = users->next;

        // Free all friends of each user
        while (users->friends)
        {
            delete_friend(users, users->username);
        }
        // Free all posts of each user
        while (users->posts)
        {
            delete_post(users);
        }
        free(users);
        users = next;
    }
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
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user's posts\n");
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
        if (*str >= 'A' && *str <= 'Z') // If in A-Z
        {
            *str = *str + ('a' - 'A');// Add the ASCII difference between uppercase and lowercase
        }
        str++;
    }
}

user_t *insert_user(user_t *users, user_t *user_to_insert)
{
    if (!users)
    {
        return user_to_insert;
    }
    else
    {
        user_t *prev = NULL;
        for (user_t *curr = users; curr; curr = curr->next)
        {
            if (strcmp(curr->username, user_to_insert->username) > 0)
            {
                
                if (prev == NULL)
                {
                    user_to_insert->next = users;
                    users = user_to_insert;
                    return users;
                }
                else
                {
                    prev->next = user_to_insert;
                    user_to_insert->next = curr;
                    return users;
                }
            }
            else if (curr->next == NULL)
            {
                curr->next = user_to_insert;
                user_to_insert->next = NULL;
                return users;
            }
            prev = curr;
        }
    }
    return users;
}


void get_username(char *username, char *prompt)
{
    do
    {
        printf("%s", prompt);
        fgets(username, USERNAME_MAX_LENGTH, stdin);
    } while (!strstr(username, "\n"));
    // Remove the newline character
    char *newline = strchr(username, '\n');
    *newline = '\0';
    convert_to_lower(username);
}

void get_password(char *password)
{
    do
    {
        printf("Enter a password between 8-15 characters: ");
        fgets(password, PASSWORD_MAX_LENGTH, stdin);
    } while (!strstr(password, "\n") || (strlen(password) - 1) < PASSWORD_MIN_LENGTH); // strlen(password) - 1 to account for the newline character
    // Remove the newline character
    char *newline = strchr(password, '\n');
    *newline = '\0';
}

void check_password(char *password)
{
    printf("Enter the password: ");
    fgets(password, PASSWORD_MAX_LENGTH, stdin);
    // Remove the newline character
    char *newline = strchr(password, '\n');
    *newline = '\0';
}

void get_post(char *post)
{
    printf("Enter your post content: ");
    scanf(" %[^\n]s", post);
}

void get_friend(char *friend, char *prompt)
{
    printf("%s", prompt);
    scanf("%s", friend);
}