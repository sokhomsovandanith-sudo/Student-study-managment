#include <stdio.h>
#include <string.h>

#define SUBJECTS 5

typedef struct {
    char subject[100];
} Subject;

void inputSubjects(Subject s[]) {
    for (int i = 0; i < SUBJECTS; i++) {
        printf("\nEnter subject %d: ", i + 1);
        scanf("%s", s[i].subject);  
    }
}

void addDayData(Subject s[]) {
    FILE *file = fopen("data.txt", "a");
    int day;
    float hours;

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter day (1-7): ");
    scanf("%d", &day);

    for (int i = 0; i < SUBJECTS; i++) {
        printf("%s hours: ", s[i].subject);
        scanf("%f", &hours);

        fprintf(file, "Day %d %s %.2f\n", day, s[i].subject, hours);
    }

    fclose(file);
    printf("Data saved successfully!\n");
}

void displayData() {
    FILE *file = fopen("data.txt", "r");
    int day;
    char subject[100];
    float hours;

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\n--- All Study Records ---\n");

    while (fscanf(file, " Day %d %s %f", &day, subject, &hours) == 3) {
        printf("Day %d - %s: %.2f hours\n", day, subject, hours);
    }

    fclose(file);
}

void totalHours() {
    FILE *file = fopen("data.txt", "r");
    int day;
    char subject[100];
    float hours, total = 0;

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    while (fscanf(file, " Day %d %s %f", &day, subject, &hours) == 3) {
        total += hours;
    }

    fclose(file);
    printf("\nTotal study hours: %.2f\n", total);
}

void updateData() {
    FILE *file = fopen("data.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    int targetDay, day;
    char targetSubject[100], subject[100];
    float hours, newHours;
    int found = 0;

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter day to update: ");
    scanf("%d", &targetDay);

    printf("Enter subject to update: ");
    scanf("%s", targetSubject);  

    printf("Enter new hours: ");
    scanf("%f", &newHours);

    while (fscanf(file, " Day %d %s %f", &day, subject, &hours) == 3) {
        if (day == targetDay && strcmp(subject, targetSubject) == 0) {
            fprintf(temp, "Day %d %s %.2f\n", day, subject, newHours);
            found = 1;
        } else {
            fprintf(temp, "Day %d %s %.2f\n", day, subject, hours);
        }
    }

    fclose(file);
    fclose(temp);

  if (remove("data.txt") == 0)
    printf("Old file deleted\n");
else
    printf("Failed to delete old file\n");

if (rename("temp.txt", "data.txt") == 0)
    printf("File updated successfully\n");
else
    printf("Failed to rename file\n");

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found.\n");
} 

void mostStudied() {
    FILE *file = fopen("data.txt", "r");
    int day;
    char subject[100];
    
    char subjects[100][100];
    float totals[100] = {0};
    int count = 0;
    float hours;

    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    while (fscanf(file, " Day %d %s %f", &day, subject, &hours) == 3) {
        int found = -1;
        for (int i = 0; i < count; i++) {
            if (strcmp(subjects[i], subject) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            strcpy(subjects[count], subject);
            totals[count] = hours;
            count++;
        } else {
            totals[found] += hours;
        }
    }

    fclose(file);
    if (count == 0) {
        printf("No data to analyze.\n");
        return;
    }

    float max = -1;
    int index = 0;

    for (int i = 0; i < count; i++) {
        if (totals[i] > max) {
            max = totals[i];
        }
    }

    printf("\nMost studied subject:\n");
     for (int i = 0; i < count; i++) {
        if (totals[i] == max) {
            printf("%s (%.2f hours)\n", subjects[i], totals[i]);
        }
    }
}

int main() {
    Subject s[SUBJECTS];
    int choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Input Subject\n");
        printf("2. Add Study Time\n");
        printf("3. View All Data\n");
        printf("4. Total Hours\n");
        printf("5. Most Studied Subject\n");
        printf("6. Update Data\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: inputSubjects(s); break;
            case 2: addDayData(s); break;
            case 3: displayData(); break;
            case 4: totalHours(); break;
            case 5: mostStudied(); break;
            case 6: updateData(); break;
            case 7: printf("Good job all students!!\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 7);

    return 0;
}