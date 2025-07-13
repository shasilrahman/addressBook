/*
name:shasil rahman
date:15/04/2025
discription:a project to create an addressbook where we can create,list,delete,search and edit the contacts
input: 
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 1
CREATE CONTACT
Enter the name : shasil
Enter the number : 9947164703
Enter the email id : npshasi38@gmail.com
output:
Contact saved successfully.    contact is saved inside file
*/
#include <stdio.h>
#include <unistd.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    do {
        printf("\nAddress Book Menu:\n");//display the menu to select what we want to do
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                int i;
                for(i=0; i<100; i++)
                {
                    printf("Saving and Exiting......%d%%\r", i);
                    usleep(20000);
                    fflush(stdout);
            
                }
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
