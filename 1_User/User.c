#include "User.h"
#include "../3_Function/Book_Management_Func.h"
#include "../3_Function/Borrow_Return_Func.h"
#include "../3_Function/Data_Func.h"
#include "../3_Function/Member_Func.h"
#include "../3_Function/Other_Func.h"

void Menu_User(memberNode* root) {
    char User_choice[100], temp_User_ID[9];
    int check_UserID = 0;

    // Input User ID & Check ID in the system
    while (check_UserID == 0) {
        ClearScreen();
        Line2();
        printf(" Please enter your ID\n");
        Line2();
        printf(" Enter your ID : ");
        scanf(" %[^\n]", temp_User_ID);
        check_UserID = Check_User_ID(temp_User_ID); // Check if the ID is valid
    }

    // Point to the member node
    memberNode* currentUser = searchMember(root, temp_User_ID);
    //Notify the user about their reservation queue
    NotifyReservationQueue(currentUser, Library[0][0].head);

    do{
        // UI design format
        ClearScreen(); Line2();
        printf("%42s\n","Welcome to Member Management System");
        Line();
        printf(" [%s] %s %s\n", 
            currentUser->data.ID, 
            currentUser->data.FirstName, 
            currentUser->data.LastName);
        Line2();
        printf(" [1] | Show All Books\n");
        printf(" [2] | The Most Borrowed Book\n");
        printf(" [3] | Search Book\n");
        printf(" [4] | Return Book\n");
        printf(" [5] | Exit\n");
        Line2();
        printf(" Please select an option : ");
        
        // User Input for menu selection
        scanf(" %s", User_choice);
        ClearScreen();
        switch (Check_Num(User_choice)){
            case 1: // Show all books
                showAllBooks();
                break;
            case 2: // Top borrowed books
                displayTop5BorrowedBooks();
                break;
            case 3: // Search & Borrow book
                searchBook();
                borrow_Book(currentUser);
                Exit();
                break;
            case 4: // Return book
                return_Book(currentUser);
                Exit();
                break;
            case 5: // Exit program
                printf(" Exiting the program . . .\n"); Delay();
                break;
            default: // Invalid choice
                printf(" Invalid choice. Please try again.\n"); Delay();
        }
    } while (Check_Num(User_choice) != 5);
    saveCSV();
    saveBorrowQueue("DATA/Borrowing_Queue.csv", root);
}