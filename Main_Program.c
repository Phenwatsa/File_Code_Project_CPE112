// [ploy]
#include <stdio.h>
#include "1_User/User.h"
#include "2_Libralian/Libralian.h"
#include "3_Function/Book_Management_Func.h"
#include "3_Function/Borrow_Return_Func.h"
#include "3_Function/Data_Func.h"
#include "3_Function/Member_Func.h"
#include "3_Function/Other_Func.h"

int main() {
    char choice[100];

    InitializeLibrary();
    csvToStruct();
    loadMember(&root, "DATA/member.csv");

    do {
        // UI design format
        Line2();
        printf("%45s\n","Welcome to the Library Management System");
        Line2();
        printf(" [1] | Librarian\n");
        printf(" [2] | Member\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User input
        scanf(" %s", choice);
        ClearScreen();
        switch (Check_Num(choice)){
            case 1:
                // For Librarian
                printf(" Librarian selected . . .\n"); Delay();
                Menu_Librarian();
                break;
            case 2:
                // For Member
                printf(" Member selected . . .\n"); Delay();
                Menu_User();
                break;
            case 3:
                // Exit program
                printf(" Exiting the program . . .\n"); Delay();
                break;
            default:
                // Invalid choice
                printf(" Invalid choice. Please try again . . .\n"); Delay();
                break;
        }
    } while (Check_Num(choice) != 3); 
    csvToStruct();
    return 0;
}