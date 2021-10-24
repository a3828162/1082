#include<iostream>
#include"BOOK.h"
using namespace std;

int main() 
{
	cout << "Taiwan High Speed Rail Booking System\n\n";
	BOOK account;
	while (1)
	{
		cout << "Enter your choice\n\n";
		cout << "1. Booking\n2. Booking History\n3. End Program\n? ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			account.Booking();
			break;		
		case 2:
			account.Booking_History();
			break;
		case 3:
			account.Save();
			break;
		default:
			cout << "\nWrong input!\n" << endl;
			break;
		}
		if (choice == 3)
			break;
	}

	return 0;
}