#ifndef BOOK_MANAGEMENT_FUNC_H
#define BOOK_MANAGEMENT_FUNC_H
#include "Data_Func.h"
#include "Other_Func.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int filterCategory(char listName[][max_char], int number_list);
int filterUsable(char filter[], int number_filter);
void addBook();
void editBook();
void deleteBook(booksNode* head, booksNode* prev, booksNode* node);
void saveCSV();
booksNode* bookParam(int cateIndex, int year, char title[], char author[], int quantity);
int* extractID(char id[15]);
void showAllBooks();
void showBookList(booksNode* temp);
void showBookData(booksNode* temp);
int checkDataEachList(booksListInfo linkList, char userInput[]);
int isNotInteger(const char* str);

#endif