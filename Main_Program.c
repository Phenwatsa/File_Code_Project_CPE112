// [ploy]
#include <stdio.h>
#include "3_Function/Other_Func.h"

int main() {
    int choice;

    do {
        // UI design format
        ClearScreen();
        Line2();
        printf("     Welcome to the Library Management System\n");
        Line2();
        printf(" [1] | Librarian\n");
        printf(" [2] | Student\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User input
        scanf("%d", &choice);
        ClearScreen();
        switch (choice) {
            case 1:
                // For Librarian
                printf("\n Librarian selected.\n");
                // Call librarian functions here
                Delay();
                break;
            case 2:
                // For Student
                printf("\n Student selected.\n");
                // Call student functions here
                break;
            case 3:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again.\n");
                Delay();
                break;
        }
    } while (choice != 3); 

    return 0;
}