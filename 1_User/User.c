//[ploy]
#include "User.h"
#include "../3_Function/Book_Management_Func.h"
#include "../3_Function/Borrow_Return_Func.h"
#include "../3_Function/Data_Func.h"
#include "../3_Function/Member_Func.h"
#include "../3_Function/Other_Func.h"

void Menu_User(memberNode* root) {
    char User_choice[100], temp_User_ID[9];
    int check_UserID = 0;

    // User ID input
    ClearScreen();
    Line2();
    printf("               Please enter your ID\n");
    Line2();
    printf(" Enter your ID : ");
    scanf(" %[^\n]", temp_User_ID);
    check_UserID = Check_User_ID(temp_User_ID);
    while (check_UserID == 0) {
        ClearScreen();
        Line2();
        printf(" Invalid ID. Please try again.\n");
        Line();
        printf(" Please enter your ID\n");
        Line2();
        printf(" Enter your ID : ");
        scanf(" %[^\n]", temp_User_ID);
        check_UserID = Check_User_ID(temp_User_ID);
    }
    memberNode* currentUser = searchMember(root, temp_User_ID);
    if (currentUser == NULL) {
        printf(" !!! Error: Member with ID [%s] not found.\n", temp_User_ID);
        return;
    }

    do{
        // UI design format
        ClearScreen();
        Line2();
        printf(" Hello %s %s [%s]\n", currentUser->data.FirstName, currentUser->data.LastName, currentUser->data.ID);
        printf("       Welcome to Member Management System\n");
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
        switch (Check_Num(User_choice)){
            case 1:
                // Show all books
                showAllBooks();
                Exit();
                break;
            case 2:
                // Top borrowed books
                //filterCategory();
                break;
            case 3:
                // Search book
                searchBook();
                borrow_Book(currentUser);
                Exit();
                break;
            case 4:
                // Return book
                return_Book(temp_User_ID);
                printf("\n ------------Book returned successfully.\n");
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
    } while (Check_Num(User_choice) != 5);
    saveCSV();
}