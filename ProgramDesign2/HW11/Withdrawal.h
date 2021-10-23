// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
   Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills );
   void execute(); // perform the withdrawal transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   int amount; // amount to withdraw
   int &remainingBills; // number of $20 bills remaining 

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account* getAccount(int accountNumber, vector< Account >& accounts)
   {
       for (size_t i = 0; i < accounts.size(); i++)
       {
           if (accounts[i].getAccountNumber() == accountNumber)
               return &accounts[i];
       }
       return NULL;
   }

   // display a menu of withdrawal amounts and the option to cancel;
   // return the chosen amount or 0 if the user chooses to cancel
   int displayMenuOfAmounts() const;
}; // end class Withdrawal

Withdrawal::Withdrawal(int userAccountNumber, vector< Account >& atmAccounts, int& atmRemainingBills)
    :accountNumber(userAccountNumber),
    accounts(atmAccounts),
    remainingBills(atmRemainingBills),
    amount()
{
}

void Withdrawal::execute()
{
    Account* const userAccountPtr = getAccount(accountNumber, accounts);
    while (1)
        switch (displayMenuOfAmounts())
        {
        case 1:
            if ((userAccountPtr->getAvailableBalance() >= 20) && remainingBills >= 1)
                userAccountPtr->debit(20);
            else
            {
                if (remainingBills < 1)
                {
                    cout << "Don't have enough Bill!\n\n";
                    break;
                }
                if (userAccountPtr->getAvailableBalance() < 20)
                {
                    cout << "\nYou dont's have enough money!\n";
                    break;
                }
            }
            cout << "\nPlease take your cash from the cash dispenser.\n";
            return;
        case 2:
            if ((userAccountPtr->getAvailableBalance() >= 40) && remainingBills >= 2)
                userAccountPtr->debit(40);
            else
            {
                if (remainingBills < 2)
                {
                    cout << "Don't have enough Bill!\n\n";
                    break;
                }
                if (userAccountPtr->getAvailableBalance() < 40)
                {
                    cout << "\nYou dont's have enough money!\n";
                    break;
                }
            }
            cout << "\nPlease take your cash from the cash dispenser.\n";
            return;
        case 3:
            if ((userAccountPtr->getAvailableBalance() >= 60) && remainingBills >= 3)
                userAccountPtr->debit(60);
            else
            {
                if (remainingBills < 3)
                {
                    cout << "Don't have enough Bill!\n\n";
                    break;
                }
                if (userAccountPtr->getAvailableBalance() < 60)
                {
                    cout << "\nYou dont's have enough money!\n";
                    break;
                }
            }
            cout << "\nPlease take your cash from the cash dispenser.\n";
            return;
        case 4:
            if ((userAccountPtr->getAvailableBalance() >= 100) && remainingBills >= 5)
                userAccountPtr->debit(100);
            else
            {
                if (remainingBills < 5)
                {
                    cout << "Don't have enough Bill!\n\n";
                    break;
                }
                if (userAccountPtr->getAvailableBalance() < 100)
                {
                    cout << "\nYou dont's have enough money!\n";
                    break;
                }
            }
            cout << "\nPlease take your cash from the cash dispenser.\n";
            return;
        case 5:
            if ((userAccountPtr->getAvailableBalance() >= 200) && remainingBills >= 10)
                userAccountPtr->debit(200);
            else
            {
                if (remainingBills < 10)
                {
                    cout << "Don't have enough Bill!\n\n";
                    break;
                }
                if (userAccountPtr->getAvailableBalance() < 200)
                {
                    cout << "\nYou dont's have enough money!\n";
                    break;
                }
            }
            cout << "\nPlease take your cash from the cash dispenser.\n";
            return;
        case 6:
            return;
        default:
            break;
        }

}

int Withdrawal::displayMenuOfAmounts() const
{
    cout << "\nWithdrawal options:" << endl;
    cout << "1 - $20\n2 - $40\n3 - $60\n4 - $100\n5 - $200\n6 - Cancel transaction\n";
    int choice;
    cout << "\nChoose a withdrawal option (1-6): ";
    cin >> choice;
    return choice;
}
#endif // WITHDRAWAL_H