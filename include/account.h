#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream> //cout, endl
#include <string> // std::string
#include <stdlib> 

struct Account{

    std::string<char> client_name;
    int bank_code;
    int ag_numb;
    int cont;
    int balance;


    // Constructor 
    Account();

    //Method

    // Return the key linked to the account.
    get_key();


}