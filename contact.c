#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int intex[10];
int intexcount;
int contactfound=0;
int validate_name(char name[])//a function to validate the given name
{
    int len,i,count=0;
    len=strlen(name);
    for(i=0;i<len;i++)
    {
      if(name[i]>='a'&&name[i]<='z'||name[i]>='A'&&name[i]<='Z'||name[i]==' '||name[i]>='0'&&name[i]<='9')
      {
        count++;
      }
    }
    if(count==len)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int validate_num(char number[],AddressBook *addressBook)//to check if the given number is valid or not
{
    int len,i,count=0;
    len=strlen(number);
    if(len==10)
    {
      for(i=0;i<len;i++)
     {
        if(number[i]>='0'&& number[i]<='9')
        {
            count++;
        }
     }
    }
    else
    {
        return 0;
    }
   return count==10;
}
int validate_email(char email[],AddressBook *addressBook)//to check if the given email is valid or not.
{
    int len;
    len=strlen(email);
    int atcount=0,dotcount=0,atpos,dotpos,i;
    for(i=0;i<len;i++)
    {
        if(email[i]=='@')
        {
            atcount++;
            atpos=i;
        }
        if(email[i]=='.')
        {
            dotcount++;
            dotpos=i;
        }
    }
    if(atcount!=1||dotcount<1)
    {
        return 0;
    }
    if(atpos>=len-1||atpos==0)
    {
        return 0;
    }
    if(dotpos==atpos+1||dotpos==len-1)
    {
        return 0;
    }
    for(i=0;i<len;i++)
    {
        if(!(isalnum(email[i])||email[i]!='.'||email[i]!='-'||email[i]!='_'))
        {
            return 0;
        }
    } 
    return 1;
}
void listContacts(AddressBook *addressBook, int sortCriteria) //to sort the contacts according to the criteria we want to sort
{
    switch(sortCriteria)
    {
        case 1:
        {
            int i,j;
            Contact temp;
            for(i=0;i<addressBook->contactCount-1;i++)//to sort the contact according to the name in accending order
            {
                for(j=0;j<addressBook->contactCount-i-1;j++)
                {
                    if(strcasecmp(addressBook->contacts[i].name,addressBook->contacts[j].name)<0)
                    {
                        temp=addressBook->contacts[i];
                        addressBook->contacts[i]=addressBook->contacts[j];
                        addressBook->contacts[j]=temp;
                    }
                }
            }
            printf("%s\t\t%s\t\t%s\n","Name","Phone","Email");//to print the sorted contact
            printf("--------------------------------------------------\n");
            for(i=0;i<addressBook->contactCount;i++)
            {
                printf("%s\t\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        }
        case 2:
        {
            int i,j;
            Contact temp;
            for(i=0;i<addressBook->contactCount-1;i++)//to sort the contact according to number in accending order.
            {
                for(j=0;j<addressBook->contactCount-i-1;j++)
                {
                    if(strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                    {
                        temp=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=temp;
                    }
                }
            }
            printf("%s\t\t%s\t\t%s\n","Name","Phone","Email");//to print the sorted contact
            printf("--------------------------------------------------\n");
            for(i=0;i<addressBook->contactCount;i++)
            {
                printf("%s\t\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break; 
        }
        case 3:
        {
            int i,j;
            Contact temp;
            for(i=0;i<addressBook->contactCount-1;i++)//to sort the contact according to email in accending order.
            {
                for(j=0;j<addressBook->contactCount-i-1;j++)
                {
                    if(strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                    {
                        temp=addressBook->contacts[j];
                        addressBook->contacts[j]=addressBook->contacts[j+1];
                        addressBook->contacts[j+1]=temp;
                    }
                }
            }
            printf("%s\t\t%s\t\t%s\n","Name","Phone","Email");//to print the sorted contact
            printf("--------------------------------------------------\n");
            for(i=0;i<addressBook->contactCount;i++)
            {
                printf("%s\t\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        }
    }
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}
void createContact(AddressBook *addressBook)//to create contacts
{   
    int i;
    printf("CREATE CONTACT\n");
        char ch;
        int label1;
        label1:
        char name[20];
        printf("Enter the name : ");//read the name 
        scanf(" %[^\n]",name);
        int res1=validate_name(name);//to check if the name is valid or not
        if(res1)
        {
            int label2;
            label2:
            char number[20];
            printf("Enter the phone number : ");//read the number
            scanf(" %[^\n]",number);
            int res2=validate_num(number,addressBook);//to check if the number is valid or not
            for(i=0;i<addressBook->contactCount;i++)//to check if the number is already present
            {
                if(strcmp(addressBook->contacts[i].phone,number)==0)
                {
                    printf("Error:number already exists,");
                    res2=0;
                }
            }
            if(res2)
            {
                int res3;
                int label3;
                label3:
                char email[30];
                printf("Enter the email id : ");//to read email
                scanf(" %[^\n]",email);
                res3=validate_email(email,addressBook);//to check email is valid or not
                for(i=0;i<addressBook->contactCount;i++)//to check if email is already present
                {
                    if(strcmp(addressBook->contacts[i].email,email)==0)
                    {
                        printf("Error:Email already exists,");
                        res3=0;
                    }
                }
                if(res3)
                {
                    //if everythig is valid and read store everything in addressbook
                    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
                    strcpy(addressBook->contacts[addressBook->contactCount].phone,number);
                    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
                    addressBook->contactCount++;
                    printf("%s\t\t%s\t%s\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email);
                    printf("Contact saved succesfully");

                }
                else
                {
                    printf("Enter a valid email\n");
                    goto label3;
                }
            }
            else
            {
                printf("Enter a valid number\n");
                goto label2;
            }
        }
        else
        {
            printf("Enter a valid name\n");
            goto label1;
        } 
}
void searchContact(AddressBook *addressBook) //to search contact according to a criteria given
{
    int i,option;
    printf("SEARCH CONTACT\n");
    printf("How do you want to search?\n");//to select the criteria how you want to search
    printf("1.Name\n2.Phone Number\n3.Mail id\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1://to search according to name
        {
            char name[20];
            int label;
            label:
            printf("Enter the name:");//read the name
            scanf(" %[^\n]",name);
            int res=validate_name(name);//validate the name
            int j=0;
            int count=0;
            if(res)
            {
                
                for(i=0;i<addressBook->contactCount;i++)//searching the contact in addressbook according to the name given
                {
                    if(strstr(addressBook->contacts[i].name,name))
                    {
                        printf("%d.%s\t%s\t%s\n",j+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        intex[j]=i;
                        intexcount++;
                        j++;
                        count++;
                        contactfound=1;
                    }
                }
                if(count==0)
                {
                    printf("contact not found\n");
                }
            }
            else
            {
                printf("Enter a valid name\n");
                goto label;
            }
            break;
        }
        case 2://search the contact according to number
        {
            char phone[20];
            int label2;
            label2:
            printf("Enter the Number:");//reading the number
            scanf(" %[^\n]",phone);
            int res=validate_num(phone,addressBook);//validating the number
            int j=0;
            int count=0;
            if(res)
            {
                for(i=0;i<addressBook->contactCount;i++)//searching the contact inside the addressbook according to the number given
                {
                    if(!(strcmp(addressBook->contacts[i].phone,phone)))
                    {
                        printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        intex[j]=i;
                        count++;
                        contactfound=1;
                    }  
                }
                if(count==0)
                {
                    printf("contact not found!");

                }
            }
            else
            {
                printf("Enter a valid number\n");
                goto label2;
            }
            break;
        }
        case 3://to search the contact according to email
        {
            char email[20];
            int label3;
            label3:
            printf("Enter the Email:");//reading the email
            scanf(" %[^\n]",email);
            int res=validate_email(email,addressBook);//validating the email
            int j=0;
            int count=0;
            if(res)
            {
                for(i=0;i<addressBook->contactCount;i++)//searching the contact in addressbook according to the given email
                {
                    if(!(strcmp(addressBook->contacts[i].email,email)))
                    {
                        printf("%s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        intex[j]=i;
                        count++;
                        contactfound=1;
                    }
                }
                if(count==0)
                {
                    printf("contact not found!");
                }
            }
            else
            {
                printf("Enter a valid email\n");
                goto label3;
            }
            break;
        }
        default:
        {
            ("Enter valid option");
            break;
        }
    }
}
void editContact(AddressBook *addressBook)//to edit a contact 
{
    intexcount=0;
    int select=0;
    int option;
    printf("Edit Contact\n");
    searchContact(addressBook);//to search the contact which has to be editted
    if(intexcount>1)//if contact listed is more than 1 select which should be editted
    {
      printf("Which contact should be editted?:");
      scanf("%d",&select);
      select--;
    }
    printf("What should be editted?\n");//read which has to be editted
    printf("1.Name\n2.Phone\n3.Email\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1://to edit the name
        {
            char name[20];
            printf("Enter the name to be replaced:\n");//read the name
            scanf(" %[^\n]",name);
           if(validate_name(name))//validate the name
           {
            strcpy(addressBook->contacts[intex[select]].name,name);//replacing the name which is given
            printf("Contact successfully saved");
            break;
           }
           else
           {
            printf("Enter a valid name");
           }
           break;
        }
        case 2://to replace the number
        {
            char phone[20];
            printf("Enter the number to be replaced:\n");//reading the number
            scanf(" %[^\n]",phone);
            int res=validate_num(phone,addressBook);//validating the number
            for(int i=0;i<addressBook->contactCount;i++)//checkimg if the number is already present
            {
                if(strcmp(addressBook->contacts[i].phone,phone)==0)
                {
                    printf("number already exists ");
                    res=0;
                    break;
                }
            }
            if(res)
            {
            strcpy(addressBook->contacts[intex[select]].phone,phone);//replacing the number given by user
            printf("Contact successfully saved");
            break;
            }
            else
            {
              printf("Enter a valid number");
            }
            break;
        }
        case 3://to edit the email
        {
            char email[20];
            printf("Enter the email to be replaced:\n");//reading the email from user
            scanf(" %[^\n]",email);
            int res=validate_email(email,addressBook);//validating the email
            for(int i=0;i<addressBook->contactCount;i++)//checking if the email is already present in the addressbook
            {
                if(strcmp(addressBook->contacts[i].email,email)==0)
                {
                    printf("number already exists ");
                    res=0;
                    break;
                }
            }
            if(res)
            {
            strcpy(addressBook->contacts[intex[select]].email,email);//replacing the email given by the user
            printf("Contact successfully saved");
            break;
            }
            else
            {
              printf("Enter a valid email");
            }
            break;
        }
        default:
        {
            printf("Enter a valid option");
        }
    } 
}
void deleteContact(AddressBook *addressBook)//to delete a contact from addressbook
{
    intexcount=0;
    int select;
    int i;
    printf("Delete Contact\n");
    searchContact(addressBook);//to search the contact which has to be deleted
    if(intexcount>1)//if multiple contacts found,asking which contact to be deleted 
    {
      printf("Which contact should be deleted?:");
      scanf("%d",&select);
      select--;
    }
    else
    {
        select=0;
    }
    if(contactfound)
    {
    printf("Do you want to proceed?(Y/N):");//confirming if you want to delete
    char ch;
    scanf(" %c",&ch);
    if(ch == 'y'||ch == 'Y')
    {
    for(i=intex[select];i<addressBook->contactCount-1;i++)//removing the contact from addressbook
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully\n");
    }
    else
    {
        printf("Deletion canceled\n");
    }
}
}