//[ploy]
#include <stdio.h>
#include "Libralian.h"
#include "../3_Function/Book_Management_Func.h"
#include "../3_Function/Member_Func.h"
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
        switch (Check_Num(Book_manag_choice)){
            case 1:
                // Add book
                addBook();
                Exit();
                break;
            case 2:
                // Update book
                editBook();
                Exit();
                break;
            case 3:
                // Delete book
                delete();
                Exit();
                break;
            case 4:
                // Show all books
                showAllBooks();
                Exit();
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
    } while (Check_Num(Book_manag_choice) != 5);
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
        printf(" [3] | Display All Members\n");
        printf(" [4] | Check Borrowing History\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input
        scanf(" %s", Member_manag_choice);
        ClearScreen();
        switch (Check_Num(Member_manag_choice)){
            case 1:
                // Register member
                Register_Member();
                Exit();
                break;
            case 2:
                // Update member
                updateMember(root);
                break;
            case 3:
                // Display All Members
                displayMember(root); 
                Exit();
                break;
            case 4:
                // Check borrowing history
                Check_Borrowing_History();
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
    } while (Check_Num(Member_manag_choice) != 5);
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
        switch (Check_Num(Borrow_manag_choice)){
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
    } while (Check_Num(Borrow_manag_choice) != 3);
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
        switch (Check_Num(Top_Borrowed_choice)){
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
    } while (Check_Num(Top_Borrowed_choice) != 2);
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
        switch (Check_Num(Libra_choice)){
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
    } while (Check_Num(Libra_choice) != 5);
}