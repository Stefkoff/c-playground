/**
* Phone Book project
 *
 * Description:
 * This Phone book Project generates an external file to permanently store the user’s data (Name and phone number).
 * The phone book is a very simple C project that will help you understand the core concepts of capacity,
 * record keeping, and data structure. This program will show you how to add,
 * list, edit or alter, look at, and delete data from a record.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PhoneRecords {
    char number[255];
    char name[255];
};

struct PhoneRecords* loadFromFile(const char* filename, int *recordsFound) {
    FILE* file;
    *recordsFound = 0;

    file = fopen(filename, "rb");

    if(file == NULL) {
        printf("No file found\n");
        return NULL;
    }
    int numRecords;
    if(fread(&numRecords, sizeof(int), 1, file) != 1) {
        return NULL;
    }

    struct PhoneRecords* records = malloc(sizeof(struct PhoneRecords) * numRecords);

    if(fread(records, sizeof(struct PhoneRecords), numRecords, file) != numRecords) {
        free(records);
        return NULL;
    }

    *recordsFound = numRecords;

    fclose(file);

    return records;
}

int saveToFile(const char* filename, struct PhoneRecords* records, int numRecords) {
    FILE* file;
    file = fopen(filename, "wb");

    if(file == NULL) {
        return -1;
    }

    // first write how many records we are saving
    if(fwrite(&numRecords, sizeof(int), 1, file) != 1) {
        return -1;
    }

    if(fwrite(records, sizeof(struct PhoneRecords), numRecords, file) != numRecords) {
        return -1;
    }

    fclose(file);

    return 0;
}

int saveRecord(struct PhoneRecords* record) {
    int currentNumRecords;
    struct PhoneRecords* currentRecords = loadFromFile("phonebook.bin", &currentNumRecords);

    if(currentRecords != NULL && currentNumRecords > 0) {
        currentRecords = realloc(currentRecords, sizeof(struct PhoneRecords) * (currentNumRecords + 1));
        currentRecords[currentNumRecords] = *record;
    } else {
        currentRecords = (struct PhoneRecords*) malloc(sizeof(struct PhoneRecords));
        currentRecords = record;
    }

    if(saveToFile("phonebook.bin", currentRecords, currentNumRecords + 1) != 0)  {
        return -1;
    }

    return 0;
}

void addNewRecord(void) {
    printf("\n");

    struct PhoneRecords* record = (struct PhoneRecords*) malloc(sizeof(struct PhoneRecords));
    printf("Enter a name of the record: ");
    scanf("%s", record->name);
    printf("Enter phone number: ");
    scanf("%s", record->number);


    if(saveRecord(record) == -1){
        printf("Error saving the record\n");
        return;
    }

    printf("Record was saved successfully!\n");

}

void viewRecord(void) {

    int currentNumRecords;
    struct PhoneRecords* currentRecords = loadFromFile("phonebook.bin", &currentNumRecords);

    if(currentRecords == NULL || currentNumRecords <= 0) {
        printf("There are not records!\n");
        return;
    }

    int recordToView;
    printf("Enter the record number: ");
    scanf("%d", &recordToView);

    if(recordToView > currentNumRecords || recordToView <= 0) {
        printf("Record not found!");
        return;
    }

    printf("---------- Displaying the information for record %d----------\n", recordToView);
    printf("Name: %s\n", currentRecords[recordToView - 1].name);
    printf("Phone Number: %s\n", currentRecords[recordToView - 1].number);
}

void updateRecord(void) {
    int currentNumRecords;
    struct PhoneRecords* currentRecords = loadFromFile("phonebook.bin", &currentNumRecords);

    if(currentRecords == NULL || currentNumRecords <= 0) {
        printf("There are not records!\n");
        return;
    }

    int recordToView;
    printf("Enter the record number: ");
    scanf("%d", &recordToView);

    if(recordToView > currentNumRecords || recordToView <= 0) {
        printf("Record not found!");
        return;
    }

    printf("Choose what to change:\n");
    printf("1. Change name\n");
    printf("2. Change number\n");
    printf("Enter you choice: ");
    int choice;
    scanf("%d", &choice);

    if(choice < 1 || choice > 2) {
        printf("You have entered invalid choice. Buy!");
        return;
    }

    printf("\n");
    if(choice == 1) {
        printf("Enter new name [%s]: ", currentRecords[recordToView - 1].name);
        scanf("%s", currentRecords[recordToView - 1].name);
    } else {
        printf("Enter new number [%s]: ", currentRecords[recordToView - 1].number);
        scanf("%s", currentRecords[recordToView - 1].number);
    }

    printf("\n");

    printf("Updating the record...\n");

    if(saveToFile("phonebook.bin", currentRecords, currentNumRecords) == -1) {
        printf("Could not update the record!\n");
        return;
    }

    printf("Record was successfully updated!'n");
}

void deleteRecord(void) {
    int currentNumRecords;
    struct PhoneRecords* currentRecords = loadFromFile("phonebook.bin", &currentNumRecords);

    if(currentRecords == NULL || currentNumRecords <= 0) {
        printf("There are not records!\n");
        return;
    }

    int recordToView;
    printf("Enter the record number: ");
    scanf("%d", &recordToView);

    if(recordToView > currentNumRecords || recordToView <= 0) {
        printf("Record not found!");
        return;
    }

    struct PhoneRecords* newRecords = (struct PhoneRecords*) malloc((sizeof (struct PhoneRecords) * currentNumRecords - 1));
    int index = 0;
    for(int i = 0; i < currentNumRecords; i++) {
        if(i != recordToView - 1) {
            newRecords[index++] = currentRecords[i];
        }
    }

    if(saveToFile("phonebook.bin", newRecords, currentNumRecords - 1) == -1) {
        printf("Could not delete the record!\n");
    }

    printf("The record was deleted successfully!\n");
}

void printAllRecords(void) {
    int currentNumRecords;
    struct PhoneRecords* currentRecords = loadFromFile("phonebook.bin", &currentNumRecords);

    if(currentRecords == NULL || currentNumRecords <= 0) {
        printf("There are not records!\n");
        return;
    }

    for(int i = 0; i < currentNumRecords; i++) {
        printf("Displaying record: %d\n", i + 1);
        printf("\tName: %s\n", currentRecords[i].name);
        printf("\tNumber: %s\n", currentRecords[i].number);
    }
}

void deleteAllRecords(void) {

    printf("Are you sure you want to remove all records?: ");
    int choice;
    scanf("%d", &choice);

    if(choice != 1 && choice != 0) {
        printf("Invalid choice");
        return;
    }

    if(choice == 1) {
        if(remove("phonebook.bin") == 0) {
            printf("All records have been deleted!\n");
            return;
        }

        printf("Could not delete the records!\n");

    }
}

void handleCommand(int choice) {
    switch (choice) {
        case 1:
            addNewRecord();
            break;
        case 2:
            viewRecord();
            break;
        case 3:
            updateRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            printAllRecords();
            break;
        case 6:
            deleteAllRecords();
            break;
    }
}

void printMenu() {
    printf("\n");
    printf("Choose from the options below:...\n");
    printf("1. Add new records\n");
    printf("2. View specific record\n");
    printf("3. Update specific record\n");
    printf("4. Delete specific record\n");
    printf("5. Print all records\n");
    printf("6. Delete all records\n");
    printf("0. Exit\n");
    printf("Enter you your choice [1-6]: ");
    int choice;
    scanf("%d", &choice);
    if(choice == 0) {
        return;
    }

    if(choice > 6) {
        printf("Invalid options!");
        printMenu();
    }

    handleCommand(choice);
    printMenu();
}

int main() {
    printMenu();
    return 0;
}