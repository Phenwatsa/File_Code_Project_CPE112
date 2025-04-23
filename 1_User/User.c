//[ploy]
#include <stdio.h>
#include "User.h"
#include "3_Function/Other_Func.h"

void Menu_User(){
    char User_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("       Welcome to Student Management System\n");
        Line2();
        printf(" [1] | Show All Books\n");
        printf(" [2] | Top Borrowed Books\n");
        printf(" [3] | Search Book\n");
        printf(" [4] | Return Book\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input
        scanf(" %s", User_choice);
        ClearScreen();
        switch (check_Num(User_choice)){
            case 1:
                // Show all books
                //showAllBooks();
                break;
            case 2:
                // Top borrowed books
                //filterCategory();
                break;
            case 3:
                // Search book
                //searchBook();
                break;
            case 4:
                // Return book
                //checkDataEachList();
                break;
            case 5:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again.\n");
                Delay();
        }
    } while (check_Num(User_choice) != 5);
}