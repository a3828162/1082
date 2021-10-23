#ifndef account
#define account

#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

class Account
{
public:
	Account()
		:ID(), PIN(), available_balance(), total_balance()
	{
	}

	~Account()
	{
	}

	void setAccountValue(string AccountID, string AccountPIN, double AccountAvaibleBalance, double AccountTotalBalance)
	{
		ID = AccountID;
		PIN = AccountPIN;
		available_balance = AccountAvaibleBalance;
		total_balance = AccountTotalBalance;
	}
	
	void ViewBalance()
	{
		cout << "Balance Information:\n";
		cout << " - Available balance: $" << fixed << setprecision(2) << available_balance << endl;
		cout << " - Total balance:     $" << fixed << setprecision(2) << total_balance << endl;

		cout.unsetf(ios::fixed);
	}

	void WithdrawCash(int& BillNumber)
	{
		int choice;
		while (1)
		{
			cout << "Withdrawal options:\n";
			cout << "1 - $20\n";
			cout << "2 - $40\n";
			cout << "3 - $60\n";
			cout << "4 - $100\n";
			cout << "5 - $200\n";
			cout << "6 - Cancel transcation\n";

			do cout << "\nChoose a withdraw option (1-6): ";
			while ((choice = inputAnInteger(1, 6)) == -1);
			cout << endl;

			switch (choice)
			{
			case 1:
				if (BillNumber >= (20 / 20) && available_balance >= 20)
				{
					BillNumber -= (20 / 20);
					available_balance -= 20;
					total_balance -= 20;
					cout << "Please take your cash from the cash dispenser.\n";
					return;
				}
				else if (available_balance < 20)
				{
					if (BillNumber < (20 / 20))
					{
						cout << "Don't have enough bill!\n";
						break;
					}
					cout << "You don't have enough money!\n";
					break;
				}					
			case 2:
				if (BillNumber >= (40 / 20) && available_balance >= 40)
				{
					BillNumber -= (40 / 20);
					available_balance -= 40;
					total_balance -= 40;
					cout << "Please take your cash from the cash dispenser.\n";
					return;
				}
				else if (available_balance < 40)
				{
					if (BillNumber < (40 / 20))
					{
						cout << "Don't have enough bill!\n\n";
						break;
					}
					cout << "You don't have enough money!\n\n";
					break;
				}
			case 3:
				if (BillNumber >= (60 / 20) && available_balance >= 60)
				{
					BillNumber -= (60 / 20);
					available_balance -= 60;
					total_balance -= 60;
					cout << "Please take your cash from the cash dispenser.\n";
					return;
				}
				else if (available_balance < 60)
				{
					if (BillNumber < (60 / 20))
					{
						cout << "Don't have enough bill!\n\n";
						break;
					}
					cout << "You don't have enough money!\n\n";
					break;
				}
			case 4:
				if (BillNumber >= (100 / 20) && available_balance >= 100)
				{
					BillNumber -= (100 / 20);
					available_balance -= 100;
					total_balance -= 100;
					cout << "Please take your cash from the cash dispenser.\n";
					return;
				}
				else if (available_balance < 100)
				{
					if (BillNumber < (100 / 20))
					{
						cout << "Don't have enough bill!\n\n";
						break;
					}
					cout << "You don't have enough money!\n\n";
					break;
				}
			case 5:
				if (BillNumber >= (200 / 20) && available_balance >= 200)
				{
					BillNumber -= (200 / 20);
					available_balance -= 200;
					total_balance -= 200;
					cout << "Please take your cash from the cash dispenser.\n";
					return;
				}
				else if (available_balance < 200)
				{
					if (BillNumber < (200 / 20))
					{
						cout << "Don't have enough bill!\n\n";
						break;
					}
					cout << "You don't have enough money!\n\n";
					break;
				}
			case 6:
				return;
			default:
				cout << "\nIncorrect choice!\n";
				break;
			}
		}
	}

	void DepositFund()
	{
		cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
		double money;
		cin >> money;
		if (money == 0)
			return;	
		money /= 100;
		total_balance += money;
		cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << money << " in the deposit slot.\n\n";
		cout << "Your envelope has been received.\n";
		cout << "Note: The money deposited will not be available until we\n";
		cout << "verify the amount of any enclosed cash, and any enclosed checks clear.\n";
	}

	string getID()
	{
		return ID;
	}

	string getPIN()
	{
		return PIN;
	}

	int inputAnInteger(int begin, int end) {

		char num[50];

		cin.getline(num, 50); // 
		if (!strlen(num)) { //如果為零輸入第二次,不用會錯 
			cin.getline(num, 50);
		}
		for (unsigned int i = 0; i < strlen(num); i++) { //判斷輸入是否為數字 
			if (num[i] < '0' || num[i]>'9') {
				return -1;
			}
		}
		int n = atoi(num); //把字串轉為整數 
		if (n >= begin && n <= end) {
			return n;
		}
		else {
			return -1;
		}
	}

private:
	string ID;
	string PIN;
	double available_balance;
	double total_balance;
};

#endif // !account.h

