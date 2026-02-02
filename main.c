#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 256
#define FILENAME "work_schedule.txt"

typedef struct {
    char date[20];
    char check_in[10];
    char check_out[10];
    char employer_name[MAX_STRING];
    char employer_id[50];
    char work_description[MAX_STRING];
} WorkEntry;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(date, 20, "%Y-%m-%d", tm_info);
}

void addWorkEntry() {
    WorkEntry entry;
    FILE *file;

    // Get current date
    getCurrentDate(entry.date);
    printf("\nAdding work entry for: %s\n", entry.date);
    printf("-----------------------------------\n");

    // Get check-in time
    printf("Check-in time (HH:MM): ");
    if (fgets(entry.check_in, sizeof(entry.check_in), stdin) != NULL) {
        entry.check_in[strcspn(entry.check_in, "\n")] = 0;
    }

    // Get check-out time
    printf("Check-out time (HH:MM): ");
    if (fgets(entry.check_out, sizeof(entry.check_out), stdin) != NULL) {
        entry.check_out[strcspn(entry.check_out, "\n")] = 0;
    }

    // Get employer name
    printf("Employer name: ");
    if (fgets(entry.employer_name, sizeof(entry.employer_name), stdin) != NULL) {
        entry.employer_name[strcspn(entry.employer_name, "\n")] = 0;
    }

    // Get employer ID
    printf("Employer ID: ");
    if (fgets(entry.employer_id, sizeof(entry.employer_id), stdin) != NULL) {
        entry.employer_id[strcspn(entry.employer_id, "\n")] = 0;
    }

    // Get work description
    printf("Work description: ");
    if (fgets(entry.work_description, sizeof(entry.work_description), stdin) != NULL) {
        entry.work_description[strcspn(entry.work_description, "\n")] = 0;
    }

    // Save to file
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    fprintf(file, "Date: %s\n", entry.date);
    fprintf(file, "Check-in: %s\n", entry.check_in);
    fprintf(file, "Check-out: %s\n", entry.check_out);
    fprintf(file, "Employer: %s\n", entry.employer_name);
    fprintf(file, "Employer ID: %s\n", entry.employer_id);
    fprintf(file, "Work Description: %s\n", entry.work_description);
    fprintf(file, "-----------------------------------\n\n");

    fclose(file);
    printf("\nWork entry saved successfully!\n");
}

void viewAllEntries() {
    FILE *file;
    char ch;

    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nNo entries found. The file doesn't exist yet.\n");
        return;
    }

    printf("\n======= WORK SCHEDULE HISTORY =======\n\n");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void displayMenu() {
    printf("\n====== WORK SCHEDULE TRACKER ======\n");
    printf("1. Add new work entry\n");
    printf("2. View all entries\n");
    printf("3. Exit\n");
    printf("===================================\n");
    printf("Choose an option: ");
}

int main() {
    int choice;

    printf("Welcome to Work Schedule Tracker!\n");

    while (1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addWorkEntry();
                break;
            case 2:
                viewAllEntries();
                break;
            case 3:
                printf("\nThank you for using Work Schedule Tracker!\n");
                return 0;
            default:
                printf("\nInvalid option. Please choose 1, 2, or 3.\n");
        }
    }

    return 0;
}
