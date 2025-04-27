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
int filterCategory(char listName[][max_char], int number_list);
void showAllBooks();
void extractID(char id[16], int* categoryIndex, int* year, int* bookNumberInt);
void addBookParam(int cateIndex, int year, char title[], char author[], int quantity);
void showBookList(booksNode* temp);
void showBookData(booksNode* temp);
int checkDataEachList(booksListInfo linkList, char userInput[]);
int isNotInteger(const char* str);
void searchBook();
void addBook();
void editBook();
void saveCSV();
void deleteBook(booksNode** head, booksNode** tail, booksNode* prev, booksNode* node);
void delete();
#endif