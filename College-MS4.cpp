#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
} Contact;

typedef struct Node {
    Contact contact;
    char color;
    struct Node *left, *right, *parent;
} Node;

Node* createContactNode(Contact contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->color = 'R';
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void rotateLeft(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixRedBlackTree(Node** root, Node* z) {
    while (z->parent != NULL && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rotateRight(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

void insertContact(Node** root, Contact contact) {
    Node* z = createContactNode(contact);
    Node* y = NULL;
    Node* x = *root;
    while (x != NULL) {
        y = x;
        if (strcmp(z->contact.name, x->contact.name) < 0)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (strcmp(z->contact.name, y->contact.name) < 0)
        y->left = z;
    else
        y->right = z;
    fixRedBlackTree(root, z);
}

Node* searchContact(Node* root, char name[]) {
    Node* x = root;
    while (x != NULL) {
        int cmp = strcmp(name, x->contact.name);
        if (cmp == 0)
            return x;
        else if (cmp < 0)
            x = x->left;
        else
            x = x->right;
    }
    return NULL;
}

void printContact(Contact contact) {
    printf("Name: %s\n", contact.name);
    printf("Phone: %s\n", contact.phone);
    printf("Email: %s\n", contact.email);
    printf("Address: %s\n", contact.address);
    printf("-------------------\n");
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printContact(root->contact);
        inorderTraversal(root->right);
    }
}

void saveContactsToFile(Node* root, FILE* file) {
    if (root != NULL) {
        fwrite(&root->contact, sizeof(Contact), 1, file);
        saveContactsToFile(root->left, file);
        saveContactsToFile(root->right, file);
    }
}

void loadContactsFromFile(Node** root, FILE* file) {
    Contact contact;
    while (fread(&contact, sizeof(Contact), 1, file) == 1) {
        insertContact(root, contact);
    }
}

void getContactDetails(Contact *contact) {
    printf("Enter name: ");
    fgets(contact->name, 50, stdin);
    contact->name[strcspn(contact->name, "\n")] = '\0';  // Remove the newline character

    printf("Enter phone: ");
    fgets(contact->phone, 15, stdin);
    contact->phone[strcspn(contact->phone, "\n")] = '\0';

    printf("Enter email: ");
    fgets(contact->email, 50, stdin);
    contact->email[strcspn(contact->email, "\n")] = '\0';

    printf("Enter address: ");
    fgets(contact->address, 100, stdin);
    contact->address[strcspn(contact->address, "\n")] = '\0';
}

int main() {
    Node* root = NULL;

    // Load contacts from file
    FILE* file = fopen("contacts.dat", "rb");
    if (file != NULL) {
        loadContactsFromFile(&root, file);
        fclose(file);
    }

    char option;
    do {
        printf("Do you want to (a)dd a new contact or (s)earch for a contact? or (e)xit (a/s/e): ");
        option = getchar();
        getchar(); // Consume the newline character
		if (option == 'e') {
			break;
		} else if (option == 'a' || option == 'A') {
            Contact contact;
            getContactDetails(&contact);
            insertContact(&root, contact);

            // Save contacts to file
            file = fopen("contacts.dat", "wb");
            if (file != NULL) {
                saveContactsToFile(root, file);
                fclose(file);
            }
        } else if (option == 's' || option == 'S') {
            char searchName[50];
            printf("Enter name to search: ");
            fgets(searchName, 50, stdin);
            searchName[strcspn(searchName, "\n")] = '\0';

            Node* foundContact = searchContact(root, searchName);
            if (foundContact != NULL) {
                printf("\nContact found!\n");
                printContact(foundContact->contact);
            } else {
                printf("\nContact not found!\n");
            }
        } else {
            printf("Invalid option. Please enter 'a' to add a contact or 's' to search for a contact.\n");
        }
    } while (option == 'a' || option == 's');

    return 0;
}
