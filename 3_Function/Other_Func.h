#ifndef OTHER_FUNC_H
#define OTHER_FUNC_H

#define MAX_BOOKS 1000
#define MAX_MEMBERS 1000
#define MAX_LINE 256
#define MAX_ID 20
#define MAX_NAME 50  
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

void Download();


int Check_Num(const char* str);
int Check_User_ID(const char* str);

//Display Top 5 Borrowed Books
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
void displayTop5BorrowedBooks();

//Show Top 3 Members With Returns
typedef struct {
    char MEMBER_ID[20];
    int RETURNED;
} MemberBorrowInfo;

typedef struct {
    char MEMBER_ID[20];
    char FirstName[MAX_NAME];
    char LastName[MAX_NAME];
} MemberInfo;

int loadMembers(const char *fileName, MemberInfo members[], int maxMembers);
void showTop3MembersWithMostReturns(const char *borrowFile, const char *memberFile);

#endif