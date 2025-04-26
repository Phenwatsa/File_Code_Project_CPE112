//[ploy]
#include <stdio.h>
#include "Libralian.h"
#include "../3_Function/Other_Func.h"

void Book_Management(){
    char Book_manag_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("        Welcome to Book Management System\n");
        Line2();
        printf(" [1] | Add Book\n");
        printf(" [2] | Update Book\n");
        printf(" [3] | Delete Book\n");
        printf(" [4] | Show All Books\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input
        scanf(" %s", Book_manag_choice);
        ClearScreen();
        switch (check_Num(Book_manag_choice)){
            case 1:
                // Add book
                //showAllBooks();
                break;
            case 2:
                // Update book
                //filterCategory();
                break;
            case 3:
                // Delete book
                //searchBook();
                break;
            case 4:
                // Show all books
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
    } while (check_Num(Book_manag_choice) != 5);
}

void Member_Management(){
    char Member_manag_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("       Welcome to Member Management System\n");
        Line2();
        printf(" [1] | Register Member\n");
        printf(" [2] | Update Member\n");
        printf(" [3] | Check Borrowing History\n");
        printf(" [4] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input
        scanf(" %s", Member_manag_choice);
        ClearScreen();
        switch (check_Num(Member_manag_choice)){
            case 1:
                // Register member
                //registerMember();
                break;
            case 2:
                // Update member
                //updateMember();
                break;
            case 3:
                // Check borrowing history
                //checkBorrowingHistory();
                break;
            case 4:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again.\n");
                Delay();
        }
    } while (check_Num(Member_manag_choice) != 4);
}

void Borrow_Management(){
    char Borrow_manag_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("       Welcome to Borrow Management System\n");
        Line2();
        printf(" [1] | Borrow Book\n");
        printf(" [2] | Borroeing Queue\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        // User Input
        scanf(" %s", Borrow_manag_choice);
        ClearScreen();
        switch (check_Num(Borrow_manag_choice)){
            case 1:
                // Borrow Book
                break;
            case 2:
                // Borroeing Queue
                break;
            case 3:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again.\n");
                Delay();
        }
    } while (check_Num(Borrow_manag_choice) != 3);
}

void Top_Borrowed_Books(){
    char Top_Borrowed_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("       Welcome to Top Borrowed Books System\n");
        Line2();
        printf(" [1] | Show Top Borrowed Books\n");
        printf(" [2] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input
        scanf(" %s", Top_Borrowed_choice);
        ClearScreen();
        switch (check_Num(Top_Borrowed_choice)){
            case 1:
                // Show top borrowed books
                break;
            case 2:
                // Exit program
                printf("\n Exiting the program . . .\n\n");
                break;
            default:
                // Invalid choice
                printf("\n Invalid choice. Please try again.\n");
                Delay();
        }
    } while (check_Num(Top_Borrowed_choice) != 2);
}

void Menu_Librarian(){
    char Libra_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("      Welcome to Librarian Management System\n");
        Line2();
        printf(" [1] | Book Management\n");
        printf(" [2] | Member Management\n");
        printf(" [3] | Borrow Management\n");
        printf(" [4] | Top Borrowed Books\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        // User Input
        scanf(" %s", Libra_choice);
        ClearScreen();
        switch (check_Num(Libra_choice)){
            case 1:
                // Book management
                Book_Management();
                break;
            case 2:
                // Member management
                Member_Management();
                break;
            case 3:
                // Borrow management
                Borrow_Management();
                break;
            case 4:
                // Top Borrowed Books
                Top_Borrowed_Books();
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