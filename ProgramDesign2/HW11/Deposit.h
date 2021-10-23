// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition
#include <iomanip>

class Deposit
{
public:
    Deposit(int userAccountNumber, vector< Account >& atmAccounts);
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account* getAccount(int accountNumber, vector< Account >& accounts)
   {
       for (size_t i = 0; i < accounts.size(); i++)
       {
           if (accountNumber == accounts[i].getAccountNumber())
               return &accounts[i];
       }
       return NULL;
   }
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit

Deposit::Deposit(int userAccountNumber, vector< Account >& atmAccounts)
    :accountNumber(userAccountNumber),
    accounts(atmAccounts),
    amount()
{
}

void Deposit::execute()
{
    cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
    amount = promptForDepositAmount();
    if (amount == 0)
        return;
    Account* const userAccountPtr = getAccount(accountNumber, accounts);
    userAccountPtr->credit(amount);
    cout << setprecision(2) << fixed << "\nPlease insert a deposit envelope containing $" << amount << " in the deposit slot." << endl << endl;
    cout << "Your envelope has been received." << endl;
    cout << "NOTE: The money deposited will not be available until we" << endl;
    cout << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
}

double Deposit::promptForDepositAmount() const
{
    double i;
    cin >> i;
    i /= 100;
    return i;
}
#endif // DEPOSIT_H