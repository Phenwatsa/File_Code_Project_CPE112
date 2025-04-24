//[Ploy]

#include <stdio.h>
#include <stdlib.h>
#include "Borrow_Return_Func.h"
#include "Data_Func.h"
#include "Book_Management_Func.h"
#include "Other_Func.h"

// Function to borrow a book
void borrow_Book(){
    char book_id[20];
    int book_found = 0;

    // Prompt user for book name
    printf("Enter the ID of the book you want to borrow: ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    /*for (i = 0; i < total_books; i++) {
        if (strcmp(books[i].name, book_name) == 0) {
            book_found = 1;
            strcpy(book_id, books[i].id);
            break;
        }
    }*/

    if (book_found!=0) {
        //printf("You have borrowed the book: %s (ID: %s)\n", book_name, book_id);
        // Update the database or perform any other necessary actions here
    } else {
        printf("Book not found.\n");
    }
}