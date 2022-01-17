#ifndef BANK_FUNCTIONS_H
#define BANK_FUNCTIONS_H

#include"information.h"


void menu();
double interest(int time,long int balance,double rate);
void new_acc(struct user_account*);
void edit(struct user_account*);
void transact(struct user_account*);
void check(struct user_account*);
void delet_e(struct user_account*);
void view_list();
void close();
#endif // BANK_FUNCTIONS_H
