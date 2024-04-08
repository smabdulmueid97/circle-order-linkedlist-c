#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a student
struct Student {
    char name[20];
    struct Student* next;
};

// Function to create a new student node
struct Student* createStudent(char name[]) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->next = NULL;
    return newStudent;
}

// Function to insert a student at the end of the list
void insertStudent(struct Student** head, char name[]) {
    struct Student* newStudent = createStudent(name);
    if (*head == NULL) {
        *head = newStudent;
    } else {
        struct Student* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newStudent;
    }
}

// Function to display the list of students in the requested format
void displayList(struct Student* head) {
    printf("List of students:\n");
    struct Student* temp = head;
    char prefix = 'A';
    while (temp != NULL) {
        printf("%c %s\n", prefix++, temp->name);
        temp = temp->next;
    }
}

// Function to reorder the list as per the given pattern
void reorderList(struct Student** head, char startChar) {
    if (*head == NULL)
        return;

    struct Student* newHead = NULL;
    struct Student* newTail = NULL;
    struct Student* current = *head;
    struct Student* prev = NULL;

    while (current != NULL) {
        if (current->name[0] == startChar) {
            if (newHead == NULL) {
                newHead = current;
                newTail = current;
            } else {
                newTail->next = current;
                newTail = current;
            }
            if (prev != NULL)
                prev->next = current->next;
            if (*head == current)
                *head = current->next;
            current = current->next;
            newTail->next = NULL;
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (newHead != NULL) {
        newTail->next = *head;
        *head = newHead;
    }

    // Display the reordered list
    displayList(*head);
}

// Function to compare two student names for sorting
int compareNames(const void* a, const void* b) {
    return strcmp(((struct Student*)a)->name, ((struct Student*)b)->name);
}

// Function to sort the list in ascending order by name
void sortList(struct Student** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    // Count the number of nodes
    struct Student* temp = *head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }

    // Create an array of pointers to nodes
    struct Student* arr[count];
    temp = *head;
    int i = 0;
    while (temp != NULL) {
        arr[i] = temp;
        temp = temp->next;
        i++;
    }

    // Sort the array of pointers by student names
    qsort(arr, count, sizeof(struct Student*), compareNames);

    // Reconnect the nodes based on the sorted array
    *head = arr[0];
    for (i = 0; i < count - 1; i++)
        arr[i]->next = arr[i + 1];
    arr[count - 1]->next = NULL;

    // Display the sorted list
    displayList(*head);
}

int main() {
    struct Student* head = NULL;

    // Inserting students
    insertStudent(&head, "Juana");
    insertStudent(&head, "Amia");
    insertStudent(&head, "Siti");
    insertStudent(&head, "Benny");

    // Display the list of students
    displayList(head);

    // Get user input for starting character
    char startChar;
    printf("\nEnter the starting character (A to D): ");
    scanf(" %c", &startChar);
    startChar = toupper(startChar); // Convert to uppercase

    // Reorder the list based on user input
    printf("\nReordered list starting from '%c':\n", startChar);
    reorderList(&head, startChar);

    // Sort the list in ascending order by name
    printf("\nList sorted in ascending order by name:\n");
    sortList(&head);

    return 0;
}
