#ifndef DATA_FUNC_H
#define DATA_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Borrow_Return_Func.h"

#define max_char 30
#define max_line 1000

// create a book information
typedef struct book {
    char id[11];
    char title[max_char];
    char author[max_char];
    char category[max_char];
    int year;
    int quantity;
    int available;
    BookQueue reservationQueue;
} book;

// define number of category value and number of year value
#define numCategory 11
#define numYear 7

// linklist of the book
typedef struct booksNode {
    struct booksNode* next;
    book data; 
} booksNode;

// create listInfo that contain head and tail of each list
typedef struct booksListInfo {
    booksNode* head;
    booksNode* tail;
} booksListInfo;

typedef booksListInfo categoryArray[numCategory][numYear];

categoryArray Library;

// create list of category 
// description of each category is on Data_Func.c : line 4
extern char categoryNames[numCategory][max_char];
extern char cateShortNames[numCategory][4];

// create list of year 
// description of each year range is on Data_Func.c : line 7
extern char yearNames[numYear][max_char];

// create a global path of the csv can be edit in Data_Func.c
extern char pathFile[max_char];

void InitializeLibrary();
void csvToStruct();
int year2yearIndex(int year);

#endif