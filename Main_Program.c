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
        //ClearScreen();
        Line2();
        printf("     Welcome to the Library Management System\n");
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
                printf("\n Librarian selected . . .\n");
                Delay();
                Menu_Librarian();
                break;
            case 2:
                // For Member
                printf("\n Member selected . . .\n");
                Delay();
                Menu_User();
                break;
            case 3:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again . . .\n");
                Delay();
                break;
        }
    } while (Check_Num(choice) != 3); 
    csvToStruct();
    return 0;
}