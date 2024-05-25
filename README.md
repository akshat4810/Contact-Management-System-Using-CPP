# Contact Management System

This project is a simple contact management system implemented in C using a Red-Black Tree data structure for efficient storage and retrieval. The application allows users to add new contacts, search for contacts by name, and store the contact information in a file for persistence.

## Features
- **Add New Contact:** Users can add new contacts with details such as name, phone number, email, and address.
- **Search Contact by Name:** Users can search for contacts by name, and the application will display the contact details if found.
- **File Persistence:** Contacts are stored in a file (`contacts.dat`) for persistence across sessions. The application loads the contacts from the file on startup and saves any new contacts before exiting.
- **Red-Black Tree Implementation:** The contacts are stored in a Red-Black Tree, ensuring efficient insertion, deletion, and search operations.

## Available Prompts
- To add a new contact, choose the option 'a' and enter the contact details when prompted.
- To search for a contact by name, choose the option 's' and enter the name when prompted.
- To exit the program, choose the option 'e' when asked if you want to continue.

## Code Overview
- **Contact Structure:**
  The `Contact` structure holds the details for each contact, including name, phone number, email, and address.
- **Red-Black Tree Implementation:**
  The `Node` structure represents a node in the Red-Black Tree, which includes the contact information and pointers to the left and right children, parent, and the node color.
- **File Operations:**
  Functions to save contacts to a file and load contacts from a file are provided to ensure data persistence.
- **User Interaction:**
  The main loop of the program allows the user to add new contacts or search for contacts by name, with prompts guiding the user through each operation.

## Example

```bash
Do you want to (a)dd a new contact or (s)earch for a contact? or (e)xit (a/s/e): a
Enter name: John Doe
Enter phone: 1234567890
Enter email: john.doe@example.com
Enter address: 123 Elm Street

Do you want to (a)dd a new contact or (s)earch for a contact? or (e)xit (a/s/e): s
Enter name to search: John Doe

Contact found!
Name: John Doe
Phone: 1234567890
Email: john.doe@example.com
Address: 123 Elm Street
-------------------
Do you want to (a)dd a new contact or (s)earch for a contact? or (e)xit (a/s/e): e
