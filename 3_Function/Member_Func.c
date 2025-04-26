//[Pi]

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Member_Func.h"

memberNode *insertMember(memberNode *root, Member data)
{
    if (root == NULL)
    {
        memberNode *newNode = (memberNode *)malloc(sizeof(memberNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;

    }
    if (strcmp(data.ID, root->data.ID) < 0)
    {
        root->left = insertMember(root->left, data);
    }else if (strcmp(data.ID, root->data.ID) > 0)
    {
        root->right = insertMember(root->right, data);
    }
    return root;

}

memberNode *searchMember(memberNode *root, const char *id)
{
    if (root == NULL || strcmp(root->data.ID, id) == 0)
    {
        return root;
    }
    if (strcmp(id, root->data.ID) < 0)
    {
        return searchMember(root->left, id);
    }else
    {
        return searchMember(root->right, id);
    }

}

<<<<<<< HEAD
void updateMember(Member members[], int count) //ตรงนี้ว่าควรแก้เพราะยังดีไม่พอ เออควรแหละ อันนี้ไม่เหมาะกับระบบใหญ่นะ 
=======

void updateMember(memberNode *root) 
>>>>>>> d80f37263999ff9f76010afcf268c9ab8d36e9dd
{
    char search_ID[MAX_ID];
    printf("Enter Member ID to update: ");
    scanf("%s", search_ID);

    memberNode *target = searchMember(root, search_ID);
    if (target)
    {
        printf("Editing member: %s %s\n",target->data.FirstName, target->data.LastName);
        printf("Enter new first name: ");
        scanf("%s", target->data.FirstName);
        printf("Enter new last name: ");
        scanf("%s", target->data.LastName);
        printf("Enter new phone number: ");
        scanf("%s", target->data.Phone);
        printf("Enter new email: ");
        scanf("%s", target->data.Email);
        FILE *fp = fopen("member.csv", "w");
        if (fp)
        {
            saveMember(root, fp);
            fclose(fp);
        }
        
    }else{
        printf("Member with ID %s not found.\n", search_ID);
    }
}

void saveMember(memberNode *root, FILE *fp)
{
    if (!root) return;
    saveMember(root->left, fp);
    fprintf(fp, "%s,%s,%s,%s,%s\n", root->data.ID, root->data.FirstName, root->data.LastName, root->data.Phone, root->data.Email);
    saveMember(root->right, fp);
}

<<<<<<< HEAD
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
=======
void loadMember(memberNode **root)
>>>>>>> d80f37263999ff9f76010afcf268c9ab8d36e9dd
{
    FILE *fp = fopen("member.csv", "r");
    if (!fp) return;
    Member temp;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",temp.ID, temp.FirstName, temp.LastName, temp.Phone, temp.Email) == 5)
    {
        *root = insertMember(*root, temp);
    }
    fclose(fp);
    
}

void displayMember(memberNode *root)
{
    if (!root) return;
    displayMember(root->left);
    printf("ID:  %s  Name:  %s  %s  Phone number:  %s   Email:  %s\n",root->data.ID, root->data.FirstName, root->data.LastName, root->data.Phone, root->data.Email); //ui สปอนเข้าทีค่ะ
    displayMember(root->right);
    
}

void freeMemberTree(memberNode *root)
{
    if (!root) return;
    freeMemberTree(root->left);
    freeMemberTree(root->right);
    free(root);
    
}

