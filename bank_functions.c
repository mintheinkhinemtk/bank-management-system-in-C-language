#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"bank_functions.h"

void menu(struct user_account* user)
{
    int choice;
    printf("Admin panel.\n");
    printf("Enter 1 for creating a new account,2 for updating an existing account ,3 for transaction,4 for checking an existing account,"
           "5 for removing an account,6 for viewing customer lists,7 for closing the program.\n");
    scanf("%d",&choice);
    int ch=getchar();
    switch(choice)
        {
            case 1:new_acc(user);
                   break;
            case 2:edit(user);
                   break;
            case 3:transact(user);
                   break;
            case 4:check(user);
                   break;
            case 5:delet_e(user);
                   break;
            case 6:view_list(user);
                   break;
            case 7:close();
                   break;
        }
}
double interest(int time,long int balance,double rate)
{
    double result;
    result=time*balance*(rate/100);
    return result;
}

void new_acc(struct user_account* new_user)
{
    FILE *fptr,*fptr1;
    if((fptr=fopen("record.dat","a+"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter today's date in format day/month/year:");
    scanf("%d/%d/%d",&new_user->deposit.day,&new_user->deposit.month,&new_user->deposit.year);
    int ch;
    ch=getchar();
    printf("Enter bank account number.\n");
    scanf("%d",&new_user->acc_number);
    ch=getchar();
    if((fptr1=fopen("account_number.dat","a+"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    int check_number;
    check_acc:
    while((fscanf(fptr1,"%d",&check_number))!=EOF)
    {
        if(check_number==new_user->acc_number)
        {
            printf("Account number you've entered is equal to old account number,try again.\n");
            scanf("%d",&new_user->acc_number);
            ch=getchar();
            rewind(fptr1);
            goto check_acc;
        }
    }
    int n;
    printf("Enter 1 or others to continue or discard.\n");
    scanf("%d",&n);
    if(n==1)
    {
    printf("Enter principal amount,name,NRC number,address and phone number.\n");
    scanf("%ld %s %s %s %s",&new_user->principal_amount,new_user->name,new_user->NRC_number,new_user->address,new_user->phone_number);
    ch=getchar();
    fprintf(fptr1,"%d\n",new_user->acc_number);
    fprintf(fptr,"%d %ld %s %s %s %s %d/%d/%d\n",new_user->acc_number,new_user->principal_amount,new_user->name,new_user->NRC_number,new_user->address,new_user->phone_number,new_user->deposit.day,new_user->deposit.month,new_user->deposit.year);
    fclose(fptr);
    fclose(fptr1);
    }
    else
    {
        fclose(fptr);
        fclose(fptr1);
    }
    printf("Enter 1 to go to menu or 0 to exit.\n");
    int main_exit;
    add_invalid:
    scanf("%d",&main_exit);
    if(main_exit==1)
    {
        menu(new_user);
    }
    else if(main_exit==0)
    {
        close();
    }
    else
    {
        printf("Invalid number.\n");
        goto add_invalid;
    }




}

void close()
{
    printf("You have closed the program.\n");
}

void edit(struct user_account *user)
{
    FILE* old_fptr,*new_fptr;
    int test=0;
    if((old_fptr=fopen("record.dat","r"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    if((new_fptr=fopen("new_record.dat","w"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    int check_number;
    printf("enter bank account number to edit.\n");
    scanf("%d",&check_number);
    int ch=getchar();
    while((fscanf(old_fptr,"%d %ld %s %s %s %s %d/%d/%d",&user->acc_number,&user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,&user->deposit.day,&user->deposit.month,&user->deposit.year))!=EOF)
    {
        if(check_number==user->acc_number)
        {
            test=1;
            int choice;
            invalid_number:
            printf("Enter 1 or 2 or 3 to edit address or phone number or both: ");
            scanf("%d",&choice);
            ch=getchar();
            if(choice==1)
            {
                printf("Enter new address.\n");
                scanf("%s",user->address);
                ch=getchar();
                fprintf(new_fptr,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);
            }
            else if(choice==2)
            {
                printf("Enter new phone number.\n");
                scanf("%s",user->phone_number);
                ch=getchar();
                fprintf(new_fptr,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);
            }
            else if(choice==3)
            {
                printf("Enter new address and phone number.\n");
                scanf("%s%s",user->address,user->phone_number);
                ch=getchar();
                fprintf(new_fptr,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);
            }
            else
            {
                goto invalid_number;
            }



        }
        else
        {
            fprintf(new_fptr,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);
        }
    }
        fclose(old_fptr);
        fclose(new_fptr);
        remove("record.dat");
        rename("new_record.dat","record.dat");
        if(test==1)
        {


        printf("Enter 1 to edit again or 2 to go to menu or 3 to exit from the program.\n");
        int number;
        edit_invalid_1:
        scanf("%d",&number);
        if(number==1)
        {
            edit(user);
        }
        else if(number==2)
        {
            menu(user);
        }
        else if(number==3)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_1;
        }
        }
    else if(test!=1)
    {
        printf("No record found.\n");
        printf("Enter 1 to edit again or 2 to go to menu or 3 to exit from the program.\n");
        int number;
        edit_invalid_2:
        scanf("%d",&number);
        if(number==1)
        {
            edit(user);
        }
        else if(number==2)
        {
            menu(user);
        }
        else if(number==3)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_2;
        }
    }


}

void transact(struct user_account* user)
{
    FILE *fptr1,*fptr2;
    int test=0;
    if((fptr1=fopen("record.dat","r"))==NULL)
    {
        fprintf(stderr,"Can't open the file.\n");
        exit(EXIT_FAILURE);
    }

    if((fptr2=fopen("new_record.dat","w"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    int check_number;
    printf("enter your bank account number to do transaction.\n");
    scanf("%d",&check_number);
    int ch=getchar();
    while((fscanf(fptr1,"%d %ld %s %s %s %s %d/%d/%d",&user->acc_number,&user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,&user->deposit.day,&user->deposit.month,&user->deposit.year))!=EOF)
    {
        if(check_number==user->acc_number)
        {
            int choice;
            test=1;
            edit_invalid_3:
            printf("Enter 1 or 2 to withdraw or deposit into your bank account.\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                long int amount;
                printf("Enter amount to withdraw.\n");
                scanf("%ld",&amount);
                user->principal_amount=(user->principal_amount)-amount;
                fprintf(fptr2,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);

            }
            else if(choice==2)
            {
                long int amount;
                printf("Enter amount to deposit.\n");
                scanf("%ld",&amount);
                user->principal_amount=(user->principal_amount)+amount;
                fprintf(fptr2,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);

            }
            else
            {
                goto edit_invalid_3;
            }
        }
        else
        {
            fprintf(fptr2,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("record.dat");
    rename("new_record.dat","record.dat");
     if(test==1)
    {


        printf("Enter 1 to transact again or 2 to go to menu or 3 to exit from the program.\n");
        int number;
        edit_invalid_4:
        scanf("%d",&number);
        if(number==1)
        {
            transact(user);
        }
        else if(number==2)
        {
            menu(user);
        }
        else if(number==3)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_4;
        }
    }
    else if(test!=1)
    {
        printf("No record found.\n");
        printf("Enter 1 to try again or 2 to go to menu or 3 to exit from the program.\n");
        int number;
        edit_invalid_5:
        scanf("%d",&number);
        if(number==1)
        {
            edit(user);
        }
        else if(number==2)
        {
            menu(user);
        }
        else if(number==3)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_5;
        }
    }
}


void check(struct user_account* user)
{
    FILE *fptr;
    int test=0;
    if((fptr=fopen("record.dat","r"))==NULL)
    {
        fprintf(stderr,"Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    int date,month,year;
    printf("Enter today's date in dd/mm/yy.\n");
    scanf("%d/%d/%d",&date,&month,&year);
    int ch=getchar();
    int check_number;
    double interest_result;
    printf("Enter your bank account number to calculate interest and final amount.\n");
    scanf("%d",&check_number);
    ch=getchar();
    while((fscanf(fptr,"%d %ld %s %s %s %s %d/%d/%d",&user->acc_number,&user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,&user->deposit.day,&user->deposit.month,&user->deposit.year))!=EOF)
        {
           if(check_number==user->acc_number)
           {
               test=1;
               if((year-(user->deposit.year)>0)||(month-(user->deposit.month)))
               {
                   int time=(year-(user->deposit.year))*12+month;
                   interest_result=interest(time,user->principal_amount,9);
                   printf("Account number:%d Principal amount:%ld username:%s NRC number:%s address:%s phone number:%s interest result:%.3lf from date:%d/%d/%d to"
                          "today's date:%d/%d/%d",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,interest_result,user->deposit.day,user->deposit.month,user->deposit.year,date,month,year);

               }

               else printf("Not enough time to calculate interest.You can get interest after 1 month of putting in your principal amount of money.\n");
           }
        }
    fclose(fptr);
    if(test==1)
    {


        printf("Enter 1 to go to menu or 2 to exit from the program.\n");
        int number;
        edit_invalid_6:
        scanf("%d",&number);
        if(number==1)
        {
            menu(user);
        }
        else if(number==2)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_6;
        }
    }
    else if(test!=1)
    {
        printf("No record found.\n");
        printf("Enter 1 to try again or 2 to go to menu or 3 to exit from the program.\n");
        int number;
        edit_invalid_7:
        scanf("%d",&number);
        if(number==1)
        {
            check(user);
        }
        else if(number==2)
        {
            menu(user);
        }
        else if(number==3)
        {
            close();
        }
        else
        {
            printf("Invalid number.\n");
            goto edit_invalid_7;
        }
    }
}


void delet_e(struct user_account* user)
{
    FILE *fptr1,*fptr2;
    int test=0;
    if((fptr1=fopen("record.dat","r"))==NULL)
    {
        fprintf(stderr,"Can't open the file.\n");
        exit(EXIT_FAILURE);
    }

    if((fptr2=fopen("new_record.dat","w"))==NULL)
    {
        fprintf(stderr,"Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    int check_number;
    printf("Enter a bank account number.\n");
    scanf("%d",&check_number);
    int ch=getchar();
    while((fscanf(fptr1,"%d %ld %s %s %s %s %d/%d/%d",&user->acc_number,&user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,&user->deposit.day,&user->deposit.month,&user->deposit.year))!=EOF)
    {
        if((user->acc_number)!=check_number)
        {
           fprintf(fptr2,"%d %ld %s %s %s %s %d/%d/%d\n",user->acc_number,user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,user->deposit.day,user->deposit.month,user->deposit.year);

        }
        else
        {
                test=1;
                printf("Account has been deleted successfully.\n");
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("record.dat");
    rename("new_record.dat","record.dat");


    if(test==0)
        {
            printf("\nRecord not found!!\a\a\a");
            int number;
            erase_invalid:
            printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
            scanf("%d",&number);

                if (number==1)
                    menu(user);
                else if (number==2)
                    close();
                else if(number==0)
                    delet_e(user);
                else
                    {
                    printf("\nInvalid!\a");
                    goto erase_invalid;
                    }
        }
    else
        {
        printf("No records found.\n");
        int number;
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&number);
        if (number==1)
            menu(user);
        else
            close();
        }
}

void view_list(struct user_account *user)
{
    FILE *view;
    int test=0;
    if((view=fopen("record.dat","r"))==NULL)
    {
        fprintf(stderr,"Can't open the file.\n");
        exit(EXIT_FAILURE);
    }
    int check_number;
    printf("Enter a bank account number.\n");
    scanf("%d",&check_number);
    int ch=getchar();

    while((fscanf(view,"%d %ld %s %s %s %s %d/%d/%d",&user->acc_number,&user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number,&user->deposit.day,&user->deposit.month,&user->deposit.year))!=EOF)
    {
        if(check_number==user->acc_number)
        {
            test=1;
            printf("%ld %s %s %s %s\n",user->principal_amount,user->name,user->NRC_number,user->address,user->phone_number);
        }
    }
    fclose(view);
    if(test==1)
    {
        int number;
        view_invalid:
            printf("Enter number 1 to go to menu or 2 to exit.\n");
            scanf("%d",&number);
            ch=getchar();
            if(number==1)
            {
                menu(user);
            }
            else if(number==2)
            {
                close();
            }
            else
                goto view_invalid;

    }
    else if(test==0)
    {
        printf("No records.\n");
        int number;
        view_invalid_1:
            scanf("%d",&number);
            ch=getchar();
            printf("Enter number 1 to go to menu or 2 to exit.\n");
            if(number==1)
            {
                menu(user);
            }
            else if(number==2)
            {
                close();
            }
            else
                goto view_invalid_1;

    }


}
