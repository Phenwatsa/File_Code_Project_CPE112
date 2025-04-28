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

int saveMemberTree(memberNode *node, FILE *fp);
void displayMember(memberNode *node);
void inputMemberData(Member *info);

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
    printf("Enter ID:  "); // /////////////////// ui เข้าสปอนที้
    fgets(info->ID, MAX_ID, stdin); 
    whitespace(info->ID);

    printf("Enter First Name:  "); // /////////////////// ui เข้าสปอนที้
    fgets(info->FirstName, MAX_NAME, stdin); 
    whitespace(info->FirstName);

    printf("Enter Last Name:  "); // /////////////////// ui เข้าสปอนที้
    fgets(info->LastName, MAX_NAME, stdin); 
    whitespace(info->LastName);

    printf("Enter Phone Number:  "); // /////////////////// ui เข้าสปอนที้
    fgets(info->Phone, MAX_PHONE, stdin); 
    whitespace(info->Phone);

    printf("Enter Email:  "); // /////////////////// ui เข้าสปอนที้
    fgets(info->Email, MAX_EMAIL, stdin); 
    whitespace(info->Email);
}



void updateMember(memberNode *root) 
{
    if (!root)
    {
        printf("Member database is empty.\n");
        return;
    }
    
    char search_ID[MAX_ID];
    printf("Enter Member ID to update: ");
    fgets(search_ID, MAX_ID, stdin);
    whitespace(search_ID);

    memberNode *target = searchMember(root, search_ID);
    if (!target)
    {
        printf("Member with ID %s not found.\n", search_ID); ///////// ui
        return;

    }


    printf("Editing member: %s %s\n", target->data.FirstName, target->data.LastName);
    Member update_d =  target->data;
    inputMemberData(&update_d);

    target->data = update_d;

    if (saveMember(root, "member.csv") == 0)
    {
        printf("Member updated successfully.\n");
    }else
    {
        printf("Error saving changes.\n");  /////ui
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
        perror("Error opening file for writing"); 
        return -1; 
    }
    
    fprintf(fp, "ID,FirstName,LastName,Phone,Email\n");
    int result = saveMemberTree(root, fp);
    fclose(fp);
    return result;
}



void checkBorrowingHistory(const char *memberId)
{
    FILE *fp = fopen("borrow_history.csv", "r"); 
    if (!fp)
    {
        printf("Cannot open borrow history file"); ////////////ui  ui ui
        return;
    }
    
    char line[MAX_LINE];
    int found = 0;

    fgets(line, sizeof(line), fp);
    printf("Borrow History for Member ID:  %s\n", memberId); //////////////// ui
    printf("%-10s %-256s %-15s\n", "Book ID", "Title", "Status"); //////////////// ui

    while (fgets(line, sizeof(line), fp))
    {
        char CurrentMemberID[MAX_ID], Book_ID[20], Title[MAX_TITLE], Status[10];

        if (sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", CurrentMemberID, Book_ID, Title, Status) == 4)
        {
            if (strcmp(CurrentMemberID, memberId) != 0) continue;

            printf("%-10s %-256s %-15s\n" , "Book_ID", "Title", "Status");
            found = 1;
            
        }
    }
    
    if (!found)
    {
        printf("No borrowing history found.\n"); ///////////////  ui      ui
    }
    fclose(fp);

}


void loadMember(memberNode **root, const char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (!fp)
    {
        perror("Error opening member file");
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp))
    {
        whitespace(line);
        if (strlen(line)==0) continue;
        Member info = {0};

        
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]",info.ID,info.FirstName,info.LastName,info.Phone,info.Email) == 5)
        {
            *root = insertMember(*root, info);
        }else{
            fprintf(stderr, "Invalid data format:  %s\n", line); //////////ui
        }
    }
    fclose(fp);
    
}

void displayMemberTree(memberNode *node)
{
    if (!node) return;
    displayMemberTree(node->left);
    printf("%-10s %-20s %-20s %-15s %-50s\n", node->data.ID, node->data.FirstName, node->data.LastName, node->data.Phone, node->data.Email);
    displayMemberTree(node->right);
}

void displayMember(memberNode *root)
{
    if (!root)
    {
        printf("No members to display.\n");
        return;
    }

    printf("\n%-10s %-20s %-20s %-15s %-50s\n", "ID", "First Name", "Last Name", "Phone Number", "Email" );  /////////////////////////ีรร สปอนเข้าทีจ้า ui
    displayMemberTree(root);
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


/*
int main() {
    memberNode* root = NULL;
    const char* filename = "member.csv";

    loadMember(&root, filename);

    int choice;
    do {
        printf("\n=== Member Management ===\n");
        printf("1. Add Member\n");
        printf("2. Update Member\n");
        printf("3. Display All Members\n");
        printf("4. Check Borrowing History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice) {
            case 1: {
                Member newMember;
                inputMemberData(&newMember);
                root = insertMember(root, newMember);
                saveMember(root, filename);
                printf("Member added successfully.\n");
                break;
            }
            case 2:
                updateMember(root);
                break;
            case 3:
                displayMember(root);
                break;
            case 4: {
                char memberId[MAX_ID];
                printf("Enter Member ID to check history: ");
                fgets(memberId, MAX_ID, stdin);
                whitespace(memberId);
                checkBorrowingHistory(memberId);
                break;
            }
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    freeMemberTree(root);
    return 0;
}
    

*/