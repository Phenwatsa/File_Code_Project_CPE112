#include "Data_Func.h"
#include "Other_Func.h"
#include "Book_Management_Func.h"

void searchBook() {
    Line2();
    printf("%38s\n","Welcome to search function");
    Line();
    printf(" Search by id or Name of the book : ");

    // read the string data 
    char UserFil[max_char];
    scanf(" %s", UserFil);
    UserFil[strcspn(UserFil, "\n")] = '\0'; // Remove any trailing newline character

    Line2();
    // for user to enter the category filter
    printf(" Using filter for category\n");
    int cateFil = filterCategory(categoryNames, numCategory);  
    printf("%d\n", cateFil); 

    Line2();
    // for user to enter the year filter
    printf(" Using filter for year\n");
    int yearFil = filterCategory(yearNames, numYear);
    printf(" %d\n", yearFil);

    ClearScreen();
    printf("%107s\n", "-- List of Book Below --"); Line3(190);
    printf(" %-15s | %-80s | %-40s | %-25s | %-5s | %-3s | %-3s\n", 
        "ID", "Title", "Author", "Category", "Year", "Qty", "Avl");
    Line3(190);
    // number of book that have been showed
    int numBooksShow = 0;

    // does not use the category filter and year filter
    if (cateFil == -1 && yearFil == -1) {
        for (int i = 0; i < numCategory; i++) {
            for (int j = 0; j < numYear; j++) {
                numBooksShow += checkDataEachList(Library[i][j], UserFil);
            }
        }
    }

    // using category filter only
    else if (cateFil != -1 && yearFil == -1) {
        for (int j = 0; j < numYear; j++) {
            numBooksShow += checkDataEachList(Library[cateFil][j], UserFil);
        }
    }

    // using year filter only
    else if (cateFil == -1 && yearFil != -1) {
        for (int i = 0; i < numCategory; i++) {
            numBooksShow += checkDataEachList(Library[i][yearFil], UserFil);
        }
    }

    // using both year and category filter
    else {
        numBooksShow += checkDataEachList(Library[cateFil][yearFil], UserFil);
    }
    Line4(190);
    printf(" Number of book found is : %d\n", numBooksShow);
    Line4(190);
}

// Function for user to describe how to use filter in search function
int filterCategory(char listName[][max_char], int number_list) {
    char cateFil[3];
    Line();
    // show all filter that possible to use
    for (int i = 0; i < number_list; i++) {
        printf("  [%d] to use %s\n", i+1, listName[i]);
    }
    Line();
    printf("  [0] to not use the filter\n");
    Line2();
    int cateFilIndex;

    do {
        printf(" Enter Number filter for category it here : ");
        scanf(" %s", cateFil);

        // value will be transform from string to int but if it return -1 means invalid
        cateFilIndex = filterUsable(cateFil, number_list);
    }

    while (cateFilIndex == -1);
    return cateFilIndex-1;
}

int filterUsable(char filter[], int number_filter) {
    // if input number is not a digit 
    if (isNotInteger(filter) == 1) {
        printf(" We aren't accept other type of data except integer\n");
        return -1;
    }

    // if input number is over the range of number of the category
    // atoi use to transform string -> int like '30' -> 30
    if (atoi(filter) > number_filter || atoi(filter) < 0) {
        printf(" The integer is out of our range of category\n");
        return -1;
    }

    // return the int value
    return atoi(filter);
}

// adding book
void addBook() {
    Line2();
    printf("%30s\n","Adding book");
    // user given the input
    char title[max_char];
    char author[max_char];
    int year;
    char yearStr[max_char];
    int quantity;

    Line2();
    printf(" Name of the book : ");
    scanf(" %[^\n]", title);

    // get the index of the category 
    ClearScreen(); Line2();
    printf(" Using filter for category\n");

    int categoryIndex;
    do {
         categoryIndex = filterCategory(categoryNames, numCategory); 
    } while (categoryIndex == -1);

    // get the value of the year 
    printf(" Published year : ");
    scanf(" %s", yearStr);

    year = atoi(yearStr);

    printf(" Author of the book name : ");
    getchar();
    scanf(" %[^\n]", author);

    printf(" Quantity of the book : ");
    scanf(" %d", &quantity);

    // traverse to the library linklist and add at the end of the linklist 
    addBookParam(categoryIndex, year, title, author, quantity);
    Exit();
}

// edit book
void editBook() {
    Line2();
    printf("%30s\n","Edit book");
    Line2();
    char bookId[16];

    printf(" Enter the book Id here : ");
    scanf(" %s", bookId);

    int oldCateIndex, oldYear, bookNumber, oldYearIndex;

    extractID(bookId, &oldCateIndex, &oldYear, &bookNumber);

    if (oldCateIndex > 11 || oldCateIndex < 0) {
        ClearScreen();
        printf(" ! Invalid input category\n"); 
        Line(); Delay();
        return;
    }

    if (oldYear < 0 ) {
        ClearScreen();
        printf(" ! Invalid input year\n"); 
        Line(); Delay();
        return;
    }

    oldYearIndex = year2yearIndex(oldYear);

    // we can access to data
    booksNode* temp = Library[oldCateIndex][oldYearIndex].head;
    booksNode* prev = temp;

    int found = 0;
    while (temp != NULL) {
        if (strcmp(bookId, temp->data.id) == 0) {
            found = 1;
            // show book data
            Line4(190);
            showBookData(temp);
            
            char newTitle[max_char];
            char newCateStr[3];
            int newCategoryIndex = 0;
            char newYearStr[5];
            int newYear = 0;
            char newQuantityStr[3];
            int newQuantity = 0;
            char newAuthor[max_char];
            Line4(190);
            // change to which value 
            printf(" Enter new title : ");
            scanf(" %[^\n]", newTitle);

            // for categoryIndex
            newCategoryIndex = filterCategory(categoryNames, numCategory);

            // for year value 
            do {
                printf(" Enter new published year : ");
                scanf(" %s", newYearStr);
            } while (isNotInteger(newYearStr));

            newYear = atoi(newYearStr);
            int newYearIndex = year2yearIndex(newYear);


            // for quantity value
            do {
                printf(" Enter new quantity : ");
                scanf(" %s", newQuantityStr);
            } while (isNotInteger(newQuantityStr));
            newQuantity = atoi(newQuantityStr);

            // for author value 
            printf(" Enter new author name : ");
            getchar();
            scanf(" %[^\n]", newAuthor);

            // check if category index or year is changed
            if (newCategoryIndex != oldCateIndex || newYearIndex != oldYearIndex) {
                // delete 
                deleteBook(&Library[oldCateIndex][oldYearIndex].head, &Library[oldCateIndex][oldYearIndex].tail, prev, temp);
                // add to the new array
                addBookParam(newCategoryIndex, newYear, newTitle, newAuthor, newQuantity);
            }

            else {
                // change data
                // title author cate year quantity
                strcpy(temp->data.author, newAuthor);
                strcpy(temp->data.category, categoryNames[newCategoryIndex]);
                strcpy(temp->data.title, newTitle);
                temp->data.year = newYear;
                temp->data.quantity = newQuantity;
            }
            Line();
            printf(" Change data!\n");
            Line2(); Exit();
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    if (found == 0){
        ClearScreen();
        printf(" !!! ID Book is not found\n"); Line();
        Exit();
        return;
    }
}

void delete() {
    Line2();
    printf("%30s\n","delete book");
    Line2();
    char bookId[16];

    printf(" Enter the book Id here : ");
    scanf(" %s", bookId);

    int cateIndex, year, bookNumber, yearIndex;

    extractID(bookId, &cateIndex, &year, &bookNumber);

    if (cateIndex > 11 || cateIndex < 0) {
        ClearScreen();
        printf(" ! Invalid input category\n"); 
        Line(); Delay();
        return;
    }

    if (year < 0 ) {
        ClearScreen();
        printf(" ! Invalid input year\n"); 
        Line(); Delay();
        return;
    }

    yearIndex = year2yearIndex(year);

    // we can access to data
    booksNode* temp = Library[cateIndex][yearIndex].head;
    booksNode* prev = temp;
    Line2();
    printf(" The book [%s] has been removed\n", bookId);
    Line2();

    if (Library[cateIndex][yearIndex].head == NULL) {
        ClearScreen();
        printf(" !!!Error: No books found in the specified category and year.\n");
        Line(); Delay();
        return;
    }

    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->data.id, bookId) == 0) {
            deleteBook(&Library[cateIndex][yearIndex].head, &Library[cateIndex][yearIndex].tail, prev, temp);
            found = 1;
        }

        prev = temp;
        temp = temp->next;
    }

    if (found == 0) {
        ClearScreen();
        printf(" !!! The ID Book is not found\n");
        Line();
    }
    Exit();
}

// delete Book
void deleteBook(booksNode** head, booksNode** tail, booksNode* prev, booksNode* node) {
    if (*head == node) {
        *head = node->next;
        if (*tail == node) *tail = NULL;
    }

    else {
        // delete data in the linklist 
        prev->next = node->next;
        if (*tail == node) {
            *tail = prev;
        }
    }
    free(node);
}

// save file to the csv
void saveCSV() {
    FILE* file = fopen("DATA/Book-ID.csv", "w");

    if (file == NULL) {
        ClearScreen();
        printf("Couldn't open a file!");
        Line(); Delay();
        return;
    }

    // write the header 
    fprintf(file, "Book_ID,Title,Author,Category,Year_Published,Quantity,Status,Borrowed\n");

    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            booksNode* temp = Library[i][j].head;

            while (temp != NULL) {
                book data = temp->data;

                // Write the data to the file
                fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d\n", 
                        data.id, data.title, data.author, data.category, 
                        data.year, data.quantity, data.available, data.borrowCount);

                temp = temp->next;
            }
        }
    }
    fclose(file);
}

void addBookParam(int cateIndex, int year, char title[], char author[], int quantity) {
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
    bookData.borrowCount = 0;
    bookData.reservationQueue = NULL;
    
    book->data = bookData;
    book->next = NULL;

    // for id check the last id in tail
        
        char lastId[16];
        char bookNumber[6];
        int bookIdInt = 1;

        if (Library[cateIndex][yearIndex].tail != NULL) {

            strcpy(lastId,Library[cateIndex][yearIndex].tail->data.id);

            // plus the last number of book index
            for (int i = 0; i < 5; i++) {
                bookNumber[i] = lastId[i+5];
            }

            bookNumber[5] = '\0';
            bookIdInt = atoi(bookNumber) + 1;

        }

        char bookIDNumber[6];

        // Convert bookNumber to string
        sprintf(bookIDNumber, "%05d", bookIdInt);
        
        char yearID[5] = "";
        // Convert year value to string 
        sprintf(yearID, "%04d", year);
        
        char newID[16] =  "";
        // Concatenate bookCate
        
        strcat(newID, cateShortNames[cateIndex]);

        // Concatenate '-'
        strcat(newID, "-");

        // ID : FT01--2014
        // Concatenate bookIDNumber 
        strcat(newID, bookIDNumber);

        // Concatenate '-'
        strcat(newID, "-");

        // Concatenate year 
        strcat(newID, yearID);

    strcpy(book->data.id, newID);

    // if the book is not empty
    if (Library[cateIndex][yearIndex].tail != NULL) {
        Library[cateIndex][yearIndex].tail->next = book;
    
        // if the book is empty
    } else {
        Library[cateIndex][yearIndex].head = book;
    }
    Library[cateIndex][yearIndex].tail = book;

    Line2();
    printf(" Add successfully\n");
    Line2();
}

void extractID(char id[16], int* categoryIndex, int* year, int* bookNumberInt) {
    // for book number 
        char bookNumber[6];
        // plus the last number of book index
        for (int i = 0; i < 5; i++) {
            bookNumber[i] = id[i+5];
        }
        
        bookNumber[5] = '\0';
        
        
    // for year number 
        char bookYear[5];
        for (int i = 0; i < 4; i++) {
            bookYear[i] = id[i+11];
        }

        *year = atoi(bookYear);

    // find category
        char bookCate[3];

        for (int i = 0; i < 2; i++) {
            bookCate[i] = id[i+2];
        }

        bookCate[2] = '\0';

        *categoryIndex = atoi(bookCate)-1;
}

// function to show all the books
void showAllBooks() {
    ClearScreen();
    Line4(162);
    printf("%88s\n","List of Books");
    Line4(162);
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            // Display only if the list is not empty
            if (Library[i][j].head != NULL) {
                printf(" Category : [%s]  | Year : [%s]\n", categoryNames[i], yearNames[j]);
                Line3(162);

                // Display the header
                printf("%-15s | %-70s | %-50s | %-5s | %-3s | %-3s\n", 
                       "ID", "Title", "Author", "Year", "Qty", "Avl");
                       Line3(162);

                // Display the book list
                showBookList(Library[i][j].head);
                Line3(162);
            }
        }
    }
    Line4(162);
    Exit();
}

// Loop the linklist
void showBookList(booksNode* temp) {
    while (temp != NULL) {
        printf("%-15s | %-70s | %-50s | %-5d | %2d  | %-3d\n",
               temp->data.id,
               temp->data.title,
               temp->data.author,
               temp->data.year,
               temp->data.quantity,
               temp->data.available);
        temp = temp->next;
    }
}

void showBookData(booksNode* temp) {
    printf(" %-15s |", temp->data.id);
    printf(" %-80s |", temp->data.title);
    printf(" %-40s |", temp->data.author);
    printf(" %-25s |", temp->data.category);
    printf(" %-5d |", temp->data.year);
    printf(" %-3d |", temp->data.quantity);
    printf(" %-3d\n", temp->data.available);
}

int checkDataEachList(booksListInfo linkList, char userInput[]) {
    booksNode* temp = linkList.head;

    int numBooks = 0;

    while (temp != NULL) {
        if (strstr(temp->data.title, userInput) != NULL) {
            showBookData(temp);
            numBooks += 1;
        }
    
        else if (strstr(temp->data.id, userInput) != NULL) {
            showBookData(temp);
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