#ifndef MEMBER_H
#define MEMBER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Other_Func.h"
#define MAX_ID 10
#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_EMAIL 50

#define MAX_LINE 256
#define MAX_TITLE 256

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

extern memberNode* root;

memberNode *insertMember(memberNode *root, Member data);
memberNode *searchMember(memberNode *root, const char *id);
int saveMemberTree(memberNode *node, FILE *fp);
void displayMember(memberNode *node);
void inputMemberData(Member *info);
void whitespace(char *message);
void updateMember(memberNode *root);
int saveMember(memberNode *root, const char *fileName);
void checkBorrowingHistory(const char *memberId);
void loadMember(memberNode **root, const char *fileName);
void displayMemberTree(memberNode *node);
void freeMemberTree(memberNode *root);
void flushInputBuffer();
void debugMemberTree(memberNode* node);
#endif