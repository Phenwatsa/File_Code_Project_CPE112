#ifndef BOOK_MANAGEMENT_FUNC_H
#define BOOK_MANAGEMENT_FUNC_H
#include "Data_Func.h"
#include "Other_Func.h"
#include "Book_Management_Func.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int filterCategory(char listName[][max_char], int number_list);
int filterUsable(char filter[], int number_filter);
int filterCategory();
void showAllBooks();
void extractID();
void addBookParam();
void showBookList();
void showBookData();
int checkDataEachList();
int isNotInteger();
int searchBook();
void addBook();
void editBook();
void saveCSV();
void deleteBook();
void delete();
#endif