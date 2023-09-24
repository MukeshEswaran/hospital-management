#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
FILE *fp;
struct patient_details
{
	int id;
	int discharge;
	char disease[10],doctor[20],gen,BG[30],STD[50],C19[30],Drug[30];
	struct
	{
		char first_name[20];
		char middle_name[20];
		char surname[20];
	}patient_name;
	int age;
	struct
	{
		int month_no;
		int day;
		int year;
	}date_of_entry;
	int room_no;
	struct
	{
		int date;
		int month_no;
		int year;
	}date_of_birth;
}patient;
struct node
{
	struct patient_details patient;
	struct node *next;
};
int ID=1000,room[9];
struct node *start=NULL;
struct node *insert_details(struct node *start);
struct node *change_details(struct node *start);
struct node *display_details(struct node *start);
void display_list(struct node *start);
void display(struct node *start);
void diagnosis();
int sort_by_month(struct node *start);
void sort_by_name(struct node *start);
void sort_by_id(struct node *start);
void swap_data(struct node *ptr1, struct node *ptr2);
int main()
{
	int choice,i;
	clrscr();
	for(i=0;i<10;i++)
		room[i]=-1;
	do
	{
		printf("\n************************* Welcome to Hangover Hospital *************************");
		printf("\n1.Make a new entry of a patient.\n2.Display details of a patient.\n3.Diagnosis.\n4.Change Patient's Details.\n5.Exit\nEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			start=insert_details(start);
			break;
			case 2:
			start=display_details(start);
			break;
			case 3:
			diagnosis();
			break;
			case 4:
			start=change_details(start);
			case 5:
			printf("\n******* Closing application,Thank You for using. ******* \n");
			break;
			default:
			printf("\nPlease enter valid option ");
		}
	}while(choice!=5);
    return 0;
}
struct node *insert_details(struct node *start)
{

	struct node *new_node,*ptr;
	int d,m,yr,ag,yrb,mb,db,flag=0,i=0,roomno=0;
	char gend,f_name[20],l_name[20],doct[20],bg[30],std[50],drug[30],c19[30];
	new_node=(struct node *)malloc(sizeof(struct node));
	printf("\n\n\t\t\t\tROOMS\n\n");
	while(i<10)
	{
		if(room[i]==-1)
		{
			printf("Room number %d is empty.\n",i+1);
			flag=1;
		}
		i++;
	}
	if(flag!=1)
		printf("\nSorry,there are no Rooms available at this time.\n");
	else
	{
		FILE *fp;

		fp=fopen("Patient.csv","w+");
		fprintf(fp,"DOE,MOE,YOE,F.NAME,L.NAME,AGE,GENDER,DD,MM,YY,Bl.Grp,C19,STD,Drug,D.Name,P.ID,R.No");
		printf("\n\nDay of entry: ");
		scanf("%d",&d);

		printf("Month of entry: ");
		scanf("%d",&m);

		printf("Year of entry: ");
		scanf("%d",&yr);

		printf("Patient's First name: ");
		scanf("%s",&f_name);

		printf("Patient's Last name: ");
		scanf("%s",&l_name);

		printf("Patient's age: ");
		scanf("%d",&ag);

		printf("Patient's Gender(only initial): ");
		scanf(" %c",&gend);

		printf("Patient's date of birth: ");
		scanf("%d",&db);

		printf("Patient's month number of birth: ");
		scanf("%d",&mb);

		printf("Patient's year of birth: ");
		scanf("%d",&yrb);

		printf("Patient's Blood Group: ");
		scanf("%s",&bg);

		printf("Patient's Diagnosis on COVID-19: ");
		scanf("%s",&c19);

		printf("Patient's Diagnosis on STD(Sexualy Transmitted Disease): ");
		scanf("%s",&std);

		printf("Patient's Diagnosis on Drug consumption(Medicines): ");
		scanf("%s",&drug);

		printf("In-charge Doctor name: ");
		scanf("%s",doct);

		printf("Patient's Generated ID: %d\n",ID);

	       //	fprintf(fp,"DOE,MOE,YOE,F.NAME,L.NAME,AGE,GENDER,DD,MM,YY,Bl.Grp,C19,STD,Drug,D.Name,P.ID,R.No")
		fprintf(fp,"\n%d,%d,%d,%s,%s,%d,%c,%d,%d,%d,%s,%s,%s,%s,%s,%d,%d",d,m,yr,f_name,l_name,ag,gend,db,mb,yrb,bg,c19,std,drug,doct,ID,roomno);
		fclose(fp);
		do
		{
			printf("Enter the Room Number for the patient: ");
			scanf("%d",&roomno);
			if(roomno>0 && roomno<11)
			{
		if(room[roomno-1]!=-1)
		{
		    printf("The Room is occupied.Please select from the given Room Number(s) only\n");
		    i=1;
		}
		else
		{
		    new_node->patient.room_no=roomno;
		    room[roomno-1]=new_node->patient.id;
		    i=0;
		}
			}
			else
			{
		printf("\n**** Invalid Room Number. Please select again. ****\n");
		i=1;
		}	 clrscr();
		}while(i);
		new_node->patient.id=ID;
		strcpy(new_node->patient.patient_name.first_name,f_name);
		strcpy(new_node->patient.patient_name.surname,l_name);
		new_node->patient.date_of_entry.month_no=m;
		new_node->patient.date_of_entry.day=d;
		new_node->patient.date_of_entry.year=yr;
		new_node->patient.age=ag;
		new_node->patient.gen=gend;
		new_node->patient.discharge=0;
		new_node->patient.date_of_birth.date=db;
		new_node->patient.date_of_birth.month_no=mb;
		new_node->patient.date_of_birth.year=yrb;
		strcpy(new_node->patient.BG,bg);
		strcpy(new_node->patient.C19,c19);
		strcpy(new_node->patient.STD,std);
		strcpy(new_node->patient.Drug,drug);
		strcpy(new_node->patient.doctor,doct);
			if(start==NULL)
		{
			new_node->next=NULL;
			start=new_node;
			ID++;
		}
			else
		{
			new_node->next=NULL;
			ptr=start;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			ptr->next=new_node;
			ID++;
		}
		fwrite(&patient,sizeof(patient),1,fp);
		fclose(fp);
	}
	return start;
}
struct node *display_details(struct node *start)
{
	int choice,i=0,m;
	char n[15];
	struct node *ptr;
	ptr=start;
	if(start==NULL)
	{
		printf("***** Patient database empty! *****\n");
		return NULL;
	}
	else
	{
		while(choice!=5)
		{
			ptr=start;
			printf("\n1.Display by name \n2.Display by ID \n3.Display for a specific month.\n4.Search patient by first name\n5.Exit\n");
			printf("\nEnter a choice: ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
				sort_by_name(start);
				printf("ID\t\tName\t\tDoctor\t\tRoom No.\tStatus\n");
				while(ptr!=NULL)
				{
					display_list(ptr);
					ptr=ptr->next;
				}
				break;
				case 2:
				sort_by_id(start);
				printf("ID\t\tName\t\tDoctor\t\tRoom No.\tStatus\n");
				while(ptr!=NULL)
				{
					display_list(ptr);
					ptr=ptr->next;
				}
				break;
				case 3:
				m=sort_by_month(start);
				if(m==0)
					printf("\nNo Entry available for this month\n ");
				else
					printf("ID\t\tName\t\tDoctor\t\tRoom No.\tStatus\n");
				while(ptr!=NULL)
					{
						if(ptr->patient.date_of_entry.month_no==m)display_list(ptr);
						ptr=ptr->next;
					}
				break;
				case 4:
				printf("Enter patient name: ");
				scanf("%s",n);
				while(ptr!=NULL)
				{
					if(!(strcmp(n,ptr->patient.patient_name.first_name)))
					{
						display(ptr);
						i++;
					}
					ptr=ptr->next;
				}
				if(i==0)
					printf("Name not found.");
				break;
				case 5:
				printf("\n******* Returning to Main Menu ******* ");
				clrscr();
				break;
				default:
				printf("Invalid choice. Please enter again.");
			}
		}
	}
	sort_by_id(start);
	return start;
}
struct node *change_details(struct node *start)
{
	struct node *ptr;
	int change_id,option,status,roomno,i=0,flag=0;
	char f_name[20],l_name[20],dis[20],doct[20];
	ptr=(struct node *)malloc(sizeof(struct node));
	ptr=start;
	if(ptr==NULL)
	{
		printf("***** No details available!! Please make an entry. *****\n");
		return NULL;
	}
	else
	{
		printf("Which patient's detail is to be changed? Please enter the patient's Id: ");
		scanf("%d",&change_id);
		while(ptr!=NULL && ptr->patient.id!=change_id)
		{
			ptr=ptr->next;
		}
		if(ptr==NULL)
		{
			printf("There is no patient with such id.\n");
			free(ptr);
			return start;
		}
		else
		{
			do
			{
				printf("Which detail is to be changed?\n1.Status of the patient\t2.Name\t3.Room Number\t4.Doctor Assigned\t5.Disease acquired\t6.Exit\nEnter your option:");
			scanf("%d",&option);
				switch(option)
				{
					case 1:
					printf("Is the patient 1.Admitted or 2.Discharged ? ");
					scanf("%d",&status);
					if(status==1)
						ptr->patient.discharge=0;
					else
					{
						ptr->patient.discharge=1;
						roomno=ptr->patient.room_no;
						room[roomno-1]=-1;
					}
					break;
					case 2:
					printf("Patient's First name: ");
					scanf("%s",f_name);
					printf("Patient's Last name: ");
					scanf("%s",l_name);
					strcpy(ptr->patient.patient_name.first_name,f_name);
					strcpy(ptr->patient.patient_name.surname,l_name);
					break;
					case 3:
					while(i<10)
					{
						if(room[i]==-1)
						{
							printf("Room number %d is empty.\n",i+1);
							flag=1;
						}
						i++;
					}
					if(flag!=1)
						printf("There are no rooms empty at this time.Please try again later.\n");
					else
					{
						do
						{
							printf("Enter new Room Number for the patient:");
							scanf("%d",&roomno);
							if(room[roomno-1]!=-1)
							{
								printf("The room is occupied.Please select from the given room no.s\n");
								i=1;
							}
							else
							{
								room[ptr->patient.room_no-1]=-1;
								ptr->patient.room_no=roomno;
								room[roomno-1]=ptr->patient.id;
								i=0;
							}
						}while(i);
					}
					break;
					case 4:
					printf("In-charge Doctor name: ");
					scanf("%s",doct);
					strcpy(ptr->patient.doctor,doct);
					break;
					case 5:
					printf("\n******* Returning to Main Menu ******* \n");
					break;
					default:
					printf("Wrong choice\n");
				}
				return start;
			}while(option!=5);
		}
	}
	return 0;
}

void diagnosis()
{
int i,ch[13],n,id;
char sy;
printf("\n\t\t\t\tDIAGNOSIS:");
printf("\nEnter Patient ID");
scanf("%d",&id);
printf("\n\nEnter the symtoms exhibited by the patient:");
printf("\n1.Recent Memory Lost\n2.Wandering Around\n3.Agressive Behaviour\n4.Depression\n5.Unaware Of Surroundings\n6.Diminished Judgement\n7.Unable to recall new info\n8.Long Term Memory Affected\n9.Personality Changes\n10.Confussion\n11.Motor Disturbances\n12.Bedridden\n13.Unable To Perform Daily Life Activities\n14.Incontinence\n15.Gait\n16.Difficulty In Concentrating\n17.Difficulty In Carrying Out Routine Or Complex Tasks\n18.Biazzare behavoiur\n19.Low Mood\n20.Passing Urine Without Consiuosness\n21.Halucination\n");
printf("\nRnter total number of Symptoms");
scanf("%d",&n);
printf("\n[ENTER THE SYMTIOMS BY THE NUMBERS BESIDE THEM]\n");
for(i=0;i<n;i++)
{
scanf("%d",&ch[i]);
}
fp=fopen("DGS.csv","w+");
fprintf(fp,"ID,Report,SymptomNo") ;
if(ch[i]==1||ch[i]==2||ch[i]==3||ch[i]==4||ch[i]==5||ch[i]==6||ch[i]==7)
{fprintf(fp,"\n%d,Mild,",id);
for(i=0;i<n;i++)
fprintf(fp,"%d",ch[i]);     }
if(ch[i]==1||ch[i]==2||ch[i]==3||ch[i]==4||ch[i]==5||ch[i]==6||ch[i]==7)
{fprintf(fp,"\n%d,Mild,",id);
for(i=0;i<n;i++)
fprintf(fp,"%d",ch[i]);
}
else if(ch[i]==1||ch[i]==2||ch[i]==3||ch[i]==4||ch[i]==5||ch[i]==6||ch[i]==7)
{fprintf(fp,"\n%,dMild,",id);
for(i=0;i<n;i++)
fprintf(fp,"%d",ch[i]);
}

}
int sort_by_month(struct node *start)
{
	struct node *pt1,*pt2;
	int m,flag=1;
	long int d1,d2;
	printf("\nMonth number for which you want all patient details: ");
	scanf("%d",&m);
	pt1=start;
	while(pt1!=NULL)
	{
		if(pt1->patient.date_of_entry.month_no==m)
			{
			    flag=0;
			    break;
			}
		pt1=pt1->next;
	}
	pt2=pt1;
	if(flag)
		return 0;
	while(pt1->next!=NULL)
	{
		while(pt1->patient.date_of_entry.month_no!=m)
			pt1=pt1->next;

		d1=pt1->patient.date_of_entry.month_no*50+pt1->patient.date_of_entry.day+pt1->patient.date_of_entry.year*1000;
		while(pt2!=NULL)
		{
		    if(pt2->patient.date_of_entry.month_no==m && pt1!=pt2){
		d2=pt2->patient.date_of_entry.month_no*50+pt2->patient.date_of_entry.day+pt2->patient.date_of_entry.year*1000;
		if((d1>d2) && (pt2->patient.date_of_entry.month_no==m))
		    swap_data(pt1,pt2);
		    }
			pt2=pt2->next;
		}
		pt1=pt1->next;
	}
    return m;
}
void display(struct node *start)
{
	char Discharge[15];
	if(start->patient.discharge==0)
		strcpy(Discharge,"Hospitalised");
	else
		strcpy(Discharge,"Discharged");
	printf("\nID: %d\n",start->patient.id);
	printf("Patient Name [FIRST LAST] : %s %s\n",start->patient.patient_name.first_name,start->patient.patient_name.surname);
	printf("Gender: %c\n",start->patient.gen);
	printf("Date of Birth: %d/%d/%d\n",start->patient.date_of_birth.date,start->patient.date_of_birth.month_no,start->patient.date_of_birth.year);
	printf("Age: %d years\n",start->patient.age);
	printf("Date of entry: %d/%d/%d\n",start->patient.date_of_entry.day,start->patient.date_of_entry.month_no,start->patient.date_of_entry.year);
	printf("Room Number: %d\n",start->patient.room_no);
	printf("Doctor: Dr. %s\n",start->patient.doctor );
	printf("Status: %s\n",Discharge);
}
void display_list(struct node *start)
{
		char Discharged[15];
		if(start->patient.discharge==0)
			strcpy(Discharged,"Hospitalised");
		else
			strcpy(Discharged,"Discharged");
		printf("%d\t\t%s %s\t\t%s\t\t%d\t\t%s\n",start->patient.id,start->patient.patient_name.first_name,start->patient.patient_name.surname,start->patient.doctor,start->patient.room_no,Discharged);
}
void sort_by_id(struct node *start)
{
	struct node *pt1,*pt2;
	pt1=start;
	while(pt1->next!=NULL)
	{
		pt2=pt1->next;
		while(pt2!=NULL)
		{
			if(pt1->patient.id>pt2->patient.id)
				swap_data(pt1,pt2);
			pt2=pt2->next;
		}
		pt1=pt1->next;
	}
}
void sort_by_name(struct node *start)
{
	struct node *pt1,*pt2;
	pt1=start;
	while(pt1->next!=NULL)
	{

		pt2=pt1->next;
		while(pt2!=NULL)
		{
			if(strcmp(pt1->patient.patient_name.first_name,pt2->patient.patient_name.first_name)>0)
				swap_data(pt1,pt2);
			pt2=pt2->next;
		}
		pt1=pt1->next;
	}
}
void swap_data(struct node *ptr1, struct node *ptr2){
	struct patient_details temp;
	temp=ptr1->patient;
	ptr1->patient=ptr2->patient;
	ptr2->patient=temp;
}

