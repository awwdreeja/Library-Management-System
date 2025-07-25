#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
};

// Function declarations
void addBook();
void viewBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;

    while (1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Add book to file
void addBook() {
    struct Book b;
    FILE *fp = fopen("library.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &b.id);
    getchar(); // clear newline

    printf("Enter book title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);

    printf("Book added successfully.\n");
}

// View all books
void viewBooks() {
    struct Book b;
    FILE *fp = fopen("library.txt", "r");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- List of Books ---\n");
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        printf("ID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
    }

    fclose(fp);
}

// Search a book by ID
void searchBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.txt", "r");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id == id) {
            printf("Book Found:\nID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book with ID %d not found.\n", id);

    fclose(fp);
}

// Delete book by ID
void deleteBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id == id) {
            found = 1;
            continue;
        }
        fwrite(&b, sizeof(struct Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("Book deleted successfully.\n");
    else
        printf("Book with ID %d not found.\n", id);
}