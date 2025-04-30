// (boook recommendation)[Pi]
// (top borrowed books)[Pi]
// Other additional functions [ploy]

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Other_Func.h"

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
    sleep(1);
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
    if (strlen(str) == 8 && str[0] >= '1' && str[0] <= '9') {
        return 1; 
    } else {
        return 0; 
    }
}

