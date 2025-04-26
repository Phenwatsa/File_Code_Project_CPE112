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
    if (root == NULL || strcmp(root->data.ID, id) = 0)
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


void updateMember(memberNode *root) 
{
    char search_ID[10];
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

void loadMember(memberNode **root, const char *fileName)
{
    FILE *fp = fopen(fileName, "r");
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

