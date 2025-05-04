//[Pi]

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Member_Func.h"

memberNode* root = NULL;
const char* filename = "DATA/member.csv";

// Insert a new member into the binary search tree
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

// Search for a member by ID in the binary search tree
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
    return NULL;
}

int saveMemberTree(memberNode *node, FILE *fp);
void displayMember(memberNode *node);
void inputMemberData(Member *info);

// Function to remove trailing whitespace from a string
void whitespace(char *message)
{
    int i = strlen(message) - 1;
    while (i >= 0 && (message[i] == ' ' || message[i] == '\t' || message[i] == '\n'))
    {
        message[i--] = '\0';
    }
}

void inputMemberData(Member *info)
{
    Line2();
    printf(" Enter ID : ");
    fgets(info->ID, MAX_ID, stdin); 
    whitespace(info->ID);

    printf(" Enter First Name : ");
    fgets(info->FirstName, MAX_NAME, stdin); 
    whitespace(info->FirstName);

    printf(" Enter Last Name : ");
    fgets(info->LastName, MAX_NAME, stdin); 
    whitespace(info->LastName);

    printf(" Enter Phone Number : ");
    fgets(info->Phone, MAX_PHONE, stdin); 
    whitespace(info->Phone);

    printf(" Enter Email : ");
    fgets(info->Email, MAX_EMAIL, stdin); 
    whitespace(info->Email);
}

void updateMember(memberNode *root) 
{
    if (!root)
    {
        ClearScreen();
        printf(" !!! Member database is empty.\n");
        Line(); Delay();
        return;
    }
    
    char search_ID[MAX_ID];
    getchar();
    Line2();
    printf(" Enter Member ID to update : ");
    fgets(search_ID, MAX_ID, stdin);
    whitespace(search_ID);

    memberNode *target = searchMember(root, search_ID);
    if (!target)
    {
        ClearScreen();
        printf(" !!! Member with ID [%s] not found.\n", search_ID);
        Line(); Exit();
        return;

    }


    printf(" Editing member : %s %s\n", target->data.FirstName, target->data.LastName);
    Member update_d =  target->data;
    inputMemberData(&update_d);

    target->data = update_d;

    if (saveMember(root, "member.csv") == 0)
    {
        Line2();
        printf(" Member updated successfully.\n");
        Line2(); Exit();
        return;
    }else
    {
        ClearScreen();
        printf(" !!! Error saving changes.\n");
        Line(); Exit();
        return;
    }
}

int saveMemberTree(memberNode *node, FILE *fp)
{
    if (!node) return 0;

    saveMemberTree(node->left, fp);
    if (fprintf(fp, "%s,%s,%s,%s,%s\n", node->data.ID, node->data.FirstName, node->data.LastName, node->data.Phone, node->data.Email) < 0)
    {
        return -1;
    }
    saveMemberTree(node->right, fp);
    return 0;
}

int saveMember(memberNode *root, const char *fileName) 
{
    if (!root) return 0;
    FILE *fp = fopen(fileName, "w");
    if (!fp)
    {
        ClearScreen();
        perror(" !!! Error opening file for writing."); 
        Line(); Delay();
        return -1; 
    }
    
    fprintf(fp, "ID,FirstName,LastName,Phone,Email\n");
    int result = saveMemberTree(root, fp);
    fclose(fp);
    return result;
}

void checkBorrowingHistory(const char *memberId)
{
    FILE *fp = fopen("DATA/borrow_history.csv", "r"); 
    if (!fp)
    {
        ClearScreen();
        printf(" !!! Cannot open borrow history file");
        Line(); Delay();
        return;
    }
    
    char line[MAX_LINE];
    int found = 0;

    fgets(line, sizeof(line), fp);
    printf(" Borrow History for Member ID : %s\n", memberId);
    Line3(115);
    printf(" %-18s | %-80s | %-5s\n", "Book-ID", "Title", "Status");
    Line3(115);

    while (fgets(line, sizeof(line), fp))
    {
        char CurrentMemberID[MAX_ID], Book_ID[20], Title[MAX_TITLE], Status[10];

        if (sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", CurrentMemberID, Book_ID, Title, Status) == 4)
        {
            if (strcmp(CurrentMemberID, memberId) != 0) continue;
            printf(" %-18s | %-80s | %-5s\n" , Book_ID, Title, Status);
            found = 1;
            
        }
    }
    
    if (!found)
    {
        ClearScreen();
        printf(" No borrowing history found.\n"); 
        Line(); Delay();
    }
    fclose(fp);
    Line4(115); Exit();
}

void loadMember(memberNode **root, const char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        ClearScreen();
        perror(" !!! Error opening member file");
        Line(); Delay();
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp))
    {
        whitespace(line);
        if (strlen(line)==0) continue;
        Member info = {0};

        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]", 
            info.ID, info.FirstName, info.LastName, info.Phone, info.Email) == 5)
        {
            *root = insertMember(*root, info);
        }else{
            fprintf(stderr, "Invalid data format:  %s\n", line);
        }
    }
    fclose(fp);
}

void displayMemberTree(memberNode *node)
{
    if (!node) return;
    displayMemberTree(node->left);
    printf(" %-15s | %-20s | %-20s | %-15s | %-10s\n", node->data.ID, node->data.FirstName, node->data.LastName, node->data.Phone, node->data.Email); ///////////// ui
    displayMemberTree(node->right);
    
}

void displayMember(memberNode *root)
{
    if (!root)
    {
        ClearScreen();
        printf(" No members to display.\n");
        Line(); Delay();
        return;
    }
    ClearScreen(); Line4(115);
    printf("%65s\n","List of Members");
    Line4(115);
    printf(" %-15s | %-20s | %-20s | %-15s | %-50s\n", "ID", "First Name", "Last Name", "Phone Number", "Email" );
    Line3(115);
    displayMemberTree(root);
    Line4(115);
    Exit();
}

void freeMemberTree(memberNode *root)
{
    if (!root) return;
    freeMemberTree(root->left);
    freeMemberTree(root->right);
    free(root);
    
}

void flushInputBuffer()
{
    int cha;
    while (1)
    {
        cha = getchar();
        if (cha == '\n' || cha == EOF)
        {
            break;
        }
        
    }
    
}

void Register_Member(){
    Member newMember;
    getchar();
    inputMemberData(&newMember);
    root = insertMember(root, newMember);
    saveMember(root, filename);
    Line2();
    printf(" Member added successfully.\n");
    Line2();
    Exit();
}

void Check_Borrowing_History(){
    getchar();
    char memberId[MAX_ID];
    Line4(115);
    printf(" Enter Member ID to check history : ");
    fgets(memberId, MAX_ID, stdin);
    Line3(115);
    whitespace(memberId);
    checkBorrowingHistory(memberId);
}