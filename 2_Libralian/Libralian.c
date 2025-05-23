#include <stdio.h>
#include "Libralian.h"
#include "../3_Function/Book_Management_Func.h"
#include "../3_Function/Borrow_Return_Func.h"
#include "../3_Function/Data_Func.h"
#include "../3_Function/Member_Func.h"
#include "../3_Function/Other_Func.h"

// Function to show all books and search for a specific book
void Show_Books_Management(){
    char Show_Books_choice[100];
    do{
        // UI design format
        ClearScreen(); Line2();
        printf("%44s\n","Welcome to Show Books Management System");
        Line2();
        printf(" [1] | Show All Books\n");
        printf(" [2] | Search Book\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", Show_Books_choice);
        ClearScreen();
        switch (Check_Num(Show_Books_choice)){
            case 1: // Show all books
                showAllBooks();
                break;
            case 2: // Search book
                searchBook();
                Exit();
                break;
            case 3: // Exit program
                printf(" Exiting the program . . .\n\n");
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Show_Books_choice) != 3);
}

// Function to manage book operations
void Book_Management(){
    char Book_manag_choice[100];
    do{
        // UI design format
        ClearScreen(); Line2();
        printf(" %40s\n","Welcome to Book Management System");
        Line2();
        printf(" [1] | Add Book\n");
        printf(" [2] | Update Book\n");
        printf(" [3] | Delete Book\n");
        printf(" [4] | Show Books\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", Book_manag_choice);
        ClearScreen();
        switch (Check_Num(Book_manag_choice)){
            case 1: // Add book
                addBook(); 
                break;
            case 2: // Update book
                editBook();
                break;
            case 3: // Delete book
                delete();
                break;
            case 4: // Show all books
                Show_Books_Management();
                break;
            case 5: // Exit program
                printf(" Exiting the program . . .\n"); Delay();
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Book_manag_choice) != 5);
    saveCSV();
}
// Function to manage member operations
void Member_Management(){
    char Member_manag_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("%42s\n","Welcome to Member Management System");
        Line2();
        printf(" [1] | Register Member\n");
        printf(" [2] | Update Member\n");
        printf(" [3] | Display All Members\n");
        printf(" [4] | Check Borrowing History\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", Member_manag_choice);
        ClearScreen();
        switch (Check_Num(Member_manag_choice)){
            case 1: // Register member
                Register_Member();
                break;
            case 2: // Update member
                updateMember(root);
                break;
            case 3: // Display All Members
                displayMember(root); 
                break;
            case 4: // Check borrowing history
                Check_Borrowing_History();
                break;
            case 5: // Exit program
                printf(" Exiting the program . . .\n\n");
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Member_manag_choice) != 5);
}
// Function to manage borrowing operations
void Borrow_Management(){
    char Borrow_manag_choice[100];
    do{
        // UI design format
        ClearScreen(); Line2();
        printf("%42s\n","Welcome to Borrow Management System");
        Line2();
        printf(" [1] | Borrowed Books List\n");
        printf(" [2] | Reservation Queue\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");

        // User Input
        scanf(" %s", Borrow_manag_choice);
        ClearScreen();
        switch (Check_Num(Borrow_manag_choice)){
            case 1: // Borrowed Books List
                Display_All_Borrowing(root);
                break;
            case 2: // Reservation Queue
                Display_All_Borrowing_Queue_AllBooks();
                break;
            case 3: // Exit program
                printf(" Exiting the program . . .\n\n");
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Borrow_manag_choice) != 3);
}
// Function to manage top borrowed books
void Top_Borrowed_Books(){
    char Top_Borrowed_choice[100];
    do{
        // UI design format
        ClearScreen(); Line2();
        printf("       Welcome to Top Borrowed Books System\n");
        Line2();
        printf(" [1] | Top 5 Borrowed Books\n");
        printf(" [2] | Top 3 Most Active Borrowers\n");
        printf(" [3] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", Top_Borrowed_choice);
        ClearScreen();
        switch (Check_Num(Top_Borrowed_choice)){
            case 1: // Show Top 5 Most Borrowed Books
                displayTop5BorrowedBooks();
                break;
            case 2: // Show top 3 members who borrowed (and returned) the most books
                showTop3MembersWithMostReturns("DATA/borrow_history.csv", "DATA/member.csv");
                break;
            case 3: // Exit program
                printf(" Exiting the program . . .\n");
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Top_Borrowed_choice) != 3);
}

void Menu_Librarian(){
    char Libra_choice[100];
    do{
        // UI design format
        ClearScreen();
        Line2();
        printf("%44s\n","Welcome to Librarian Management System");
        Line2();
        printf(" [1] | Book Management\n");
        printf(" [2] | Member Management\n");
        printf(" [3] | Borrow Management\n");
        printf(" [4] | Top Borrowed Books\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", Libra_choice);
        ClearScreen();
        switch (Check_Num(Libra_choice)){
            case 1: // Book management
                Book_Management();
                break;
            case 2: // Member management
                Member_Management();
                break;
            case 3: // Borrow management
                Borrow_Management();
                break;
            case 4: // Top Borrowed Books
                Top_Borrowed_Books();
                break;
            case 5: // Exit program
                printf(" Exiting the program . . .\n\n");
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n");
                Delay();
        }
    } while (Check_Num(Libra_choice) != 5);
    saveCSV();
    saveMember(root, "DATA/member.csv");
}