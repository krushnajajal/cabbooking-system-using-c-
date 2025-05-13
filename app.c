#include<stdio.h>
#include<string.h>
struct customer
{
    int cab_num;
    char cust_name[100];
    char starting_loc[100];
    char destination_loc[100];
    int seat;
    int charge;
}c1;
struct data
{
    char userid[50];
    char password[50];
}d1;
int log_in()
{
    FILE *fp;
    fp=fopen("data","r");
    int result;
    char user[50],pass[50];
    printf("enter your username :");
    scanf("%s",user);
    printf("enter your password : ");
    scanf("%s",pass);
    while(fread(&d1,sizeof(d1),1,fp))
    {
        if(strcmp(user,d1.userid)==0 && strcmp(pass,d1.password)==0)
            result=1;
    }
    fclose(fp);
    return result;
}
void new_ac()
{
    FILE *fp;
    fp=fopen("data","a");
    char user[50],pass[50],confirm[50];
    printf("\nenter your username : ");
    scanf("%s",d1.userid);
    pass :
    printf("enter password : ");
    scanf("%s",d1.password);
    printf("confirm password : ");
    scanf("%s",confirm);
    if(strcmp(d1.password,confirm)!=0)
    {
        printf("\n\nboth passwords are not same \n\n");
        goto pass;
    }
    fwrite(&d1,sizeof(d1),1,fp);
    fclose(fp);
}
int choice()
{
    int ch;
    printf("1) insert the customer data \n");
    printf("2) display the customer data \n");
    printf("3) update data \n");
    printf("4) search data base on customer name \n");
    printf("5) search data base on no of seat\n");
    printf("6) delete the record \n");
    printf("7) sorting the data base on charges \n");
    printf("8) total number of records \n");
    printf("9) exit \n");
    printf("enter your choice : ");
    scanf("%d",&ch);
    return ch;
}
void insert()
{
    FILE *fp;
    fp=fopen("customer","a");
    int i,n;
    printf("enter the number of records you want to insert : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\n\nenter the customerid : ");
        scanf("%d",&c1.cab_num);
        printf("enter the customer name : ");
        scanf("%s",c1.cust_name);
        printf("enter the starting location : ");
        scanf("%s",c1.starting_loc);
        printf("enter the destination location : ");
        scanf("%s",c1.destination_loc);
        seat :
        printf("enter the seat between 2 to 6 : ");
        scanf("%d",&c1.seat);
        if(c1.seat>6 || c1.seat<2)
        {
            printf("enter right input\n");
            goto seat;
        }
        printf("enter the charges : ");
        scanf("%d",&c1.charge);

        fwrite(&c1,sizeof(c1),1,fp);
    }
    fclose(fp);
}
int empty()
{
    int c=0;
    FILE *fp;
    fp=fopen("customer","r");
    while(fread(&c1,sizeof(c1),1,fp))
        c++;
    fclose(fp);
    return c;
}
void display()
{
    FILE *fp;
    fp=fopen("customer","r");
    printf("\n cab no \t cust_name \t starting \t destination \t seat \t charge \n\n");
    while(fread(&c1,sizeof(c1),1,fp))
    {
        printf("%d \t\t %s \t\t %s \t\t %s \t\t %d \t %d \n",c1.cab_num,c1.cust_name,c1.starting_loc
               ,c1.destination_loc,c1.seat,c1.charge);
    }
    printf("\n\n");
    fclose(fp);
}
void searchbyname()
{
    FILE *fp;
    fp=fopen("customer","r");
    char str1[100];
    int count=0;
    printf("enter the customer name you want to search : ");
    scanf("%s",str1);
    printf("\n cab no \t cust_name \t starting \t destination \t seat \t charge \n\n");
    while(fread(&c1,sizeof(c1),1,fp))
    {
        if(strcmp(str1,c1.cust_name)==0)
        {
            count++;
            printf("%d \t\t %s \t\t %s \t\t %s \t\t %d \t %d \n",c1.cab_num,c1.cust_name,c1.starting_loc
               ,c1.destination_loc,c1.seat,c1.charge);
        }
    }
    if(count==0)
        printf("\n\n NO RECORD FOUND \n\n");
    fclose(fp);
}
void searchbyseat()
{
    FILE *fp;
    fp=fopen("customer","r");
    int count=0,s;
    seat1:
    printf("enter the no of seat you want to search (enter no between 2 to 6): ");
    scanf("%d",&s);
    if(s<2 || s>6)
    {
        printf("\n WRONG INPUT\n");
        goto seat1;
    }
    printf("\n cab no \t cust_name \t starting \t destination \t seat \t charge \n\n");
    while(fread(&c1,sizeof(c1),1,fp))
    {
        if(c1.seat==s)
        {
            count++;
            printf("%d \t\t %s \t\t %s \t\t %s \t\t %d \t %d \n",c1.cab_num,c1.cust_name,c1.starting_loc
               ,c1.destination_loc,c1.seat,c1.charge);
        }
    }
    printf("\n\n");
    if(count==0)
        printf("\n\n NO RECORD FOUND \n\n");
    fclose(fp);
}
int total_no_records()
{
    int count=0;
    FILE *fp;
    fp=fopen("customer","r");
    while(fread(&c1,sizeof(c1),1,fp))
        count++;
    fclose(fp);
    return count;
}
void update()
{
    FILE *fp,*temp;
    fp=fopen("customer","r");
    temp=fopen("temp","w");
    int n,count=0;
    printf("enter the cab number you want  to update the record : ");
    scanf("%d",&n);
    while(fread(&c1,sizeof(c1),1,fp))
    {
        if(n==c1.cab_num)
            count++;
    }
    if(count==0)
        printf("\n\n NO SUCH CAB NO FOUND \n\n");
    else
    {
        rewind(fp);
        int choice;
        while(fread(&c1,sizeof(c1),1,fp))
        {
            if(n!=c1.cab_num)
                fwrite(&c1,sizeof(c1),1,temp);
            else
            {
                printf("\n\n1) update customer name \n");
                printf("2)update no of seat \n");
                printf("3)update starting and destination location \n");
                printf("4)update charges \n");
                printf("5)update all data \n");
                printf("enter your choice : ");
                scanf("%d",&choice);
                switch(choice)
                {
                case 1:
                    printf("enter the customer name : ");
                    scanf("%s",c1.cust_name);
                    break;

                case 2:
                    seat :
                    printf("enter the no of seat (between 2 to 6) : ");
                    scanf("%d",&c1.seat);
                    if(c1.seat>6 || c1.seat<2)
                    {
                        printf("\n enter proper no of seat \n");
                        goto seat;
                    }
                    break;

                case 3:
                    printf("enter starting and destination location : ");
                    scanf("%s %s",c1.starting_loc,c1.destination_loc);
                    break;

                case 4:
                    printf("enter the charges : ");
                    scanf("%d",&c1.charge);
                    break;

                case 5:
                    printf("enter the customer name,starting location,destination location,charges : ");
                    scanf("%s %s %s %d",c1.cust_name,c1.starting_loc,c1.destination_loc,&c1.charge);
                    seat1:
                    printf("enter the no of seat : ");
                    scanf("%d",&c1.seat);
                    if(c1.seat>6 || c1.seat<2)
                    {
                        printf("\n enter proper no of seat \n");
                        goto seat1;
                    }
                    break;

                default:
                    printf("\nwrong choice\n\n");
                }
        fwrite(&c1,sizeof(c1),1,temp);
            }
    }
     fclose(fp);
    fclose(temp);
    fp=fopen("customer","w");
    temp=fopen("temp","r");
    while(fread(&c1,sizeof(c1),1,temp))
    {
        fwrite(&c1,sizeof(c1),1,fp);
    }
    printf("\n\nRECORD UPDATED\n\n");
    fclose(fp);
    fclose(temp);
    printf("\n\n");
    display();
    }
}
void delete()
{
    FILE *fp,*temp;
    fp=fopen("customer","r");
    temp=fopen("temp","w");
    int n,count=0;
    printf("enter the cab number you want to delete : ");
    scanf("%d",&n);
    while(fread(&c1,sizeof(c1),1,fp))
    {
        if(c1.cab_num==n)
            count++;
    }
    fclose(fp);
    if(count==0)
        printf("\n\n NO SUCH CAB NO FOUND \n\n");
    else
    {
        fp=fopen("customer","r");
        while(fread(&c1,sizeof(c1),1,fp))
        {
            if(n!=c1.cab_num)
            {
                fwrite(&c1,sizeof(c1),1,temp);
            }
    }
    fclose(fp);
    fclose(temp);
    fp=fopen("customer","w");
    temp=fopen("temp","r");
    while(fread(&c1,sizeof(c1),1,temp))
    {
        fwrite(&c1,sizeof(c1),1,fp);
    }
    fclose(fp);
    fclose(temp);
    printf("\n\n RECORD DELETED \n\n");
    display();
    }
}
void sort()
{
	int a[20], count = 0, i, j, t, c;
	int size=total_no_records();
	struct customer *p,temp;
	p=(struct customer *)calloc(size,sizeof(struct customer));
	FILE *fp;
	fp = fopen("customer", "r");
	for(int i=0;i<size;i++)
	{
		fread(p+i, sizeof(c1), 1, fp);
	}
	c = size;
	for (i = 0; i<size; i++)
	{
		for (j = i + 1; j<size; j++)
		{
			if ((p+i)->charge>(p+j)->charge)
			{
				temp = *(p+i);
				*(p+i) =*(p+j);
				*(p+j) = temp;
			}
		}
	}
    printf("\n cab no \t cust_name \t starting \t destination \t seat \t charge \n\n");
    for (i = 0; i<size; i++)
	{
		printf("%d \t\t %s \t\t %s \t\t %s \t\t %d \t %d \n", (p+i)->cab_num, (p+i)->cust_name,(p+i)->starting_loc,
         (p+i)->destination_loc,(p+i)->seat,(p+i)->charge);
	}
	fclose(fp);
}
int main()
{
    int n,result;
    printf("enter 1 if you have account otherwise enter 0 : ");
    scanf("%d",&n);
    if(n==1)
    {
        login:
        result=log_in();
        if(result==1)
            printf("\n\n\t\t\t WELCOME TO OUR WEBSITE \n\n");
        else
        {
            printf("\n\ncreate new account : \n\n");
            new_ac();
            printf("\n\nenter your details again to verify \n\n");
            goto login;
        }
    }
    else
    {
        new_ac();
        printf("\n\n ENTER YOUR DETAILS AGAIN TO VERIFY \n\n");
        goto login;
    }
    int ch,emp,ans;
    do{
        ch=choice();
        switch(ch)
        {
        case 1:
            insert();
            break;
        case 2:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                display();
            }
        break;
        case 3:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                update();
            }
        break;
        case 4:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                searchbyname();
            }
        break;
        case 5:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                searchbyseat();
            }
        break;
        case 6:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                delete();
            }
        break;
        case 7:
            emp=empty();
            if(emp==0)
                printf("\n\n EMPTY SET \n\n");
            else
            {
                printf("\n\n");
                sort();
            }
        break;
        case 8:
            ans=total_no_records();
            printf("\n\n THE TOTAL NO OF RECORDS ARE %d\n\n",ans);
            break;

        }
    }while(ch!=9);
    return 0;
}