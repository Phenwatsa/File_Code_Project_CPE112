#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Book_Management_Func.h"
#include "Member_Func.h"
#include "Data_Func.h"
#include "Other_Func.h"
#include "Borrow_Return_Func.h"

// Function to search for a member by ID
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

// Function Add Data to Borrowed Book Structure
void AddBorrowedBook(memberNode* member, const char* bookID, const char* title, const char* status) {
    BookBorrowing* NewBorrow = (BookBorrowing*)malloc(sizeof(BookBorrowing));
    if (NewBorrow == NULL) {
        ClearScreen();
        printf(" !!! Error : Memory allocation failed.\n");
        Line(); Delay();
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

// Function to delete a borrowed book from the member's list
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
        ClearScreen();
        printf(" !!! Error : Book with ID [%s] not found in borrow list.\n", bookID);
        Line(); Delay();
        return;
    }

    if (previous == NULL) {
        member->borrowList = current->next; 
    } else {
        previous->next = current->next; 
    }
    free(current);
}

// Function to load borrowing history from a CSV file
void LoadBorrowHistory(const char* filename, memberNode* root){
    FILE* ptFile = fopen(filename, "r");
    if (ptFile == NULL){
        ClearScreen();
        printf(" !!! Error : Could not open file %s\n", filename);
        Line(); Delay();
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

// Function to display borrowing history for a specific member
void DisplayBorrowing(memberNode* Borrowing_Member){
    if (Borrowing_Member == NULL) {
        ClearScreen();
        printf(" !!! Error: Invalid member.\n");
        Line(); Delay();
        return;
    }

    if (Borrowing_Member->borrowList == NULL){
        ClearScreen();
        printf(" !!! Member [%s] has no books borrowed.\n", Borrowing_Member->data.ID);
        Line(); Delay();
        return;
    }

    Line2();
    printf(" Borrowing Books List for Member [%s]\n", Borrowing_Member->data.ID); 
    Line2();
    
    // Display the borrowed books
    BookBorrowing* temp = Borrowing_Member->borrowList;
    printf(" %-20s %-50s\n", "Book ID", "Title");
    while (temp != NULL) {
        printf(" %-20s %-50s\n", temp->Book_ID, temp->Title);
        temp = temp->next;
    }
    Line2();
}

// Function to count the number of borrowed books for a member
int CountBorrowedBooks(memberNode* member){
    int count = 0;
    BookBorrowing* temp = member->borrowList;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to load borrowing queue from a CSV file
void LoadBorrowQueue(const char* filename, memberNode* memberRoot, booksNode* bookRoot){
    FILE* ptFile = fopen(filename, "r");
    if (ptFile == NULL) {
        ClearScreen();
        printf(" !!! Error : Could not open file %s\n", filename);
        Line(); Delay();
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

// Function to save borrowing queue to a CSV file
void saveBorrowQueue(const char* filename, memberNode* root) {
    FILE* ptFile = fopen(filename, "w");
    if (ptFile == NULL) {
        ClearScreen();
        printf(" !!! Error : Could not open file %s\n", filename);
        Line(); Delay();
        return;
    }

    // Write header
    fprintf(ptFile, "Member_ID,Book_ID,Title,Queue_Position\n");

    // Write borrowing queue data
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                if (temp->data.reservationQueue != NULL) {
                    QueueNode* queueTemp = temp->data.reservationQueue->front;
                    while (queueTemp != NULL) {
                        fprintf(ptFile, "%s,%s,%s,%s\n", 
                            queueTemp->User_ID, temp->data.id, temp->data.title, "Reserved");
                        queueTemp = queueTemp->next;
                    }
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
        ClearScreen();
        printf(" !!!You cannot borrow more than 3 books at a time.\n");
        Line(); Exit();
        return;
    }

    char book_id[20];
    int book_found = 0;

    printf(" Enter the ID of the book you want to borrow : ");
    scanf(" %[^\n]", book_id);

    // Search for the book in the list
    for (int i = 0 ; i < numCategory ; i++){
        for (int j = 0 ; j < numYear ; j++){
            // Check if the book is in the library
            booksNode* temp = Library[i][j].head; 
            while (temp != NULL){
                // Check if the book ID matches
                if (strcmp(temp->data.id, book_id)==0){
                    book_found = 1;
                    ClearScreen(); Line();
                    printf(" Book found: %s (ID : %s)\n", temp->data.title, temp->data.id);
                    printf(" Quantity available : %d\n", temp->data.quantity);
                    Line();


                    char Confirm;
                    do {
                        // Ask for confirmation to borrow the book
                        printf(" Do you want to borrow this book? (Y/N) : ");
                        scanf(" %c", &Confirm);
                    } while (Confirm != 'Y' && Confirm != 'y' && Confirm != 'N' && Confirm != 'n');

                    // Check if the user wants to borrow the book
                    if (Confirm == 'Y' || Confirm == 'y'){
                        if (temp->data.quantity > 0){
                            // Proceed with borrowing the book
                            temp->data.quantity--;
                            if (temp->data.quantity <= 0){
                                temp->data.available = 0;
                            }
                            // Add the book to the member's borrowed list
                            AddBorrowedBook(member, temp->data.id, temp->data.title, "Borrowed");
                            writeBorrowHistoryToCSVFile(member->data.ID, temp->data.id, temp->data.title, "Borrowed");
                            saveCSV(); updateBorrowCount(temp->data.id);
                            Line();
                            printf(" You have successfully borrowed the book: %s (ID: %s)\n", temp->data.title, temp->data.id);
                            Line2();
                        }
                        else{
                            // Book is not available for borrowing
                            Line();
                            printf(" Sorry, this book is not available for borrowing.\n");
                            // Ask if the user wants to join the reservation queue
                            Borrowing_Queue(temp);
                        }
                    }
                    // Check if the user does not want to borrow the book
                    else if (Confirm == 'N' || Confirm == 'n'){
                        Line();
                        printf(" Borrowing cancelled.\n");                        
                        Line2();
                    }
                    Exit();
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
    Exit();
}

// Function to create a new queue node
void Enqueue(BookQueue* queue, char* user_ID) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));

    strcpy(newNode->User_ID, user_ID);
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a user from the reservation queue
void Dequeue(BookQueue* queue){
    if (queue->front == NULL){
        ClearScreen();
        printf(" !!!The reservation queue is empty.\n");
        Line(); Delay();
        return;
    }

    QueueNode* temp = queue->front;

    queue->front = queue->front->next;

    if (queue->front == NULL){
        queue->rear = NULL;
    }
    free(temp);
}

int isQueueEmpty(BookQueue* queue){
    return (queue->front == NULL);
}

// Function to initialize the reservation queue for all books in the library
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

// Function to print the reservation queue
void PrintQueue(BookQueue* queue){
    if (queue->front == NULL) {
        ClearScreen();
        printf("The queue is empty.\n");
        Line(); Delay();
        return;
    }

    QueueNode* temp = queue->front;
    printf(" Current queue: ");
    while (temp != NULL) {
        printf("%s -> ", temp->User_ID);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to add a user to the reservation queue
// This function is called when a book is not available for borrowing
void Borrowing_Queue(booksNode* temp){
    char reserve_queue;
    do{
        ClearScreen();
        printf(" Do you want to join the reservation queue (Y/N): ");
        scanf(" %c", &reserve_queue);
    } while (reserve_queue != 'Y' && reserve_queue != 'y' && reserve_queue != 'N' && reserve_queue != 'n');

    if (reserve_queue == 'Y' || reserve_queue == 'y') {
        char user_ID[50];
        printf(" Enter your ID: ");
        scanf(" %[^\n]", user_ID);

        // Add the user to the reservation queue
        printf(" Adding [%s] to the reservation queue for book : %s\n", user_ID, temp->data.title);
        Enqueue(temp->data.reservationQueue, user_ID);
        PrintQueue(temp->data.reservationQueue);
    } else {
        ClearScreen();
        printf(" Reservation cancelled.\n");
        Line(); Delay();
        return;
    }
    saveBorrowQueue("DATA/Borrowing_Queue.csv", root);
    Exit();
}

// Function to notify a member about the availability of a book
void NotifyReservationQueue(memberNode* member, booksNode* bookRoot){
    if (member == NULL) {
        ClearScreen();
        printf(" !!! Error: Invalid member.\n");
        Line(); Delay();
        return;
    }

    // Check if the member has any books in the reservation queue
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                // Check if the book has a reservation queue
                if (temp->data.reservationQueue != NULL && temp->data.reservationQueue->front != NULL) {
                    if (strcmp(temp->data.reservationQueue->front->User_ID, member->data.ID) == 0) {
                        ClearScreen(); Line2();
                        printf("   Member ID: [%s] | Name: [%s %s]\n", 
                            member->data.ID, member->data.FirstName, member->data.LastName);
                        Line2();
                        printf("\n !!! Notification !!!\n");
                        Line2();
                        printf(" The book '%s' (ID: %s) \n is now available for you.\n", 
                            temp->data.title, temp->data.id);
                        Line2();
                        printf(" Do you want to borrow this book (Y/N): ");
                        
                        char confirm;
                        scanf(" %c", &confirm);

                        // User confirmation to borrow the book
                        if (confirm == 'Y' || confirm == 'y') {
                            if (temp->data.quantity > 0) {
                                temp->data.quantity--;
                                if (temp->data.quantity <= 0) {
                                    temp->data.available = 0;
                                }
                                AddBorrowedBook(member, temp->data.id, temp->data.title, "Borrowed");
                                writeBorrowHistoryToCSVFile(member->data.ID, temp->data.id, temp->data.title, "Borrowed");
                                updateBorrowCount(temp->data.id);
                                ClearScreen();
                                printf(" You have successfully borrowed the book: %s (ID: %s)\n", 
                                    temp->data.title, temp->data.id);
                                Line2(); Delay();
                            }
                        } else if (confirm == 'N' || confirm == 'n') {
                            ClearScreen();
                            printf(" You have declined to borrow the book.\n");
                            Line2(); Delay();
                        }
                        // Remove the user from the reservation queue
                        Dequeue(temp->data.reservationQueue);
                    }
                }
                temp = temp->next;
            }
        }
    }
    saveBorrowQueue("DATA/Borrowing_Queue.csv", root);
}

// Function returning a book
void return_Book(memberNode* member) {
    char book_id[20];
    int book_found = 0;

    // Check if the member has information
    if (member == NULL) {
        ClearScreen();
        printf(" !!! Warning : Invalid member.\n");
        Line(); Delay();
        return;
    }

    // Check if the member has borrowed books
    if (member->borrowList == NULL) {
        Line2();
        printf(" Member [%s] has no books borrowed.\n", member->data.ID);
        Line2();
        return;
    }
    DisplayBorrowing(member);

    // Input Book ID 
    printf(" Enter the ID of the book you want to return: ");
    scanf(" %[^\n]", book_id);

    // Check if the book is in the member's borrowed list
    BookBorrowing* borrowedBook = member->borrowList;
    while (borrowedBook != NULL) {
        if (strcmp(borrowedBook->Book_ID, book_id) == 0) {
            book_found = 1;
            break;
        }
        borrowedBook = borrowedBook->next;
    }

    if (!book_found) {
        ClearScreen();
        printf(" !!! Error: Book with ID [%s] is not in your borrowing list.\n", book_id);
        Line(); Delay();
        return;
    }

    // Search for the book in the library
    booksNode* temp = NULL;
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* current = Library[i][j].head;
            // Check if the book ID matches
            while (current != NULL) {
                if (strcmp(current->data.id, book_id) == 0) {
                    temp = current;
                    break;
                }
                current = current->next;
            }
            if (temp != NULL) break;
        }
        if (temp != NULL) break;
    }

    if (temp == NULL) {
        ClearScreen();
        printf(" !!! Error: Book not found in the library.\n");
        Line(); Delay();
        return;
    }

    // Confirm the return of the book
    char Confirm;
    do {
        printf(" Do you want to return this book (Y/N): ");
        scanf(" %c", &Confirm);
    } while (Confirm != 'Y' && Confirm != 'y' && Confirm != 'N' && Confirm != 'n');

    // User confirmation to return the book
    if (Confirm == 'Y' || Confirm == 'y') {
        temp->data.quantity++;
        temp->data.borrowCount++;
        if (temp->data.quantity > 0) {
            temp->data.available = 1;
        }
        changingStatusToReturn(member->data.ID, temp->data.id);
        DeleteBorrowedBook(member, temp->data.id);
        updateBorrowCount(temp->data.id);

        ClearScreen();
        printf(" You have successfully returned the book: %s (ID: %s)\n", temp->data.title, temp->data.id);
        Line();
    } else if (Confirm == 'N' || Confirm == 'n') {
        ClearScreen();
        printf(" Returning cancelled.\n");
        Line();
    }
}

// Function to display all members who are borrowing books
void displayBorrowingMemberTree(memberNode *node) {
    if (!node) return;

    // Traverse the left subtree
    displayBorrowingMemberTree(node->left);

    // Display only members who are borrowing books
    if (node->borrowList != NULL) {
        printf(" Member ID: [%s] | Name: [%s %s]\n", node->data.ID, node->data.FirstName, node->data.LastName);
        Line3(115);
        // point to the borrowed books list
        BookBorrowing* temp = node->borrowList;
        while (temp != NULL) {
            printf("\t- Book-ID: %-17s  Title: %-80s\n", temp->Book_ID, temp->Title);
            temp = temp->next;
        }
        printf("\n");
        Line4(115); 
    }

    // Traverse the right subtree
    displayBorrowingMemberTree(node->right);
}

// Function to display all borrowing members and their borrowed books
void Display_All_Borrowing(memberNode* root) {
    if (root == NULL) {
        printf(" !!! No borrowing history available.\n");
        return;
    }

    Line4(115);
    printf("%81s\n","All Borrowing Members and Their Borrowed Books");
    Line4(115);

    // Call the recursive function to display the borrowing tree
    displayBorrowingMemberTree(root);
    Exit();
}

// Function to display all borrowing queues for all books
void Display_All_Borrowing_Queue_AllBooks() {
    int bookCount = 0; // Counter for books with borrowing queues
    Line4(100);
    printf("%64s\n", "Borrowing Queue for All Books");
    Line4(100);

    // Iterate through all categories and years
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;
            while (temp != NULL) {
                if (temp->data.reservationQueue != NULL && temp->data.reservationQueue->front != NULL) {
                    bookCount++;
                    // Display book information
                    printf(" Book ID: [%s] | Title: %s\n", temp->data.id, temp->data.title);
                    Line3(100);
                    printf(" %-10s | %-20s | %-30s\n", "Position", "User ID", "Member Name");
                    Line3(100);

                    // Display the reservation queue
                    QueueNode* queueTemp = temp->data.reservationQueue->front;
                    int position = 1;
                    while (queueTemp != NULL) {
                        // Search for the member by ID
                        memberNode* member = searchMember(root, queueTemp->User_ID);
                        char memberName[50] = "Unknown"; // Default name if not found
                        if (member != NULL) {
                            snprintf(memberName, sizeof(memberName), "%s %s", member->data.FirstName, member->data.LastName);
                        }

                        // Display the queue information
                        printf(" %-10d | %-20s | %-30s\n", position, queueTemp->User_ID, memberName);
                        queueTemp = queueTemp->next;
                        position++;
                    }
                    Line4(100);
                }
                temp = temp->next;
            }
        }
    }

    if (bookCount == 0) {
        printf(" No books have a borrowing queue.\n");
    }
    Line4(100);
    Exit();
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