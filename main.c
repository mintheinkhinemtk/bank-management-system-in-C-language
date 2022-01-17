#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"information.h"
#include"bank_functions.h"

int main()
{
    struct user_account user;
    char pass[10],password[10]="codewithc";
    printf("Enter password to login.\n");
    scanf("%s",pass);
    if(strcmp(pass,password)==0)
    {
        menu(&user);
    }
    else
    {
        printf("Wrong password.\n");
        int number;
        login_try:
        printf("Enter 1 or 0 to try again or exit.\n");
        scanf("%d",&number);
        if(number==1)
        {
            main();
        }
        else if(number==0)
        {
            close();
        }
        else
        {
            goto login_try;
        }

    }
    return 0;
}
