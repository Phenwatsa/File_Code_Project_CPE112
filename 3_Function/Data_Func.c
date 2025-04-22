// Add book to the library structure
#include "Data_Func.h"

// Set list of category
char categoryNames[numCategory][max_char] = {"Fiction", "History", "Science", "Biography & Autography", "Psychology", "Religion", "Business & Economics", "Computers", "Cooking", "Mathematics", "Comics & Graphic Novels"};

// Set list of year range
char yearNames[numYear][max_char] = {"below 1975", "1975-1985", "1985-1995", "1995-2005", "2005-2015", "2015-2025", "2025-2035"};

char pathFile[] = "Book-ID.csv";

// Initialize data to be NULL
void InitializeLibrary() {
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            Library[i][j].head = NULL;
            Library[i][j].tail = NULL;
        }
    }
}

void csvToStruct() {
    
    FILE* csvFile = fopen(pathFile, "r");

    if (csvFile == NULL) {
        printf("File not found\n");
        return;
    }

    // set line value for reading csv with fgets
    char line[max_line];

    // In case if it has weird value in csv for the first two value
    if (fgets(line, sizeof(line), csvFile)) {
        if (line[0] == '\xEF' && line[1] == '\xBB' && line[2] == '\xBF') {
            memmove(line, line + 3, strlen(line) - 2);
        } else {
            fseek(csvFile, 0, SEEK_SET);
        }
    }
    
    // With fget will read the file and split it into part 
    while (fgets(line, sizeof(line), csvFile)) {
        line[strcspn(line, "\n")] = '\0';

        // tokenize the line using strtok
        char* id = strtok(line, ",");
        char* title = strtok(NULL, ",");
        char* author = strtok(NULL, ",");
        char* category = strtok(NULL, ",");
        char* yearStr = strtok(NULL, ",");
        char* quantityStr = strtok(NULL, ",");
        char* availableStr = strtok(NULL, ",");
        char* bookIndex = strtok(NULL, ",");
        
        // convert the quantity to quantity
        // atoi can transform '30' -> 30 ** Use with string only **
        int quantity = atoi(quantityStr);
        int available = 0;

        // change available to 1
        if (strcmp(availableStr, "available") == 0)  available = 1;


        // read category data
        int categoryIndex = 0;
        categoryIndex += 10 * (int)(id[2] - '0');
        categoryIndex += (int)(id[3] - '0') - 1;
        
        
        // atoi can transform '30' -> 30 ** Use with string only **
        int year = atoi(yearStr);

        // find index of year array
        int yearIndex = (year - 1975) / 10;
        if (yearIndex < 0) yearIndex = 0;
        else yearIndex += 1; 
        
        booksNode* newBookNode = (booksNode*)malloc(sizeof(booksNode)); 
        book newBooks;
        
        strcpy(newBooks.id, id);
        strcpy(newBooks.title, title);
        strcpy(newBooks.author, author);
        strcpy(newBooks.category, category);
        newBooks.available = available;
        newBooks.quantity = quantity;
        newBooks.year = year;
        
        newBookNode->data = newBooks;
        newBookNode->next = NULL;

        // if the value is not initialize yet 
        // create one and assign it
        if (Library[categoryIndex][yearIndex].tail == NULL) {
            
            Library[categoryIndex][yearIndex].head = newBookNode;
            Library[categoryIndex][yearIndex].tail = newBookNode;
            continue;
        }
        
        // set the value of the new book
        Library[categoryIndex][yearIndex].tail->next = newBookNode;

        // set the location of tail value
        Library[categoryIndex][yearIndex].tail = newBookNode;
    }
}