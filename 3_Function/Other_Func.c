// (boook recommendation)[Pi]
// (top borrowed books)[Pi]
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
    sleep(3);
}

void Exit(){
    char Enter_Exit[1];
    do{
        printf(" Enter [E] to Exit : ");
        scanf(" %s", Enter_Exit);
    }while (Enter_Exit[0] != 'E' && Enter_Exit[0] != 'e');
    ClearScreen();
}

int Check_Num(const char* str){
    if (strlen(str) == 1 && str[0] >= '1' && str[0] <= '9') {
        return str[0] - '0'; 
    } else {
        return 0; 
    }
}

int Check_User_ID(const char* str){
    memberNode *target = searchMember(root, str);
    if (!target){
        ClearScreen();
        printf(" Member with ID [%s] not found.\n", str);
        Line();
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
        printf("Cannot open file"); ////////ui
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

void displayTop5BorrowedBooks(Book books[], int count)
{

    qsort(books,count,sizeof(Book),compareByBorrowed);
    printf("Top 5 Most Borrowed Books\n");
    printf("%-20s %-90s %-20s\n", "Borrowed", "Title", "Book ID"); ////////ีรรรuiiiii

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
        printf("%-20d %-90s %-20s\n",books[i].BORROWED,books[i].TITLE,books[i].ID); //////ีรรรร  uiiiii

    }
    

}