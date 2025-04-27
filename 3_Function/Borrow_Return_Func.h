#ifndef BORROW_RETURN_FUNC_H 
#define BORROW_RETURN_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_Func.h"
#include "Other_Func.h"

typedef struct booksNode booksNode;
typedef struct QueueNode{
    char User_ID[20];
    struct QueueNode* next;
} QueueNode;

typedef struct BookQueue{
    QueueNode* front;
    QueueNode* rear;
} BookQueue;

// Function Book Borrowing Queue

void Enqueue(BookQueue* queue, char* user_ID);
void Dequeue(BookQueue* queue);
int isQueueEmpty(BookQueue* queue);
void InitializeLibrary_Borrow();
void PrintQueue(BookQueue* queue);
void Borrowing_Queue(booksNode* temp);

// Function to borrow a book
void borrow_Book();

// Function returning a book
void return_Book();
void Show_Borrowed_Books();

#endif