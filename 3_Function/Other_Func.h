#ifndef OTHER_FUNC_H
#define OTHER_FUNC_H

#define MAX_BOOKS 1000
#define MAX_LINE 256
#define MAX_ID 15  
#define MAX_TITLE 200    
#define MAX_AUTHER 100    
#define MAX_CATEGORY 100 
#define MAX_STATUS 20

// UI design format
void Line();
void Line2();
void Line3(int num);
void Line4(int num);
void ClearScreen();
void Delay();
void Exit();



typedef struct {
    char ID[MAX_ID];
    char TITLE[MAX_TITLE];
    char AUTHOR[MAX_AUTHER];
    char CATEGORY[MAX_CATEGORY];
    int YEAR;
    int QUANTITY;
    char STATUS[MAX_STATUS];
    int BORROWED;
} Book;

int loadBooksFromCSV(const char *fileName, Book books[]);
void displayTop5BorrowedBooks(Book books[], int count);

int Check_Num(const char* str);
int Check_User_ID(const char* str);

#endif