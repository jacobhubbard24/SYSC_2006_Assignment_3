/********* main.c ********
    Student Name 	=
    Student Number	=
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

    fclose(csv_file);
 

}