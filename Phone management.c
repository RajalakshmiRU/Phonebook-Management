#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
struct date{
	int dd;
	int mm;
	int yyyy;
};
struct details{
	char name[25];
	char mail[100];
	struct date dob;
	char num[10];                                              
};
void menu();
void add();
void update();
void del();
void view();
void search();
int main(){
	//system("COLOR B5");
	menu();
	return 0;
}
void menu(){
	int ch;
	system("cls");
	printf("\n\t\t**********************************************************\n");
	printf("\t\t\t\tPhonebook Management System\t\t\n");
	printf("\t\t**********************************************************\n");
	while (ch!=6){
		printf("\n\t\t 1-\tAdd a contact\n\n\t\t 2-\tUpdate a contact\n\n\t\t 3-\tDelete a contact");
		printf("\n\n\t\t 4-\tView all Contacts\n\n\t\t 5-\tSearch for a contact\n\n\t\t 6-\tExit");
		printf("\n\n\t\tEnter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				add();
				break;
			case 2:
				update();
				break;
			case 3:
				del();
				break;
			case 4:
				view();
				break;
			case 5:
				search();
				break;
			default:
				exit(1);
		}
	}
}
void add(){
	system("cls");
	int flag=0,i;
	FILE *fp=fopen("phonebook.xls","r+");
	if (fp==NULL){
		fp=fopen("phonebook.xls","w");
	}
	rewind(fp);
	int result;
	struct details person,contact;
	printf("\n\t\t\t-------------Adding Records---------------\n");
	printf("\n\t\tEnter the Name: ");
	scanf("%s",person.name);
	check:
	printf("\n\t\tEnter Contact Number: ");
	scanf("%s",person.num);
	for(i=0;i<10;i++){
		if (isdigit(person.num[i])==0){
			printf("\n\n\t\tEnter a Valid Number!");
			goto check;
		}
	}
	if (strlen(person.num)<10 || strlen(person.num)>10){
		printf("\n\n\t\tEnter a Valid Number!");
		goto check;
	}
	while(!feof(fp)){
		fread(&contact, sizeof(struct details), 1, fp);
    	if (strcmp(contact.name, person.name) == 0 || strcmp(contact.num,person.num)==0){
    		printf("\n\n\t\tRecord already Available... ");
			printf("\n\n\t\t Name: %s \n\n\t\t Contact Number: %s",contact.name,contact.num);
			printf("\n\n\t\t Mail-id: %s \n\n\t\t Date Of Birth: %d-%d-%d",contact.mail,contact.dob.dd,contact.dob.mm,contact.dob.yyyy);
			flag=1;
		}
	}
	if (flag==1){
		printf("\n\n\t\t Do you want to Continue?(Y/N)");
		if (getch()=='Y' || getch()=='y'){
			printf("\n\n\t\tCreating New record...");
		}
		else{
			menu();
		}
	}
	printf("\n\t\tEnter Date of Birth: ");
	scanf("%d %d %d",&person.dob.dd,&person.dob.mm,&person.dob.yyyy);
	printf("\n\t\tEnter Mail-id : ");
	scanf("%s",person.mail);
	fseek(fp,0,SEEK_END);
	fwrite(&person,sizeof(person),1,fp);
	fclose(fp);
	printf("\n\t\tAdded Successfully...");
	printf("\n\n\t\tPress any Key to Continue...");
	getch();
	system("cls");
	menu();
}
void update(){
	system("cls");
	FILE *fp=fopen("phonebook.xls","r+");
	if (fp==NULL){
		printf("File does not exist");
		exit(0);
	}
	struct details person,nperson;
	int ch,result;
	signed int len=-sizeof(struct details);
	char name[25];
	printf("\n\t\t\t-------------Updating Records---------------\n");
	printf("\n\t\t Enter Name to update Details: ");
	scanf("%s",name);
	while(!feof(fp)){
		result=fread(&person,sizeof(struct details),1,fp);
		if(result!=0 && strcmp(person.name,name)==0){
			printf("\n\t\t The Details available are: ");
			printf("\n\n\t\t Name: %s \n\n\t\t Contact Number: %s",person.name,person.num);
			printf("\n\n\t\t Mail-id: %s \n\n\t\t Date Of Birth: %d-%d-%d",person.mail,person.dob.dd,person.dob.mm,person.dob.yyyy);
			printf("\n\n\t\tWhat do you want to update?\n\t\t 1. Name\n\t\t 2. Contact Number ");
			printf("\n\t\t 3. Mail-id \n\t\t 4. Date Of Birth \n\t\t 5.All \n\t\t Enter your choice: ");
			scanf("%d",&ch);
			switch(ch){
				case 1:
					printf("\n\t\tEnter New Name: ");
					scanf("%s",person.name);
					break;
				case 2:
					printf("\n\t\tEnter New Contact Number: ");
					scanf("%s",person.num);
					break;
				case 3:
					printf("\n\t\tEnter New Mail-id: ");
					scanf("%s",person.mail);
					break;
				case 4:
					printf("\n\t\tEnter Date of Birth(dd mm yyyy): ");
					scanf("%d %d %d",person.dob.dd,person.dob.mm,person.dob.yyyy);
					break;
				case 5:
					printf("\n\t\tEnter New Name: ");
					scanf("%s",person.name);
					printf("\n\t\tEnter New Contact Number: ");
					scanf("%s",person.num);
					printf("\n\t\tEnter New Mail-id: ");
					scanf("%s",person.mail);
					printf("\n\t\tEnter Date of Birth(dd mm yyyy): ");
					scanf("%d %d %d",person.dob.dd,person.dob.mm,person.dob.yyyy);
					break;
				default:
					printf("Invalid Choice!!");
					fclose(fp);
			}
			fseek(fp,len,SEEK_CUR);
			fwrite(&person,sizeof(struct details),1,fp);
			printf("\n\n\t\tUpdated Successfully");
			break;
		}	
	}
	printf("\n\n\t\tPress any key to Continue...");
	fclose(fp);
	getch();
	system("cls");
	menu();
}
void view(){
	system("cls");
	FILE *fp=fopen("phonebook.xls","r");
	if (fp==NULL){
		printf("File does not exist");
		exit(0);
	}
	rewind(fp);
	struct details person;
	printf("\t\t--------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t Contacts in Phonebook \t\t\n");
	printf("\t\t--------------------------------------------------------------------------\n");
	printf("\n\n\t Name \t\t\t Contact Number  \t\t Date of Birth \t\tEmail-id\n");
	while(fread(&person, sizeof(person), 1, fp)!=0 ){
		if (strcmp(person.name,"\0")!=0)
    		printf("\n\n %20s \t\t +91%10s \t\t\t   %d/%d/%d \t%30s\n",person.name,person.num,person.dob.dd,person.dob.mm,person.dob.yyyy,person.mail);
    }
    printf("\n\t\t--------------------------------------------------------------------------\n");
    fclose(fp);
    printf("\n\n\t\tPress any Key to Continue...");
    getch();
    system("cls");
  	menu();
}
void del(){
	system ("cls");
	FILE *fp=fopen("phonebook.xls","r+");
	if (fp==NULL){
		printf("File does not exist");
		exit(0);
	}
	rewind(fp);
	int record=0,result;
	char name[25];
	struct details person,blank;
	printf("\n\t\tEnter contact name: ");
	scanf("%s",name);
	while(!feof(fp)){
    	result = fread(&person, sizeof(struct details), 1, fp);
    	if(result != 0 && strcmp(name, person.name) == 0){
      		fseek(fp,-(sizeof(struct details)), SEEK_CUR);
      		fwrite(&blank,sizeof(struct details),1,fp);
      		printf("\n\n\t\tRecords Deleteted Successfully...");
      		break;
    	}
  	}
	printf("\n\n\t\tPress any key to Continue...");
	fclose(fp);
	getch();
	system("cls");
	menu();
}
void search(){
	system("cls");
	FILE *fp=fopen("phonebook.xls","r");
	if (fp==NULL){
		printf("File not found");
		exit(0);
	}
	struct details person;
	int ch,result;
	char name[25],let,num[10];
	printf("\n\t\t\t-------------Searching Records---------------\n");
	printf("\n\n\t\t1.Search by Name \n\n\t\t2.Search by (starting)Letter: \n\n\t\t3.Search by Number: ");
	printf("\n\n\t\tEnter your Choice: ");
	scanf("%d",&ch);
	switch(ch){
		case 1:
			printf("\n\n\t\tEnter Name: ");
			scanf("%s",name);
			while (!feof(fp)){
				result=fread(&person,sizeof(struct details),1,fp);
				if(result!=0 && strcmp(person.name,name)==0){
					printf("\n\n\t\t Name: %s \n\n\t\t Contact Number: %s",person.name,person.num);
					printf("\n\n\t\t Mail-id: %s \n\n\t\t Date Of Birth: %d-%d-%d",person.mail,person.dob.dd,person.dob.mm,person.dob.yyyy);
				}
			}
			break;
		case 2:
			printf("\n\n\t\tEnter First Letter: ");
			let=getch();
			printf("%c",let);
			printf("\n\n\t Name \t\t\t Contact Number  \t\t Date of Birth \t\tEmail-id\n");
			while (!feof(fp)){
				result=fread(&person,sizeof(struct details),1,fp);
				if(result!=0 && person.name[0]==let){
					printf("\n\n %20s \t\t +91%10s \t\t\t   %d/%d/%d \t%30s\n",person.name,person.num,person.dob.dd,person.dob.mm,person.dob.yyyy,person.mail);	
				}
			}
			break;
		case 3:
			printf("\n\n\t\tEnter Contact Number: ");
			scanf("%s",num);
			while (!feof(fp)){
				result=fread(&person,sizeof(struct details),1,fp);
				if(result!=0 && strcmp(person.num,num)==0){
					printf("\n\n\t\t Name: %s \n\n\t\t Contact Number: %s",person.name,person.num);
					printf("\n\n\t\t Mail-id: %s \n\n\t\t Date Of Birth: %d-%d-%d",person.mail,person.dob.dd,person.dob.mm,person.dob.yyyy);
				}
			}
			break;
		default:
			printf("\n\n\t\tInvalid Choice!!");
	}
	printf("\n\n\t\tPress any key to Continue...");
	fclose(fp);
	getch();
	system("cls");
	menu();
}
