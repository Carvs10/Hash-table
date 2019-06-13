#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <forward_list> 
#include "../include/hash.h"
 

struct Account{

    std::string client_name;
    int bank_code;
    int ag_numb;
    int cont;
    float balance;
    int m_balance;

    using AcctKey = std::pair < std::string, int >


    // Constructor 
    Account( std::string name, int code, int agg, int cont, float balance )
    : client_name(name), bank_code(code), ag_numb(agg), cont(cont), balance(balance)
    {/* empty */}

    Account(){

        client_name = " ";
        bank_code = 0;
        ag_numb = 0;
        cont = 0;
        balance = 0;
        m_balance =0;
    }

     // Return the key linked to the account.
    std::pair < std::string, int > getKey(){
        return{client_name, bank_code};
    }
};

/*!
 * Primary hash function to aplly on the key to get an positive integer
 * of type std::size_t. 
 */


struct KeyHash{
    std::size_t operator()(const Account::AcctKey& k_) const{
        return std::hash <std::string>()(k_.first) xor
               std::hash<int>()(k_.second);
    }
};

/*!
 * Method to compare keys by equality. Turn possible
 * to search for equal keys during linear search made on
 * the list of collisions, when necessary.
 */

struct KeyEqual{
    bool operator()(const Account::AcctKey& lhs_, const Account::AcctKeys& rhs_) const{
        return lhs_.first == rhs.first and lhs_.second == rhs_.second;
    }
};

/// Operator that checks if the contents of lhs and rhs are equal
bool operator==(const Account &lhs, const Account &rhs){
    return lhs.account == rhs.account;
}

#endif