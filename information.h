#ifndef INFORMATION_H
#define INFORMATION_H

struct date
{
    int day,month,year;
};


struct user_account
{
    char name[21];
    char NRC_number[20];
    char address[66];
    char phone_number[12];
    long int principal_amount; //beginning balance
    struct date deposit;
    int acc_number;

};

#endif // INFORMATION_H
