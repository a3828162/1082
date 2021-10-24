// MakeReservation.cpp
// AvailSeats-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h"

extern int inputAnInteger( int begin, int end );

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
   AvailSeatsDatabase &theSeatsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availSeatsDatabase( theSeatsDatabase )
{
}

void MakeReservation::execute()
{
   cout << "\nEnter the party size (1~6): ";

   int partySize;
   do cout << "? ";
   while( ( partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   Date date;
   inputDate( date, currentDate, partySize );

   int timeCode;
   inputTimeCode( timeCode, date, partySize );

   string name;
   cout << "\nEnter name: ";
   cin >> name;

   string phoneNumber;
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   int menuCode;
   do cout << "? ";
   while( ( menuCode = inputAnInteger( 1, 3 ) ) == -1 );

   Reservation newReservation( phoneNumber, name, date, timeCode, partySize, menuCode );

   cout << endl;
   newReservation.displayReservationInfo();

   cout << "\n\nReservation Completed\n";

   reservationDatabase.pushBack( newReservation );

   availSeatsDatabase.decreaseAvailSeats( date, timeCode, partySize );
}

void MakeReservation::inputDate( Date &date, Date currentDate, int partySize )
{
	vector <Date> temp;
	vector <int> temp2;
	cout << "\nChoose a date\n";
	size_t a = 0;
	for (size_t i = 1; i <= 30; ++i)
	{
		currentDate + 1;
		if (availSeatsDatabase.availableTimes(currentDate, partySize))
		{
			cout << setw(2) << i << ". " << setw(4) << currentDate.getYear() << "/";
			if (currentDate.getMonth() < 10)
				cout << 0;
			cout << currentDate.getMonth() << "/";
			if (currentDate.getDay() < 10)
				cout << 0;
			cout << currentDate.getDay() << "   ";
			temp.push_back(currentDate);
			temp2.push_back(i);
			++a;
			if (a % 4 == 0)
				cout << endl;
		}
	}
	cout << endl;
	int choice;
	bool temp3 = false;
	while (1)
	{
		cout << "?";
		choice = inputAnInteger(1, 30);
		for (size_t i = 0; i < temp2.size(); ++i)
			if (choice == temp2[i] && choice > 0 && choice < 31)
			{
				temp3 = true;
				break;
			}
		if (temp3)
			break;
	}

	date.setDate(temp[choice - 1].getYear(), temp[choice - 1].getMonth(), temp[choice - 1].getDay());
}

void MakeReservation::inputTimeCode( int &timeCode, Date date, int partySize )
{
	cout << "\nChoose a time:\n";
	string Time[5] = { " ","11:30","13.30","17:45","19:45" };
	vector <int> temp;
	for (size_t i = 1; i <= 4; ++i)
	{
		if (availSeatsDatabase.availableTimes(date, i, partySize))
		{
			cout << i << ".  " << Time[i] << endl;
			temp.push_back(i);
		}
	}
	bool temp2 = false;
	while (1)
	{
		cout << "?";
		timeCode = inputAnInteger(1, 4);
		for (size_t i = 0; i < temp.size(); ++i)
			if (timeCode == temp[i] && timeCode > 0 && timeCode < 5)
			{
				temp2 = true;
				break;
			}
		if (temp2)
			break;
	}
}