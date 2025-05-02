// Add book to the library structure
#include "Data_Func.h"

// Set list of category
char categoryNames[numCategory][max_char] = {"Fiction", "History", "Science", "Biography & Autography", "Psychology", "Religion", "Business & Economics", "Computers", "Cooking", "Mathematics", "Comics & Graphic Novels"};

char cateShortNames[numCategory][5] = {"FT01", "HT02", "SC03", "BI04", "PS05", "RE06", "BE07", "CP08", "CK09", "MT10", "CG11"};

// Set list of year range
char yearNames[numYear][max_char] = {"below 1975", "1975-1985", "1985-1995", "1995-2005", "2005-2015", "2015-2025", "above 2025"};

// path to csv file
char pathFile[] = "DATA/Book-ID.csv";

// Initialize data to be NULL
void InitializeLibrary() {
    for (int i = 0; i < numCategory; i++) {
        for (int j = 0; j < numYear; j++) {
            Library[i][j].head = NULL;
            Library[i][j].tail = NULL;
        }
    }
}

int year2yearIndex(int year) {
    // find the index of given year
    int yearIndex = (year - 1975) / 10;
    if (yearIndex < 0) yearIndex = 0;
    else if (yearIndex < 6) yearIndex += 1;
    else yearIndex = 6; 
    return yearIndex;
}

void csvToStruct() {
    FILE* csvFile = fopen(pathFile, "r");

    if (csvFile == NULL) {
        printf("ERROR: File not found: %s\n", pathFile);
        return;
    }

    char line[max_line];

    if (fgets(line, sizeof(line), csvFile)) {
        if (line[0] == '\xEF' && line[1] == '\xBB' && line[2] == '\xBF') {
            memmove(line, line + 3, strlen(line) - 2);
        } else {
            fseek(csvFile, 0, SEEK_SET);
        }
    }

    int count = 0;

    while (fgets(line, sizeof(line), csvFile)) {

        if (count == 0) {
            count = 1;
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        char* id = strtok(line, ",");
        char* title = strtok(NULL, ",");
        char* author = strtok(NULL, ",");
        char* category = strtok(NULL, ",");
        char* yearStr = strtok(NULL, ",");
        char* quantityStr = strtok(NULL, ",");
        char* availableStr = strtok(NULL, ",");
        char* borrowCountStr = strtok(NULL, ",");
        

        if (!id || !title || !author || !category || !yearStr || !quantityStr || !availableStr || !borrowCountStr) {
            printf("ERROR: Invalid line format: %s\n", line);
            continue;
        }

        int quantity = atoi(quantityStr);
        int available = strcmp(availableStr, "available") == 0 ? 1 : 0;

        int categoryIndex = 10 * (id[2] - '0') + (id[3] - '0') - 1;
        int year = atoi(yearStr);
        int yearIndex = year2yearIndex(year);
        int borrowCount = atoi(borrowCountStr);

        if (categoryIndex < 0 || categoryIndex >= numCategory || yearIndex < 0 || yearIndex >= numYear) {
            printf("ERROR: Invalid categoryIndex (%d) or yearIndex (%d)\n", categoryIndex, yearIndex);
            continue;
        }

        booksNode* newBookNode = (booksNode*)malloc(sizeof(booksNode));
        if (newBookNode == NULL) {
            printf("ERROR: Memory allocation failed\n");
            fclose(csvFile);
            return;
        }

        book newBooks;
        strcpy(newBooks.id, id);
        strcpy(newBooks.title, title);
        strcpy(newBooks.author, author);
        strcpy(newBooks.category, category);
        newBooks.year = year;
        newBooks.available = available;
        newBooks.quantity = quantity;
        newBooks.borrowCount = borrowCount;
        newBooks.reservationQueue = NULL;
        newBookNode->data = newBooks;
        newBookNode->next = NULL;

        if (Library[categoryIndex][yearIndex].tail == NULL) {
            Library[categoryIndex][yearIndex].head = newBookNode;
            Library[categoryIndex][yearIndex].tail = newBookNode;
        } else {
            Library[categoryIndex][yearIndex].tail->next = newBookNode;
            Library[categoryIndex][yearIndex].tail = newBookNode;
        }
    }

    fclose(csvFile);
}

void BorrowQueue(booksNode* bookNode) {
    if (bookNode == NULL) {
        printf("ERROR: Book node is NULL\n");
        return;
    }

    if (bookNode->data.available == 0) {
        printf("ERROR: Book ip not available for borrowing\n");
        return;
    }

    bookNode->data.available = 0;
    bookNode->data.borrowCount += 1;

    printf("Book borrowed successfully: %s\n", bookNode->data.title);
}