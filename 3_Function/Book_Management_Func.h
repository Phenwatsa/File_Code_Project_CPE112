#define LIBRARY_H
#include "Data_Func.h"
#include "Other_Func.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int filterUsable(char filter[], int number_filter);
void showAllBooks();
int filterCategory();
void showBookList();
void showBookData();
int checkDataEachList();
int isNotInteger();
int searchBook();
