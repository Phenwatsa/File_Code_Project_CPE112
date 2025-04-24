#ifndef MEMBER_H
#define MEMBER_H
#define MAX_MEMBERS 100
#define MAX_LEN_ID 10
#define MAX_LEN_FN 20
#define MAX_LEN_LN 20

typedef struct 
{
    char ID[MAX_LEN_ID];
    char FirstName[MAX_LEN_FN];
    char LastName[MAX_LEN_LN];
    char Phone[15];
    char email[50];
} Member;

void registerMember(Member members[], int *count);
void updateMember(Member members[], int count);
void checkBorrowingHistory(const char *memberId);
void saveAllMemberToFile(Member members[],int count);


#endif