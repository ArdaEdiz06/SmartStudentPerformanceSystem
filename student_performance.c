#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NUM_SUBJECTS 3

typedef struct {
    char name[50];
    float marks[NUM_SUBJECTS];
    float total;
    float average;
    char grade;
    int passed;
} Student;

Student students[MAX_STUDENTS];
int count = 0;

char getGrade(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

void addStudent() {
    if (count >= MAX_STUDENTS) {
        printf("Class is full!\n");
        return;
    }
    printf("\nEnter student name: ");
    scanf(" %[^\n]", students[count].name);
    float total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter mark for subject %d (0-100): ", i + 1);
        scanf("%f", &students[count].marks[i]);
        total += students[count].marks[i];
    }
    students[count].total   = total;
    students[count].average = total / NUM_SUBJECTS;
    students[count].grade   = getGrade(students[count].average);
    students[count].passed  = students[count].average >= 60 ? 1 : 0;
    count++;
    printf("Student added successfully!\n");
}

void showAllResults() {
    if (count == 0) { printf("No students yet.\n"); return; }
    printf("\n%-20s %-8s %-8s %-8s %-8s %-8s %-6s %-6s\n",
           "Name", "Sub1", "Sub2", "Sub3", "Total", "Avg", "Grade", "Status");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f %-6c %-6s\n",
               students[i].name,
               students[i].marks[0], students[i].marks[1], students[i].marks[2],
               students[i].total, students[i].average,
               students[i].grade,
               students[i].passed ? "Pass" : "Fail");
    }
}

void showStatistics() {
    if (count == 0) { printf("No students yet.\n"); return; }
    int passed = 0, failed = 0;
    float totalAvg = 0;
    int highIdx = 0, lowIdx = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].passed) passed++; else failed++;
        totalAvg += students[i].average;
        if (students[i].average > students[highIdx].average) highIdx = i;
        if (students[i].average < students[lowIdx].average)  lowIdx  = i;
    }
    printf("\n=== Class Statistics ===\n");
    printf("Total Students  : %d\n", count);
    printf("Class Average   : %.2f\n", totalAvg / count);
    printf("Highest Student : %s (%.2f)\n", students[highIdx].name, students[highIdx].average);
    printf("Lowest Student  : %s (%.2f)\n", students[lowIdx].name,  students[lowIdx].average);
    printf("Passed          : %d\n", passed);
    printf("Failed          : %d\n", failed);
}

int main() {
    int choice;
    printf("=== ARIDA Smart Student Performance System ===\n");
    do {
        printf("\n1. Add Student\n2. Show All Results\n3. Show Class Statistics\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent();    break;
            case 2: showAllResults(); break;
            case 3: showStatistics(); break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}
