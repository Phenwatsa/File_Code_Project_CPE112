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
void ClearScreen(){
    system("clear");
}
void Delay(){
    sleep(2);
}

int check_Num(const char* str){
    if (strlen(str) == 1 && str[0] >= '1' && str[0] <= '9') {
        return str[0] - '0'; 
    } else {
        return 0; 
    }
}