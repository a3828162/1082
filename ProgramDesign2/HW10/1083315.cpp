#include <iostream>
#include <string.h>
#include <vector>
#include "account.h"
using namespace std;

int main() {

	string InputID, InputPIN;
	vector< Account > atm(2);
	atm[0].setAccountValue("12345", "54321", 1000, 1200);
	atm[1].setAccountValue("98765", "56789", 200, 200);
	int BillNumber = 500;
	while (1)
	{
		cout << "Welcome!\n\n";
		cout << "Please enter your account number: ";
		cin >> InputID;
		cout << endl << "Enter your PIN: ";
		cin >> InputPIN;
		bool a = false;
		for (unsigned int i = 0; i < 2; i++)
		{
			if (InputID == atm[i].getID() && InputPIN == atm[i].getPIN())
			{
				int choice;
				while (1)
				{
					cout << "\nMain menu:\n";
					cout << "1 - View my balance\n";
					cout << "2 - Withdraw cash\n";
					cout << "3 - Deposit funds\n";
					cout << "4 - Exit\n";

					do cout << "\nEnter a choice: ";
					while ((choice = atm[i].inputAnInteger(1, 4)) == -1);
					cout << endl;

					switch (choice)
					{
					case 1:
						atm[i].ViewBalance();
						break;
					case 2:
						atm[i].WithdrawCash(BillNumber);
						break;
					case 3:
						atm[i].DepositFund();
						break;
					case 4:
						cout << "Exitint the system..." << endl;
						break;
					default:
						cout << "\nIncorrect choice!\n";
						break;
					}
					if (choice == 4)
						break;
				}
				a = true;
				cout << "\nThank you! Goodbye!\n\n";
			}
		}
		if (a == false)
			cout << "\nWrong Input!\n\n";
	}

	return 0;
}