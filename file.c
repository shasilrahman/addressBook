#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("contacts.csv","w");//to open a file, if file not present creating a file
    int i;
    fprintf(fptr,"#%d\n",addressBook->contactCount);//to store the number of contact present into the file
    for(i=0;i<addressBook->contactCount;i++)//to store the contact into the file
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("contacts.csv","r");//to open the file
    int i;
    fscanf(fptr,"#%d\n",&addressBook->contactCount);//to read how many contacts are present in the file
    for(i=0;i<addressBook->contactCount;i++)//to read the contacts in the file
    {
        fscanf(fptr," %[^,], %[^,], %[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}
