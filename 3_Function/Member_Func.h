#ifndef MEMBER_H
#define MEMBER_H
<<<<<<< HEAD
#include<stdio.h>
#include<string.h>
#define MAX_MEMBERS 100
#define MAX_LEN_ID 10
#define MAX_LEN_FN 50
#define MAX_LEN_LN 50
=======

#define MAX_ID 10
#define MAX_NAME 20
#define MAX_PHONE 15
#define MAX_EMAIL 50
>>>>>>> d80f37263999ff9f76010afcf268c9ab8d36e9dd

typedef struct 
{
    char ID[MAX_ID];
    char FirstName[MAX_NAME];
    char LastName[MAX_NAME];
    char Phone[MAX_PHONE];
    char Email[MAX_EMAIL];
} Member;

typedef struct memberNode
{
    Member data;
    struct memberNode *left;
    struct memberNode *right;
} memberNode;

memberNode *insertMember(memberNode *root, Member data);
memberNode *searchMember(memberNode *root, const char *id);
void updateMember(memberNode *root);
void saveMember(memberNode *root, FILE* fp);
void loadMember(memberNode **root);
void displayMember(memberNode *root);
void freeMemberTree(memberNode *root);

#endif