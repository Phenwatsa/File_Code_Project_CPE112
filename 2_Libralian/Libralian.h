#ifndef LIBRALIAN_H
#define LIBRALIAN_H

#include <stdio.h>
#include "../3_Function/Book_Management_Func.h"
#include "../3_Function/Borrow_Return_Func.h"
#include "../3_Function/Data_Func.h"
#include "../3_Function/Member_Func.h"
#include "../3_Function/Other_Func.h"

// Function to manage librarian operations
void Menu_Librarian();

// Function book operations
void Book_Management();
void Member_Management();
void Borrow_Management();
void Top_Borrowed_Books();

// Function to show all books and search for a specific book
void Show_Books_Management();

#endif