#ifndef MEMBER_H
#define MEMBER_H

#define MAX_ID 10
#define MAX_NAME 20
#define MAX_PHONE 15
#define MAX_EMAIL 50

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
void loadMember(memberNode **root, const char *fileName);
void displayMember(memberNode *root);
void freeMemberTree(memberNode *root);

#endif