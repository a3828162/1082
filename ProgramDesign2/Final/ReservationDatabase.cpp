#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase()
{
	Date current;
	bool temp = true;
	computeCurrentDate(current);
    loadReservations();
    while (1)
    {
	    for (size_t i = 0; i < reservations.size(); ++i)
	    {
			if (reservations[i].getDate() < current || current == reservations[i].getDate())
			{
				reservations.erase(reservations.begin() + i);
				temp = false;
				break;
			}
	    }
		if (temp)
			break;
    }
}

ReservationDatabase::~ReservationDatabase()
{
    storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::exist( string phoneNumber )
{
	for (size_t i = 0; i < reservations.size(); ++i)
		if (reservations[i].getPhoneNumber() == phoneNumber)
			return true;
	return false;
}

void ReservationDatabase::displayReservationInfo( string phoneNumber )
{
	size_t j = 0;
	string Time[5] = { " ","11:30","13.30","17:45","19:45" };
	cout << endl;
	for(size_t i=0;i<reservations.size();++i)
		if (reservations[i].getPhoneNumber() == phoneNumber)
		{
			++j;
			cout << setw(2) << j << ". ";
			reservations[i].displayReservationInfo();
			cout << endl;
		}
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

void ReservationDatabase::loadReservations()
{
	ifstream inFile("Reservations.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened!" << endl;
		exit(1);
		system("PAUSE");
	}
	Reservation temp;
	while (inFile.read(reinterpret_cast<char *>(&temp), sizeof(Reservation)))
		reservations.push_back(temp);
	inFile.close();
}

void ReservationDatabase::storeReservations()
{
	ofstream outFile("Reservations.dat", ios::binary);
	if(!outFile)
	{
		cout << "File could not be opened!" << endl;
		exit(1);
		system("PAUSE");
	}
	for (size_t i = 0; i < reservations.size(); ++i)
		outFile.write(reinterpret_cast<char*>(&reservations[i]),sizeof(Reservation));
	outFile.close();
}