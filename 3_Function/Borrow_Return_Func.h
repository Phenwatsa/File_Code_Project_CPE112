#ifndef BORROW_RETURN_FUNC_H 
#define BORROW_RETURN_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Member_Func.h"
#include "Data_Func.h"
#include "Other_Func.h"

typedef struct booksNode booksNode ;
typedef struct memberNode memberNode;

typedef struct QueueNode{
    char User_ID[20];
    struct QueueNode* next;
} QueueNode;

typedef struct BookQueue{
    QueueNode* front;
    QueueNode* rear;
} BookQueue;

typedef struct BookBorrowing{
    char Member_ID[20];
    char Book_ID[20];
    char Title[100];
    struct BookBorrowing* next;
} BookBorrowing;

booksNode* searchBook_ID(booksNode* root, const char* bookID);

// Function csvToStruct
void AddBorrowedBook(memberNode* member, const char* bookID, const char* title, const char* status);
void LoadBorrowHistory(const char* filename, memberNode* root);
void DisplayBorrowing(memberNode* Borrowing_Member);
int CountBorrowedBooks(memberNode* member);

void LoadBorrowQueue(const char* filename, memberNode* memberRoot, booksNode* bookRoot);

// Function Book Borrowing Queue
void Enqueue(BookQueue* queue, char* user_ID);
void Dequeue(BookQueue* queue);
int isQueueEmpty(BookQueue* queue);
void InitializeLibrary_Borrow();
void PrintQueue(BookQueue* queue);
void Borrowing_Queue(booksNode* temp);

// Function to borrow a book
void borrow_Book(memberNode* member);

// Function returning a book
void return_Book();
void Show_Borrowed_Books();

#endif