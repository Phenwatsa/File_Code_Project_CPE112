// (add,delete,update,search) [Est]
// (search) [Ploy]

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
    if (cateFil == -1 && yearFil == -1) {
        for (int i = 0; i < numCategory; i++) {
            for (int j = 0; j < numYear; j++) {
                numBooksShow = checkDataEachList(Library[i][j], UserFil);
            }
        }
    }

    // using category filter only
    else if (cateFil != -1 && yearFil == -1) {
        for (int j = 0; j < numYear; j++) {
            numBooksShow = checkDataEachList(Library[cateFil][j], UserFil);
        }
    }

    // using year filter only
    else if (cateFil == -1 && yearFil != -1) {
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

// adding book
void addBook() {

    printf(" -- Adding book --\n");
    // user given the input
    char id[11];
    char title[max_char];
    char author[max_char];
    int year;
    char yearStr[max_char];
    int quantity;

    printf("--  Enter book data -- \n");
    
    printf(" Name of the book : ");
    scanf("%s", title);
    printf("\n");

    // get the index of the category 
    int categoryIndex = filterCategory(categoryNames, numCategory);

    // get the value of the year 
    printf(" Published year : ");
    scanf("%s", yearStr);
    int year = atoi(yearStr);
    int yearIndex = year2yearIndex(year);


    printf(" Author of the book name : ");
    scanf("%s", author);

    printf(" Quantity of the book : ");
    scanf("%d", quantity);

    // traverse to the library linklist and add at the end of the linklist 
    addBookParam(categoryIndex, year, title, author, quantity);
    
}

// edit book
void editBook() {

    printf(" -- Edit book --\n");
    char bookId[15];

    printf(" Enter the book Id here :");
    scanf("%s", bookId);

    int oldCateIndex, oldYear, bookNumber, oldYearIndex;
    oldCateIndex = extractID(bookId)[0];
    oldYear = extractID(bookId)[1];
    bookNumber = extractID(bookId)[2];

    int oldYearIndex = year2yearIndex(oldYear);

    // we can access to data
    booksNode* temp = Library[oldCateIndex][oldYearIndex].head;
    booksNode* prev = temp;

    while (temp->next != NULL) {

        if (strcmp(bookId, temp->data.id) == 0) {
            
            // show book data
            showBookData(temp);
            
            char newTitle[max_char];
            int newCategoryIndex;
            int newYear;
            int newQuantity;
            char newAuthor[max_char];

            // change to which value 
            printf("Enter new title : ");
            scanf("%s", newTitle);

            // for categoryIndex
            do {
                newCategoryIndex = filterCategory(categoryNames, numCategory);

            } while (newCategoryIndex != -1);

            // for year value 
            printf("Enter new published year : ");
            scanf("%d", &newYear);
            int yearIndex = year2yearIndex(newYear);


            // for quantity value
            printf("Enter new quantity : ");
            scanf("%d", &newQuantity);

            // for author value 
            printf("Enter new author name : ");
            scanf("%s", newAuthor);

            // check if category index is changed
            if (newCategoryIndex != oldCateIndex || yearIndex != oldYearIndex) {
                
                // delete 
                deleteBook(Library[oldCateIndex][oldYearIndex].head, prev, temp);

                // add to the new array
                bookParam(newCategoryIndex, newYear, newTitle, newAuthor, newQuantity);
            }
            
            printf(" Change data!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

// delete Book
void deleteBook(booksNode* head, booksNode* prev, booksNode* node) {
    
    if (head == node) {
        head = node->next;
    }

    else {
        // delete data in the linklist 
        prev->next = node->next;
    }
    free(node);
}

// save file to the csv
void saveCSV() {
    FILE* file = fopen(pathFile, "w");

    if (file == NULL) {
        printf("File is not found!");
        return;
    }

    // loop through all book data
    // FT01-00001-2004,Gilead,Marilynne Robinson,Fiction,2004,1,available,1

    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {

            booksNode* temp = Library[i][j].head;
            
            while (temp != NULL) {
                book data = temp->data;
                fprintf("%s %s %s %d %d %d %d", data.id, data.title, data.author, data.category, data.year, data.quantity, data.available);

                temp = temp->next;
            }
        }
    }

    printf("Update successfully!\n");
    return;
}

booksNode* bookParam(int cateIndex, int year, char title[], char author[], int quantity) {
    
    int yearIndex = year2yearIndex(year);

    // create a new book data
    book bookData;
    booksNode* book = (booksNode*)malloc(sizeof(booksNode));

    strcpy(bookData.title, title);
    strcpy(bookData.author, author);
    strcpy(bookData.category, categoryNames[cateIndex]);
    
    bookData.quantity = quantity;
    bookData.available = 1;
    bookData.year = year;
    
    book->data = bookData;
    book->next = NULL;


    // for id check the last id in tail
        // get the book category id
        char bookCate[4];
        for (int i = 0; i < 4; i++) {
            bookCate[i] = cateShortNames[cateIndex][i];
        }

        bookCate[4] = '\0';
        
        char lastId[15];
        char bookNumber[5];
        int bookIdInt = 0;
        
        if (Library[cateIndex][yearIndex].tail != NULL) {

            strcpy(lastId,Library[cateIndex][yearIndex].tail->data.id);
            
            // plus the last number of book index
            for (int i = 0; i < 5; i++) {
                bookNumber[i] = lastId[i+5];
            }

            bookNumber[5] = '\0';
            bookIdInt = atoi(bookNumber) + 1;
        }

        char bookIDNumber[5];

        // Convert bookNumber to string
        sprintf(bookIDNumber, "%05d", bookIdInt);

        char yearID[4];
        // Convert year value to string 
        sprintf(yearID, "%04d", year);

        char newID[15] =  "";

        // Concatenate bookCate
        strcat(newID, bookCate);

        // Concatenate '-'
        strcat(newID, '-');

        // Concatenate bookIDNumber 
        strcat(newID, bookIDNumber);

        // Concatenate '-'
        strcat(newID, '-');

        // Concatenate year 
        strcat(newID, yearID);

    strcpy(book->data.id, newID);
    
    // if it has book in the list assign it
    if (Library[cateIndex][yearIndex].tail != NULL) {

        Library[cateIndex][yearIndex].tail->next = book;
        
    }
    
    // if there is no book before 
    else {
        Library[cateIndex][yearIndex].head = book;
    }

    Library[cateIndex][yearIndex].tail = book;
}

int* extractID(char id[15]) {
    
    // for book number 
        char bookNumber[5];
        int bookNumberInt;
        // plus the last number of book index
        for (int i = 0; i < 5; i++) {
            bookNumber[i] = id[i+5];
        }

        bookNumber[5] = '\0';

        // Convert bookNumber to string
        sprintf(bookNumber, "%05d", bookNumberInt);

    // for year number 
        char bookYear[5];
        int year;
        for (int i = 0; i < 4; i++) {
            bookYear[i] = id[i+11];
        }

        year = atoi(bookYear);

    // find category
        char bookCate[2];
        int categoryIndex;

        for (int i = 0; i < 2; i++) {
            bookCate[i] = id[i+2];
        }

        categoryIndex = atoi(bookCate)-1;

    int data[3];
    data[0] = categoryIndex;
    data[1] = year;
    data[2] = bookNumberInt;

    return data;
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
