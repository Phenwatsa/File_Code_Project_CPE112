//[Ploy]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data_Func.h"
#include "Other_Func.h"
#include "Borrow_Return_Func.h"

// Function to borrow a book
void borrow_Book(){
    char book_id[20];
    int book_found = 0;

    // Prompt user for book name
    printf("Enter the ID of the book you want to borrow : ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    for (int i = 0 ; i < numCategory ; i++){
        for (int j = 0 ; j < numYear ; j++){
            booksNode* temp = Library[i][j].head; 
            while (temp != NULL){
                if (strcmp(temp->data.id, book_id)==0){
                    book_found = 1;
                    printf("Book found: %s (ID: %s)\n", temp->data.title, temp->data.id);

                    //Check if the book is available
                    char Confirm;
                    printf("Do you want to borrow this book? (Y/N): ");
                        //ใส่ฟังชั่นเช็คคำตอบเพิ่ม
                    scanf(" %c", &Confirm);

                    if (Confirm == 'Y' || Confirm == 'y'){
                        if (temp->data.available > 0){
                            temp->data.available--;
                            printf("You have successfully borrowed the book: %s (ID: %s)\n", temp->data.title, temp->data.id);
                        }
                        else{
                            printf("Sorry, this book is not available for borrowing.\n");
                            Borrowing_Queue(temp);
                        }
                    }
                    else if (Confirm == 'N' || Confirm == 'n'){
                        printf("Borrowing cancelled.\n");                        
                    }
                    return;
                }                    
                temp = temp->next;
            }
        }
    }

    if (book_found==0){
        printf("Book not found.\n");
    }
}

// Function Book Borrowing Queue
void Enqueue(BookQueue* queue, char* user_ID){
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strcpy(newNode->User_ID, user_ID);
    newNode->next = NULL;

    if (queue->rear == NULL){
        queue->front = newNode;
        queue->rear = newNode;
    }
    else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("User %s added to the queue.\n", user_ID);
}

void Dequeue(BookQueue* queue){
    if (queue->front == NULL){
        printf("The reservation queue is empty.\n");
        return;
    }

    QueueNode* temp = queue->front;
    printf("Notifying %s that the book is now available.\n", temp->User_ID);
    queue->front = queue->front->next;

    if (queue->front == NULL){
        queue->rear = NULL;
    }
    free(temp);
}

int isQueueEmpty(BookQueue* queue){
    return (queue->front == NULL);
}

void InitializeLibrary_Borrow(){
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            Library[i][j].head = NULL;
            Library[i][j].tail = NULL;

            // Initialize reservation queue
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                temp->data.reservationQueue->front = NULL;
                temp->data.reservationQueue->rear = NULL;
                temp = temp->next;
            }
        }
    }
}

void PrintQueue(BookQueue* queue){
    if (queue->front == NULL) {
        printf("The queue is empty.\n");
        return;
    }

    QueueNode* temp = queue->front;
    printf("Current queue: ");
    while (temp != NULL) {
        printf("%s -> ", temp->User_ID);
        temp = temp->next;
    }
    printf("NULL\n");
}

void Borrowing_Queue(booksNode* temp){
    char reserve_queue;
    printf("Do you want to join the reservation queue? (Y/N): ");
    scanf(" %c", &reserve_queue);

    if (reserve_queue == 'Y' || reserve_queue == 'y') {
        char user_ID[50];
        printf("Enter your ID: ");
        scanf(" %[^\n]", user_ID);

        // Add the user to the reservation queue
        Enqueue(temp->data.reservationQueue, user_ID);
        PrintQueue(temp->data.reservationQueue);
    } else {
        printf("Reservation cancelled.\n");
    }
}

// Function returning a book
void return_Book(){
    char book_id[20];
    int book_found = 0;

    // Prompt user for book name
    void Show_Borrowed_Books();
    printf("Enter the ID of the book you want to return : ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    for (int i = 0 ; i < numCategory ; i++){
        for (int j = 0 ; j < numYear ; j++){
            booksNode* temp = Library[i][j].head;
            while (temp != NULL){
                if (strcmp(temp->data.id, book_id)==0){
                    book_found = 1;
                    printf("Book found: %s (ID: %s)\n", temp->data.title, temp->data.id);

                    // Check if the book is available
                    char Confirm;
                    printf("Do you want to return this book? (Y/N): ");
                        //ใส่ฟังชั่นเช็คคำตอบเพิ่ม
                    scanf(" %c", &Confirm);

                    if (Confirm == 'Y' || Confirm == 'y'){
                        temp->data.available++;
                        printf("You have successfully returned the book: %s (ID: %s)\n", temp->data.title, temp->data.id);

                        if (isQueueEmpty(temp->data.reservationQueue) == 0) {
                            Dequeue(temp->data.reservationQueue);
                        }
                        else{
                            printf("No one is waiting for this book.\n");
                        }
                    }
                    else if (Confirm == 'N' || Confirm == 'n'){
                        printf("Returning cancelled.\n");                        
                    }
                    return;
                }
                temp = temp->next;
            }
        }
    }
    if (book_found==0){
        printf("Book not found.\n");
    }
}

void Show_Borrowed_Books(){
    Line2();
    printf(" borrowed books\n");
    Line();
    // Display borrowed books
    printf("Borrowed books are displayed here.\n");
    Line2();
    printf("\n");
}