//[Ploy]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Book_Management_Func.h"
#include "Member_Func.h"
#include "Data_Func.h"
#include "Other_Func.h"
#include "Borrow_Return_Func.h"

booksNode* searchBook_ID(booksNode* root, const char* bookID) {
    booksNode* current = root;
    while (current != NULL) {
        if (strcmp(current->data.id, bookID) == 0) {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}

void AddBorrowedBook(memberNode* member, const char* bookID, const char* title, const char* status) {
    BookBorrowing* NewBorrow = (BookBorrowing*)malloc(sizeof(BookBorrowing));
    if (NewBorrow == NULL) {
        printf(" !!! Error : Memory allocation failed.\n");
        return;
    }

    strcpy(NewBorrow->Member_ID, member->data.ID);
    strcpy(NewBorrow->Book_ID, bookID);
    strcpy(NewBorrow->Title, title);
    NewBorrow->next = NULL;

    if (member->borrowList == NULL) {
        member->borrowList = NewBorrow;
    } else {
        BookBorrowing* temp = member->borrowList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = NewBorrow;
    }    
}

void DeleteBorrowedBook(memberNode* member, const char* bookID) {
    if (member == NULL || member->borrowList == NULL) {
        return;
    }

    BookBorrowing* current = member->borrowList;
    BookBorrowing* previous = NULL;

    while (current != NULL && strcmp(current->Book_ID, bookID) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf(" !!! Error : Book with ID [%s] not found in borrow list.\n", bookID);
        return;
    }

    if (previous == NULL) {
        member->borrowList = current->next; 
    } else {
        previous->next = current->next; 
    }
    free(current);
}

void LoadBorrowHistory(const char* filename, memberNode* root){
    FILE* ptFile = fopen(filename, "r");
    if (ptFile == NULL){
        printf(" !!! Error : Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), ptFile)) {
        char* userID = strtok(line, ",");
        char* bookID = strtok(NULL, ",");
        char* title = strtok(NULL, ",");
        char* status = strtok(NULL, "\n");
        if (status != NULL) {
            while (isspace((unsigned char)*status)) status++;
            status[strcspn(status, "\r\n")] = '\0';           
        }

        if (!userID || !bookID || !title || !status) {
            printf(" !!! Error : Invalid line format: %s\n", line);
            continue;
        }

        status[strcspn(status, "\n")] = '\0';
        if (strcmp(status, "Borrowed") == 0) {
            memberNode* member = searchMember(root, userID);
            if (member == NULL) {
                printf(" !!! Warning : Member with ID [%s] not found.\n", userID);
                continue;
            }
            AddBorrowedBook(member, bookID, title, status);
        }
    }
    fclose(ptFile);
}

void DisplayBorrowing(memberNode* Borrowing_Member){
    if (Borrowing_Member == NULL) {
        Line2();
        printf(" !!! Error: Invalid member.\n");
        Line2();
        return;
    }

    if (Borrowing_Member->borrowList == NULL){
        Line2();
        printf(" Member [%s] has no books borrowed.\n", Borrowing_Member->data.ID);
        Line2();
        return;
    }

    Line2();
    printf(" Borrowing Books List for Member [%s]\n", Borrowing_Member->data.ID); 
    Line2();

    BookBorrowing* temp = Borrowing_Member->borrowList;
    printf(" %-20s %-50s\n", "Book ID", "Title");
    while (temp != NULL) {
        printf(" %-20s %-50s\n", temp->Book_ID, temp->Title);
        temp = temp->next;
    }
    Line2();
}

int CountBorrowedBooks(memberNode* member){
    int count = 0;
    BookBorrowing* temp = member->borrowList;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void LoadBorrowQueue(const char* filename, memberNode* memberRoot, booksNode* bookRoot){
    FILE* ptFile = fopen(filename, "r");
    if (ptFile == NULL) {
        printf(" !!! Error : Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), ptFile); // Skip header line

    while (fgets(line, sizeof(line), ptFile)) {
        char* userID = strtok(line, ",");
        char* bookID = strtok(NULL, ",");
        char* title = strtok(NULL, ",");
        char* Queue_Position = strtok(NULL, "\n");

        if (!userID || !bookID || !title || !Queue_Position) {
            printf(" !!! Error : Invalid line format: %s\n", line);
            continue;
        }

        int queuePosition = atoi(Queue_Position);
        
        booksNode* book = searchBook_ID(bookRoot, bookID);
        if (book == NULL) {
            printf(" !!! Warning : Book with ID [%s] not found.\n", bookID);
            continue;
        }

        if (book->data.reservationQueue == NULL) {
            book->data.reservationQueue = (BookQueue*)malloc(sizeof(BookQueue));
            book->data.reservationQueue->front = NULL;
            book->data.reservationQueue->rear = NULL;
        }
        Enqueue(book->data.reservationQueue, userID);
    }
    fclose(ptFile);
}

void saveBorrowQueue(const char* filename, memberNode* root) {
    FILE* ptFile = fopen(filename, "w");
    if (ptFile == NULL) {
        printf(" !!! Error : Could not open file %s\n", filename);
        return;
    }

    fprintf(ptFile, "User_ID,Book_ID,Title,Status\n");

    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                QueueNode* queueTemp = temp->data.reservationQueue->front;

                while (queueTemp != NULL) {
                    fprintf(ptFile, "%s,%s,%s,%s\n", queueTemp->User_ID, temp->data.id, temp->data.title, "Reserved");
                    queueTemp = queueTemp->next;
                }
                temp = temp->next;
            }
        }
    }
    fclose(ptFile);
}

// Function to borrow a book
void borrow_Book(memberNode* member){
    if (CountBorrowedBooks(member) >= 3) {
        printf(" You cannot borrow more than 3 books at a time.\n");
        return;
    }

    char book_id[20];
    int book_found = 0;

    // Prompt user for book name
    Line2();
    printf(" Enter the ID of the book you want to borrow : ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    for (int i = 0 ; i < numCategory ; i++){
        for (int j = 0 ; j < numYear ; j++){
            booksNode* temp = Library[i][j].head; 
            while (temp != NULL){
                if (strcmp(temp->data.id, book_id)==0){
                    book_found = 1;
                    Line();
                    printf(" Book found: %s (ID : %s)\n", temp->data.title, temp->data.id);
                    printf(" Quantity available : %d\n", temp->data.quantity);
                    Line();

                    //Check if the book is available
                    char Confirm;
                    do {
                        printf(" Do you want to borrow this book? (Y/N) : ");
                        scanf(" %c", &Confirm);
                    } while (Confirm != 'Y' && Confirm != 'y' && Confirm != 'N' && Confirm != 'n');

                    if (Confirm == 'Y' || Confirm == 'y'){
                        if (temp->data.quantity > 0){
                            temp->data.quantity--;
                            if (temp->data.quantity <= 0){
                                temp->data.available = 0;
                            }
                            AddBorrowedBook(member, temp->data.id, temp->data.title, "Borrowed");
                            writeBorrowHistoryToCSVFile(member->data.ID, temp->data.id, temp->data.title, "Borrowed");
                            saveCSV();
                            updateBorrowCount(temp->data.id);
                            Line();
                            printf(" You have successfully borrowed the book: %s (ID: %s)\n", temp->data.title, temp->data.id);
                            Line2();
                        }
                        else{
                            Line();
                            printf(" Sorry, this book is not available for borrowing.\n");
                            Borrowing_Queue(temp);
                        }
                    }
                    else if (Confirm == 'N' || Confirm == 'n'){
                        Line();
                        printf(" Borrowing cancelled.\n");                        
                        Line2();
                    }
                    return;
                }                    
                temp = temp->next;
            }
        }
    }

    if (book_found==0){
        Line();
        printf(" Book not found.\n");
        Line2();
    }
}

// Function Book Borrowing Queue
void Enqueue(BookQueue* queue, char* user_ID) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    printf("1.1\n");
    strcpy(newNode->User_ID, user_ID);
    newNode->next = NULL;
    printf("1.2\n");
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
        printf("Queue is empty, added first node.\n");
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
        printf("Added to the end of the queue.\n");
    }
    printf("1.3\n");
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

void InitializeLibrary_Borrow() {
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                if (temp->data.reservationQueue == NULL) {
                    temp->data.reservationQueue = (BookQueue*)malloc(sizeof(BookQueue));
                }
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
        printf("1\n");
        printf("Adding %s to the reservation queue for book %s\n", user_ID, temp->data.title);
        Enqueue(temp->data.reservationQueue, user_ID);
        printf("2\n");
    } else {
        printf("Reservation cancelled.\n");
    }
    printf("3--------------------\n");
    saveBorrowQueue("DATA/Borrowing_Queue.csv", root);
}

void NotifyReservationQueue(memberNode* member, booksNode* bookRoot){

    if (member == NULL) {
        printf(" !!! Error: Invalid member.\n");
        return;
    }

    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                if (temp->data.reservationQueue != NULL && temp->data.reservationQueue->front != NULL) {
                    // ตรวจสอบว่าผู้ใช้คนแรกในคิวตรงกับสมาชิกที่ล็อกอินหรือไม่
                    if (strcmp(temp->data.reservationQueue->front->User_ID, member->data.ID) == 0) {
                        printf("\n !!! Notification: The book '%s' (ID: %s) is now available for you.\n", temp->data.title, temp->data.id);
                        printf(" Do you want to borrow this book? (Y/N): ");
                        
                        char confirm;
                        scanf(" %c", &confirm);

                        if (confirm == 'Y' || confirm == 'y') {
                            // ดำเนินการยืมหนังสือ
                            if (temp->data.quantity > 0) {
                                temp->data.quantity--;
                                if (temp->data.quantity <= 0) {
                                    temp->data.available = 0;
                                }
                                AddBorrowedBook(member, temp->data.id, temp->data.title, "Borrowed");
                                writeBorrowHistoryToCSVFile(member->data.ID, temp->data.id, temp->data.title, "Borrowed");
                                updateBorrowCount(temp->data.id);
                                printf(" You have successfully borrowed the book: %s (ID: %s)\n", temp->data.title, temp->data.id);
                            } else {
                                printf(" Sorry, this book is no longer available.\n");
                            }
                        } else if (confirm == 'N' || confirm == 'n') {
                            printf(" You have declined to borrow the book.\n");
                        }

                        // ลบสมาชิกออกจากคิว
                        Dequeue(temp->data.reservationQueue);
                    }
                }
                temp = temp->next;
            }
        }
    }
}

// Function returning a book
void return_Book(memberNode* member){
    char book_id[20];
    int book_found = 0;

    // Prompt user for book name
    if (member != NULL) {
        DisplayBorrowing(member); // เรียกฟังก์ชันเพื่อแสดงรายการยืมของสมาชิก
    } else {
        printf(" !!! Warning : Member with ID [%s] not found.\n", member->data.ID);
    }
    Line();
    printf(" Enter the ID of the book you want to return : ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    for (int i = 0 ; i < numCategory ; i++){
        for (int j = 0 ; j < numYear ; j++){
            booksNode* temp = Library[i][j].head;
            while (temp != NULL){
                if (strcmp(temp->data.id, book_id)==0){
                    book_found = 1;
                    printf(" Book found: %s (ID: %s)\n", temp->data.title, temp->data.id);

                    // Check if the book is available
                    char Confirm;
                    printf(" Do you want to return this book? (Y/N): ");
                        //ใส่ฟังชั่นเช็คคำตอบเพิ่ม
                    scanf(" %c", &Confirm);

                    if (Confirm == 'Y' || Confirm == 'y'){
                        temp->data.quantity++;
                        temp->data.borrowCount++;
                        if (temp->data.quantity >0 ){
                            temp->data.available = 1;
                        }
                        
                        changingStatusToReturn(member->data.ID, temp->data.id);
                        DeleteBorrowedBook(member, temp->data.id);
                        updateBorrowCount(temp->data.id);
                        printf("You have successfully returned the book: %s (ID: %s)\n", temp->data.title, temp->data.id);

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

void displayBorrowingMemberTree(memberNode *node) {
    if (!node) return;

    // Traverse the left subtree
    displayBorrowingMemberTree(node->left);

    // Display only members who are borrowing books
    if (node->borrowList != NULL) {
        printf(" Member ID: %s | Name: %s %s\n", node->data.ID, node->data.FirstName, node->data.LastName);
        printf(" Borrowed Books:\n");

        // Use a temporary pointer to traverse the borrowList
        BookBorrowing* temp = node->borrowList;
        while (temp != NULL) {
            printf("  - %s: %s\n", temp->Book_ID, temp->Title);
            temp = temp->next;
        }
        printf("\n");
    }

    // Traverse the right subtree
    displayBorrowingMemberTree(node->right);
}

void Display_All_Borrowing(memberNode* root) {
    if (root == NULL) {
        printf(" !!! No borrowing history available.\n");
        return;
    }

    Line2();
    printf(" All Borrowing Members and Their Borrowed Books\n");
    Line2();

    // Call the recursive function to display the borrowing tree
    displayBorrowingMemberTree(root);

    Line2();
}

void Display_All_Borrowing_Queue(BookQueue* queue) {
    if (queue == NULL || queue->front == NULL) {
        printf("The borrowing queue is empty.\n");
        return;
    }

    QueueNode* temp = queue->front;
    int position = 1; // ตำแหน่งในคิว
    Line2();
    printf(" Borrowing Queue:\n");
    Line();
    printf(" %-10s | %-20s\n", "Position", "User ID");
    Line();

    while (temp != NULL) {
        printf(" %-10d | %-20s\n", position, temp->User_ID);
        temp = temp->next;
        position++;
    }
    Line2();
}

//Funcion write borrow history to csv
int writeBorrowHistoryToCSVFile(const char *memberID,const char *bookID, const char *title, const char *status)
{
    FILE *fp = fopen("DATA/borrow_history.csv", "a");
    if (!fp)
    {
        perror("Error opening file.\n");
        return 0;
    }
    fprintf(fp,"%s,%s,%s,%s\n",memberID,bookID,title,status);
    fclose(fp);
    return 1;
    
}

void Show_Borrowed_Books(){
    
}

//Funcion update borrowed count
void updateBorrowCount(const char *bookID) 
{
    if (bookID == NULL) 
    {
        fprintf(stderr, "Error: bookID is NULL\n");
        return;
    }
    FILE *fp = fopen("DATA/Book-ID.csv", "r");
    if (fp == NULL) 
    {
        perror("Error opening Book-ID.csv");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) 
    {
        perror("Error creating temp file");
        fclose(fp);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) 
    {
        char id[20], title[200], author[100], category[50], year[6], status[20];
        int quantity, borrowCount;

        int fields = sscanf(line, "%19[^,],%199[^,],%99[^,],%49[^,],%5[^,],%d,%19[^,],%d",id, title, author, category, year, &quantity, status, &borrowCount);
        if (fields != 8) 
        {
            fputs(line, temp);
            continue;
        }

        if (strcmp(id, bookID) == 0) 
        {
            borrowCount+=1;
        }

        fprintf(temp, "%s,%s,%s,%s,%s,%d,%s,%d\n", id, title, author, category, year, quantity, status, borrowCount);
    }

    fclose(fp);
    fclose(temp);

    if (remove("DATA/Book-ID.csv") != 0) 
    {
        perror("Error deleting original file");
        return;
    }
    if (rename("temp.csv", "DATA/Book-ID.csv") != 0) 
    {
        perror("Error renaming temp file");
    }
}

//Funcion changing status to return in history csv file
int changingStatusToReturn(const char *memberId, const char *bookId)
{
    FILE *fp = fopen("DATA/borrow_history.csv", "r+");
    FILE *tem = fopen("tem.csv", "w");
    if (!fp || !tem)
    {
        perror("Error opening file.\n");
        return 0;
    }
    
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) 
    {
        char member[20], book[20], title[200], status[20];
        sscanf(line,"%[^,],%[^,],%[^,],%[^\n]", member, book, title, status);

        if((strcmp(member, memberId)== 0) && (strcmp(book, bookId)== 0) && (strcmp(status, "Borrowed") == 0))
        {
            fprintf(tem, "%s,%s,%s,Returned\n", member, book,title);
            found = 1;
        } else
        {
            fprintf(tem, "%s", line);
        }
        
    }

    fclose(fp);
    fclose(tem);
    remove("DATA/borrow_history.csv");
    rename("tem.csv", "DATA/borrow_history.csv");
    return found;

}
