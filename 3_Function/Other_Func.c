#include "Data_Func.h"
#include "Other_Func.h"


int searchBook() {

    printf("-- Welcome to search function --\n");

    printf(" -- Search by id or Name of the book :");

    // read the string data 
    char UserFil[max_char];
    scanf("%s", UserFil);

    // for user to enter the category filter
    printf("Using filter for category\n");
    int cateFil = filterCategory(categoryNames, numCategory);   


    // for user to enter the year filter
    printf("Using filter for year\n");
    int yearFil = filterCategory(yearNames, numYear);

    printf("-- List of book below -- \n");
    
    // number of book that have been showed
    int numBooksShow = 0;

    // does not use the category filter and year filter
    if (cateFil == 0 && yearFil == 0) {
        for (int i = 0; i < numCategory; i++) {
            for (int j = 0; j < numYear; j++) {
                numBooksShow = checkDataEachList(Library[i][j], UserFil);
            }
        }
    }

    // using category filter only
    else if (cateFil != 0 && yearFil == 0) {
        for (int j = 0; j < numYear; j++) {
            numBooksShow = checkDataEachList(Library[cateFil][j], UserFil);
        }
    }

    // using year filter only
    else if (cateFil == 0 && yearFil != 0) {
        for (int i = 0; i < numCategory; i++) {
            numBooksShow = checkDataEachList(Library[i][yearFil], UserFil);
        }
    }

    // using both year and category filter
    else {
        numBooksShow = checkDataEachList(Library[cateFil][yearFil], UserFil);
    }

    printf("Number of book found is : %d", numBooksShow);
    
}

int filterUsable(char filter[], int number_filter) {
    // if input number is not a digit 
    if (isNotInteger(filter) == 1) {
        printf(" We aren't accept other type of data except integer");
        return -1;
    }

    // if input number is over the range of number of the category
    // atoi use to transform string -> int like '30' -> 30
    if (atoi(filter) > number_filter || atoi(filter) < 0) {
        printf(" The integer is out of our range of category");
        return -1;
    }

    // return the int value
    return atoi(filter);
}



// function to show all the books
void showAllBooks() {
    for (int i = 0; i < numCategory; i++) {

        printf("Category of the book : %s\n", categoryNames[i]);
        for (int j = 0; j < numYear; j++) {
            
            // print if found the the book in that year range
            if (Library[i][j].head != NULL) 
            printf("Publish year of the book : %s\n", yearNames[j]);

            // loop and show the book data
            showBookList(Library[i][j].head);

        }
    }
}


// Function for user to describe how to use filter in search function
int filterCategory(char listName[][max_char], int number_list) {
    
    char cateFil[2];
    
    // show all filter that possible to use
    for (int i = 0; i < number_list; i++) {
        printf("-- Enter %d to use %s --\n", i+1, listName[i]);
    }

    printf("-- Enter 0 to not use the filter\n");

    int cateFilIndex;

    do {
        printf(" Enter it here : ");
        scanf("%s", cateFil);

        // value will be transform from string to int but if it return -1 means invalid
        cateFilIndex = filterUsable(cateFil, number_list);
    }

    while (cateFilIndex == -1);
    
    return cateFilIndex-1;
}

// Loop the linklist
void showBookList(booksNode* temp) {
    
    while (temp != NULL) {
        
        showBookData(temp);
        temp = temp->next;
    }
}


void showBookData(booksNode* temp) {
    printf(" ---- BOOKS ----\n");
    printf(" ID : %s\n", temp->data.id);
    printf(" title : %s\n", temp->data.title);
    printf(" category : %s\n", temp->data.category);
    printf(" year : %d\n", temp->data.year);
    printf(" quantity : %d\n", temp->data.quantity);
    printf(" available : %d\n", temp->data.available);
    printf(" ------------ \n");
}



int checkDataEachList(booksListInfo linkList, char userInput[]) {
    
    booksNode* temp = linkList.head;

    int numBooks = 0;

    while (temp != NULL) {

        if (strstr(temp->data.author, userInput) != NULL) {
            showBookList(temp);
            numBooks += 1;
        }
    
        else if (strstr(temp->data.id, userInput) != NULL) {
            showBookList(temp);
            numBooks += 1;
        }

        temp = temp->next;

    }

    return numBooks;
}



int isNotInteger(const char* str) {
    // Check for empty string
    if (str == NULL || *str == '\0') {
        return 1; // Not an integer
    }

    // Check each character
    while (*str) {
        if (!isdigit(*str)) {
            return 1; // Not an integer
        }
        str++;}
    return 0;

}
