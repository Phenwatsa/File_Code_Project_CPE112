// (top 5 borrowed books)[Phi]
// (Top 3 Members With Returns)[Phi]
// Other additional functions [ploy]

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Other_Func.h"
#include "Member_Func.h"

//UI design format
void Line(){
    printf("--------------------------------------------------\n");
}
void Line2(){
    printf("==================================================\n");
}
void Line3(int num){
    for (int i = 0; i < num; i++){
        printf("-");
    }
    printf("\n");
}
void Line4(int num){
    for (int i = 0; i < num; i++){
        printf("=");
    }
    printf("\n");
}
void ClearScreen(){
    system("clear");
}
void Delay(){
    sleep(1);
}
void Exit(){
    char Enter_Exit;
    do{
        printf(" Enter [E] to Exit : ");
        scanf(" %c", &Enter_Exit);
    }while (Enter_Exit != 'E' && Enter_Exit != 'e');
    ClearScreen();
}

// Download function
void Download(){
    InitializeLibrary();
    csvToStruct();
    loadMember(&root, "DATA/member.csv");
    booksNode* bookRoot = Library[0][0].head;
    LoadBorrowHistory("DATA/borrow_history.csv", root);
    LoadBorrowQueue("DATA/Borrowing_Queue.csv", root, bookRoot);
}

// Check if the input is a number between 1 and 9
int Check_Num(const char* str){
    if (strlen(str) == 1 && str[0] >= '1' && str[0] <= '9') {
        return str[0] - '0'; 
    } else {
        return 0; 
    }
}
// Check if the input is a valid member ID
int Check_User_ID(const char* str){
    memberNode *target = searchMember(root, str);
    if (!target){
        ClearScreen();
        printf(" Member with ID [%s] not found.\n", str);
        Line(); Delay();
        return 0 ;
    }
    return 1;
}

//Display top 5 borrowed books
int loadBooksFromCSV(const char *fileName, Book books[])
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        ClearScreen();
        perror("Error opening file"); 
        printf("Tried to open: %s\n", fileName);
        Line(); Delay();
        return 0;
    }
    
    char line[MAX_LINE];
    int count = 0;
    fgets(line, sizeof(line), fp );
    while (fgets(line, sizeof(line), fp ) != NULL && count < MAX_BOOKS)
    {
        char *comma_firstposi = strchr(line, ',');
        if (comma_firstposi == NULL) continue;

        int len_id = comma_firstposi - line;
        if (len_id >= MAX_ID)
        {
           len_id = MAX_ID-1;
        }
        
        strncpy(books[count].ID, line,len_id);
        books[count].ID[len_id] = '\0';
        
        sscanf(comma_firstposi + 1, "%[^,],%*[^,],%*[^,],%*d,%*d,%*[^,],%d",books[count].TITLE,&books[count].BORROWED);
        count++;  
    }

    fclose(fp);
    return count;
}

int compareByBorrowed(const void *a, const void *b) {
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    return bookB->BORROWED - bookA->BORROWED; 
}

void displayTop5BorrowedBooks()
{
    Book books[MAX_BOOKS];
    const char *fileName = "DATA/Book-ID.csv";
    int count = loadBooksFromCSV(fileName, books);

    qsort(books,count,sizeof(Book),compareByBorrowed);
    Line4(115);
    printf("%70s\n","Top 5 Most Borrowed Books");
    Line4(115);
    printf(" %-10s | %-80s | %-20s\n", "Borrowed", "Title", "Book ID");
    Line3(115);

    int top5;
    if (count < 5)
    {
        top5 = count;
    }else
    {
        top5 = 5;
    }
    
    for (int i = 0; i < top5; i++)
    {
        printf(" %-10d | %-80s | %-20s\n",books[i].BORROWED,books[i].TITLE,books[i].ID); 

    }
    Line4(115);
    Exit();
}

//Show Top 3 Members With Returns
int compareByReturnCount(const void *a, const void *b) 
{
    MemberBorrowInfo *memA = (MemberBorrowInfo *)a;
    MemberBorrowInfo *memB = (MemberBorrowInfo *)b;
    return memB->RETURNED - memA->RETURNED;
}

int loadMembers(const char *fileName, MemberInfo members[], int maxMembers) 
{
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        ClearScreen();
        printf("Error opening member file.\n");
        Line(); Delay();
        return 0;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), fp);
    int count = 0;

    while (fgets(line, sizeof(line), fp) && count < maxMembers) 
    {
        sscanf(line, "%[^,],%[^,],%[^,]", members[count].MEMBER_ID,members[count].FirstName, members[count].LastName);
        count++;
    }
    fclose(fp);
    return count;
}

void showTop3MembersWithMostReturns(const char *borrowFile, const char *memberFile) {
    FILE *fp = fopen(borrowFile, "r");
    if (!fp) 
    {
        ClearScreen();
        printf("Error opening borrow file.\n");
        Line(); Delay();
        return;
    }

    MemberInfo member_list[MAX_MEMBERS];
    int total_members = loadMembers(memberFile, member_list, MAX_MEMBERS);
    MemberBorrowInfo borrow_info[MAX_MEMBERS];
    int borrow_count = 0;
    char line[MAX_LINE];
    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp)) 
    {
        char member_id[MAX_ID], book_id[MAX_ID], title[MAX_TITLE], status[MAX_STATUS];
        sscanf(line, "%[^,],%[^,],%[^,],%s", member_id, book_id, title, status);
        if (strcmp(status, "Returned") == 0) 
        {
            int found = 0;
            for (int i = 0; i < borrow_count; i++) 
            {
                if (strcmp(borrow_info[i].MEMBER_ID, member_id) == 0) 
                {
                    borrow_info[i].RETURNED++;
                    found = 1;
                    break;
                }
            }
            if (!found && borrow_count < MAX_MEMBERS) 
            {
                strcpy(borrow_info[borrow_count].MEMBER_ID, member_id);
                borrow_info[borrow_count].RETURNED = 1;
                borrow_count++;
            }
        }
    }

    fclose(fp);

    qsort(borrow_info, borrow_count, sizeof(MemberBorrowInfo), compareByReturnCount);
    Line4(75);
    printf("%55s\n","Top 3 members with most borred books");
    Line3(75);
    for (int i = 0; i < 3 && i < borrow_count; i++) 
    {
        char *first = "Unknown";
        char *last = "Unknow";
        for (int j = 0; j < total_members; j++) 
        {
            if (strcmp(borrow_info[i].MEMBER_ID, member_list[j].MEMBER_ID) == 0) 
            {
                first = member_list[j].FirstName;
                last = member_list[j].LastName;
                break;
            }
        }
        printf(" [%d] %-10s | %-15s %-15s (%-2d books returned)\n",i + 1, borrow_info[i].MEMBER_ID,first,last,borrow_info[i].RETURNED); 
    }
    Line4(75);
    Exit();
}
