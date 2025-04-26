#define LIBRARY_H
#include "Data_Func.h"
#include "Other_Func.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int filterUsable(char filter[], int number_filter);
int filterCategory();
void showAllBooks();
void extractID();
void addBookParam();
void deleteBook();
void showBookList();
void showBookData();
int checkDataEachList();
int isNotInteger();
int searchBook();
void addBook();
void editBook();
void saveCSV();
