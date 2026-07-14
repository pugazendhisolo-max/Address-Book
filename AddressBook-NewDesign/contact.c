#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
//This fuction is used to validate name
int valid_name(char name[])
{
	for(int i=1;name[i]!='\0';i++){
		if(!isalpha(name[i])&& name[i]!=' ')
		{
			return 0;
		}
	}
	return 1;
}
// This function is used to validate phone
int valid_phone(AddressBook *addressBook,char phone[],int index)
{
	int len=strlen(phone);
	if(len!=10){
		printf("!! Enter the 10 digit Numbers !!");
		return 0;
	}
	if(phone[0]<'6'||phone[0]>'9'){
		printf("!! Enter number is starting form 6,7,8 & 9 !!");
		return 0;
	}
	for(int i=0;i<len;i++){
		if(!isdigit(phone[i])){
			printf("!! Enter the contain digits !!");
			return 0;
		}
	}
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(i==index)
		{continue;
		}
		if(strcmp(addressBook->contacts[i].phone,phone)==0){
			printf(" !! This number alredy exsit !!");
			return 0;
		}
	}
	return 1;
}
//This function is used to validate email
int valid_email(AddressBook *addressBook,char pemail[],int index)
{
	for(int i=1;pemail[i]!='\0';i++)
	{
		if(!islower(pemail[i]) && isalpha(pemail[i]) )
		{
			printf("!! Error: Only lower case allowed in Email !!\n");
			return 0;
		}
	}
//	for(int i=0;pemail[i]!='\0';i++)
//	{
		if(isdigit(pemail[0]))
		{
			printf("!! Error: Only alphabets only allowed in Email !!\n");
			return 0;
		}
//	}
	for(int i=0;i<=addressBook->contactCount;i++)
	{
                if(i==index){
                    continue;
                }
		if(strcmp(addressBook->contacts[i].email,pemail)==0)
		{
			printf("!! Already is Email are Exist !!\n");
			return 0;
		}
	}
	int count=0;
	char *pat=strchr(pemail,'@');
	char *temppat=pat;
	char *pcom=strstr(pemail,".com");
	char *tempcom=pcom;
	while(temppat!=NULL)
	{
		count++;
		temppat=strchr(temppat+1,'@');
	}
	if(count !=1)
	{
		printf("Email format error: exactly one '@' is required.\n");
		return 0;
	}
	int comcount=0;
	while(tempcom !=NULL)
	{
		comcount++;
		tempcom=strstr(tempcom+4,".com");
	}
	if(comcount !=1)
	{
		printf("Email format error: exactly one '.com' is required.\n");
		return 0;
	}
	if(pat>pcom)
	{
		printf("Invalid format: '.com' should come after '@'.\n");
		return 0;
	}
	if(pat+1==pcom)
	{
		printf("Invalid format: domain name is required (example: user@domain.com)\n");
		return 0;
	}
	for(char *p=pat+1;p<pcom;p++)
	{
		if(isdigit(*p))
		{
			printf("Email error: domain should contain only letters.\n");
			return 0;
		}
	}
	if(strcmp(pcom,".com")!=0)
	{
		printf("Email must end with '.com'\n");
		return 0;
	}
        return 1;
}


//This function is used to search a name
int namesearch(AddressBook *addressBook,char pname[])
{
	int index[50];
	int puga=0;
	printf("\n%-5s | %-20s | %-15s | %-25s\n", "S.No", "Name", "Phone", "Email");
	printf("--------------------------------------------------------------------\n");

	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(addressBook->contacts[i].name,pname)==0)
		{
			index[puga]=i;	
			printf("%-5d | %-20s | %-15s | %-25s\n",i+1,addressBook->contacts[i].name,
					addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
			puga++;
		}
	}
	if(puga==0)
	{
		printf("No contact found with name %s\n",pname);
		return -1;
	}
	if(puga==1)
	{
		return index[0];

	}
	int choice;
	printf("\nMultiple contacts found. Enter s.no to select : ");
	scanf("%d",&choice);
	if(choice >=1 && choice <=puga){
		return index[choice - 1];
	}
	return -1;
}
//This function is used search a phone number
int phonesearch(AddressBook *addressBook,char pphone[])
{
	for(int i=0;i<addressBook->contactCount;i++){
		if(strcmp(addressBook->contacts[i].phone,pphone)==0){
			printf("\nContact Found!\n");
			printf("\n%-5s | %-20s | %-15s | %-25s\n", "S.No", "Name", "Phone", "Email");
			printf("--------------------------------------------------------------------\n");

			printf("%-5d | %-20s | %-15s | %-25s\n", i+1,addressBook->contacts[i].name,										   addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
			return i;

		}
	}
	printf("The phone number %s is not found!!",pphone);
	return -1;


}
//This function is used to  search a mail
int mailsearch(AddressBook *addressBook,char pmail[])
{
	int mflag=0;
	for(int i=0;i<addressBook->contactCount;i++)
	{
		if(strcmp(addressBook->contacts[i].email,pmail)==0)
		{
			printf("\nContact Found!\n");
			printf("\n%-5s | %-20s | %-15s | %-25s\n", "S.No", "Name", "Phone", "Email");
			printf("--------------------------------------------------------------------\n");
			printf("%d.Name : %s | phone : %s | Email : %s\n", i+1,
					addressBook->contacts[i].name,
					addressBook->contacts[i].phone,
					addressBook->contacts[i].email);

			return i;

		}
	}
	printf("The %s is not found!!",pmail);
	return -1;
}
void listContacts(AddressBook *addressBook) 
{	
	if(addressBook->contactCount==0)
	{
		printf("!! contact is Empty \n");
		return;
	}
	printf("\n%-5s,|%-20s |%-15s |%-25s\n","S.NO","NAME","PHONE","EMAIL");
	printf("__________________________________________________________\n");
	for(int i=0;i<addressBook->contactCount;i++)
	{        printf("%-5d |%-20s |%-15s |%-25s\n",i+1,addressBook->contacts[i].name,
			addressBook->contacts[i].phone,
			addressBook->contacts[i].email);
	}
	printf("____________________________________________________________\n");
}

void initialize(AddressBook *addressBook) {
	addressBook->contactCount = 0;


	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); //Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	char pugalname[50];
	char pugalphone[20];
	char pugalmail[50];
	if(addressBook->contactCount>=MAX_CONTACTS)
	{
		printf(" Error:Addressbook is FULL !!"); 
		return;
	}
	printf("\n-------creating new contact ---------\n");
	int flag=0;
	for(int i=1;i<=3;i++){
		printf("Enter the name you have %d/3 attempt:",i);
		scanf(" %[^\n]",pugalname);
		if(valid_name(pugalname)==0)
		{
			printf("Name can't be Empty!!");
		}
		if(valid_name(pugalname))
		{flag=1;
			break;
		}
		else
		{
			printf("!!Invalid:Only alphabets character are allowed!!\n");
		}
	}
	if(!flag)
	{
		printf(" !! Too many attempts: Try later!!");
		return;
	}	
	int phoneflag=0;
	for(int i=1;i<=3;i++)
	{
		printf("Enter the phone number you have %d/3 attempts:",i);
		scanf(" %s",pugalphone);
		if(valid_phone(addressBook,pugalphone,-1))
		{
			phoneflag=1;
			break;
		}
		}
	if(!phoneflag)
	{
		printf("!! Too many attempts: Try later!!");
		return;
	}	
	int mailflag=0;
	for(int i=1;i<=3;i++)
	{
		printf("Enter the Email you have %d/3 attempts:",i);
		scanf(" %s",pugalmail);
		if(valid_email(addressBook,pugalmail,-1))
		{
			mailflag=1;
			break;
		}
			}
	if(!mailflag)
	{
		printf(" !! Too many attempts: Try later !!\n");
		return;
	}
	int i=addressBook->contactCount;
	strcpy(addressBook->contacts[i].name,pugalname);
	strcpy(addressBook->contacts[i].phone,pugalphone);
	strcpy(addressBook->contacts[i].email,pugalmail);
	addressBook->contactCount++;
	printf("contact created sucessfully");
}

// This function is used to search a contact
int searchContact(AddressBook *addressBook) 
{
	if(addressBook->contactCount==0)
	{
		printf("AddressBook is Empty! Nothing to search !!");
		return -1;
	}
	char name[50];
	char phone[20];
	char mail[50];
	int choice;
	printf("choose what you want to search \n");
	printf("1.name\n 2.phone\n 3.email\n");
	printf("Enter the choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Enter the Name to search: ");
			scanf(" %[^\n]",name);
			return namesearch(addressBook,name);
			
		case 2:
			printf("Enter the phone to search: ");
			scanf(" %[^\n]",phone);
			return phonesearch(addressBook,phone);
			
		case 3:
			printf("Enter the mail to search: ");
			scanf(" %[^\n]",mail);
			return mailsearch(addressBook,mail);
			
		default:
			printf("Invalid choices!!");
			return-1;
	}
}


void editContact(AddressBook *addressBook)
{	char edit[50];
	int index[50];
	int count=0;
	int choice;
	if(addressBook->contactCount==0){
		printf("Addressbook is empty");
		return;
	}
	int indexpugal=searchContact(addressBook);
	if(indexpugal==-1)
	{
		printf("contact not found.\n");
		return;			
	}
	printf("contact found ! editing....%s\n",addressBook->contacts[indexpugal].name);
	printf("1. NAME\n 2. PHONE\n 3. EMAIL\n 4. EXIT\n");
	printf("PLEASE SELECT THE CHOICE: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
                        {
			char pugalname[50];
			int nflag=0;
			for(int i=1;i<=3;i++)
			{
				printf("ENTER THE NAME : YOU HAVE %d/3 ATTEMPTS : \n",i);
				scanf(" %[^\n]",pugalname);
				if(valid_name(pugalname))
				{
					if(strcpy(addressBook->contacts[indexpugal].name,pugalname)){
						nflag=1;
						break;
					}
					else{
						printf("Error:Enter Only alphabits");
					}
				}
			}
			if(nflag)
			{
				printf("CONTACTS CREATED SUCCESSFULLY");
			}
			else{
				printf("TOO MANY ATTEMPTS : TRY AGAIN!!");
			}
                         break;
                        }
		case 2:
			{
				char pugalphone[20];
				int pflag=0;
				for(int i=1;i<=3;i++)
				{
					printf("ENTER THE PHONE :YOU HAVE %d/3 ATTEMPTS : \n",i);
					scanf(" %[^\n]",pugalphone);
					if(valid_phone(addressBook,pugalphone,indexpugal))
					{
						if(strcpy(addressBook->contacts[indexpugal].phone,pugalphone))
						{
							pflag=1;
							break;
						}
						else{
							printf("Error: Enter only digits");
						}
					}
				}
				if(pflag)
				{
					printf("CONTACTS CREATED SUCCESSFULLY");
				}
				else{
					printf("TOO MANY ATTEMPTS : TRY AGAIN !!");
				}
                                 break;
			}
		case 3:
			{
				char pugalemail[50];
				int eflag=0;
				for(int i=1;i<=3;i++)
				{
					printf("ENTER THE EMAIL : YOU HAVE %d/3 ATTEMPTS : \n",i);
					scanf(" %[^\n]",pugalemail);
					if(valid_email(addressBook,pugalemail,indexpugal))
					{
						if(strcpy(addressBook->contacts[indexpugal].email,pugalemail))
						{
							eflag=1;
							break;
						}
						else{
							printf("Error: Enter only email ");
						}
					}
				}
				if(eflag)
				{
					printf("CONTACTS CREATED SUCCESSFULLY");
				}
				else{
					printf("TOO MANY ATTEMPTS : TRY AGAIN !!");
				}
                                break;
			}
		case 4:
			return;

		default:
			printf("INVALID CHOICE");
			return;

	}
}

void deleteContact(AddressBook *addressBook)
{
	printf("CURRENT CONTACT FOUND %d\n",addressBook->contactCount);
	char name[50];
	int index[50];
	int count=0;
	if(addressBook->contactCount==0){
		printf("ADDDRESSBOOK IS EMPTY\n");
		return;
	}
	int indexpugal= searchContact(addressBook);
	if(indexpugal == -1)
	{
		printf("\ncontact not found\n");
		return;
	}
	char confirm;
	printf("Are you sure you want to delete %s? (y/n):",addressBook->contacts[indexpugal].name);
	scanf(" %c",&confirm);
	if(confirm == 'Y' || confirm == 'y')
	{
		for(int i=indexpugal;i<addressBook->contactCount-1;i++)
		{
			addressBook->contacts[i]=addressBook->contacts[i+1];
		}
		addressBook->contactCount--;
		printf("CONTACTS  DELETE SUCCESSFULLY");
	}else{
		printf("Deleted operation aborted\n");
	}
}




