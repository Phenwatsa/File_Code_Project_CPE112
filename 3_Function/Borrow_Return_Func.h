#ifndef BORROW_RETURN_FUNC_H 
#define BORROW_RETURN_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_Func.h"
#include "Other_Func.h"
#include "Borrow_Return_Func.h"

// Function to borrow a book
void borrow_Book();

// Function Book Borrowing Queue
typedef struct QueueNode{
    char User_ID[20];
    struct QueueNode* next;
} QueueNode;

typedef struct BookQueue{
    QueueNode* front;
    QueueNode* rear;
} BookQueue;

void Enqueue(BookQueue* queue, char* user_ID);
void Dequeue(BookQueue* queue);
int isQueueEmpty(BookQueue* queue);
void InitializeLibrary();
void PrintQueue(BookQueue* queue);
void Borrowing_Queue(booksNode* temp);

// Function returning a book
void return_Book();

#endif