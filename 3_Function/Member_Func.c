//[Pi]

#include<stdio.h>
#include<string.h>
#include "Member_Func.h"

void registerMember(Member members[], int *count)
{
    if (*count >= MAX_MEMBERS)
    {
        printf("Cannot register more members.\n"); //ลงไว้ก่อนว่าเอามากสุดร้อยนึงก่อนนน แต่อาจได้แก้ๆๆๆๆ
        return;
    }
    
    printf("Enter Member ID: ");
    scanf("%s", members[*count].ID);
    printf("Enter Fisrt Name: ");
    scanf("%s", members[*count].FirstName);
    printf("Enter Last Name: ");
    scanf("%s", members[*count].LastName);
    printf("Enter Phone Number: ");
    scanf("%s", members[*count].Phone);
    printf("Enter Email: ");
    scanf("%s", members[*count].email);

    FILE *fp = fopen("member.csv", "a");
    if (fp)
    {
        fprintf(fp,"%s,%s,%s,%s,%s\n", members[*count].ID, members[*count].FirstName, members[*count].LastName, members[*count].Phone, members[*count].email);
        fclose(fp);
        printf("Member registered.\n");
        (*count)++;

    }else 
    {
        printf("Cannot open file.\n");
    }
    

}


void updateMember(Member members[], int count) //ตรงนี้ว่าควรแก้เพราะยังดีไม่พอ เออควรแหละ อันนี้ไม่เหมาะกับระบบใหญ่นะ 
{
    char search_ID[10];
    printf("Enter Member ID to update: ");
    scanf("%s", search_ID);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(members[i].ID, search_ID)==0)
        {
            printf("Editing member: %s %s\n",members[i].FirstName,members[i].LastName);
            printf("Enter new first name: ");
            scanf("%s", members[i].FirstName);
            printf("Enter new last name: ");
            scanf("%s", members[i].LastName);
            printf("Enter new phone number: ");
            scanf("%s", members[i].Phone);
            printf("Enter new email: ");
            scanf("%s", members[i].email);
            saveAllMemberToFile(members, count); //บันทึกข้อมูลทุกคนเลย จะแก้ไหม แต่นี่คิดว่าบันทึกทุกคนไปเลยก็ได้มั้ง เผื่อไว้ หรือต้องแก้
            printf("Member updated.\n");
            return;

        }
    }
    printf("Member with ID %s not found.\n", search_ID);
}

void saveAllMemberToFile(Member members[], int count)
{
    FILE *fp = fopen("member.csv", "w");
    if (fp)
    {
        for (int i = 0; i < count; i++)
        {
            fprintf(fp, "%s,%s,%s,%s,%s\n",members[i].ID, members[i].FirstName, members[i].LastName, members[i].Phone, members[i].email);
        }
        fclose(fp);
        
    } else
    {
        printf("Error saving to file.\n");
    }
    
    

}

void checkBorrowingHistory(const char *memberId)
{
    FILE *fp = fopen("borrow_history.csv", "r"); //อย่าลืมสร้างไฟล์ยืมมมเปล่าๆด้วยนาจร้ะ
    if (!fp)
    {
        printf("Cannot open borrow_history.csv\n");
        return;
    }
    
    char perLine[256];
    int found = 0;
    printf("Borrow History for Member ID:  %s \n", memberId);
    while (fgets(perLine, sizeof(perLine), fp))
    {
        char CurrentMemberID[20], Book_ID[20], Title[200], BorrowDate[15], ReturnDate[15];
        int Read = sscanf(perLine, "%[^,],%[^,],%[^,],%[^,],%[^\n]",CurrentMemberID,Book_ID,Title,BorrowDate,ReturnDate);
        if (Read != 5)
        {
            printf("Invalid data format in line: %s", perLine); // ui เข้าได้
            continue;
        }
        
        if (strcmp(CurrentMemberID, memberId)==0)
        {
        
            if (strlen(Title)==0)
            {
                strcpy(Title, "UNKNOW");
            }

            if (strlen(ReturnDate)==0)
            {
                strcpy(ReturnDate,"-");
            }
            
            printf("%s %s Borrowed: %s  Returned: %s\n",Book_ID,Title,BorrowDate,ReturnDate); // แก้ ui ตรงนี้ดั้ย
            found = 1;
        }
    }
    
    if (!found)
    {
        printf("No borrowing history found.\n");
    }
    fclose(fp);

}


void loadMemberBefore(Member members[], int *count)
{
    FILE *fp = fopen("member.csv", "r");
    if (!fp)
    {
        return;
    }

    char perLine[200];
    while (fgets(perLine, sizeof(perLine), fp) && *count < MAX_MEMBERS)
    { 
        sscanf(perLine, "%[^,],%[^,],%[^,],%[^,],%[^\n]",members[*count].ID, members[*count].FirstName,members[*count].LastName,members[*count].Phone,members[*count].email);
        (*count)++;
    }
    fclose(fp);
    
}
