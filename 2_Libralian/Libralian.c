//[ploy]
#include <stdio.h>
#include "Libralian.h"
#include "3_Function/Other_Func.h"

void Menu_Librarian(){
    char Libra_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("       Welcome to Librarian Management System\n");
        Line2();
        printf(" [1] | Book Management\n");
        printf(" [2] | Member Management\n");
        printf(" [3] | Borrow Management\n");
        printf(" [4] | Return Management\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        // User Input
        scanf(" %s", Libra_choice);
        ClearScreen();
        switch (check_Num(Libra_choice)){
            case 1:
                // Book management
                //showAllBooks();
                break;
            case 2:
                // Member management
                //filterCategory();
                break;
            case 3:
                // Borrow management
                //searchBook();
                break;
            case 4:
                // Return management
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
    } while (check_Num(Libra_choice) != 5);
}