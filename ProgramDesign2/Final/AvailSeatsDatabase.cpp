#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailSeatsDatabase.h"

AvailSeatsDatabase::AvailSeatsDatabase()
{
	int seats[5] = { 0,20,20,20,20 };
	loadAvailSeats();
	if (availSeats.size() == 0)
	{
		for (size_t i = 1; i <= 30; ++i)
		{
			Date current;
			computeCurrentDate(current);
			current + i;
			AvailSeats temp(current, seats);
			availSeats.push_back(temp);
		}
	}
	else
	{
		Date current;
		computeCurrentDate(current);
		if (availSeats[0].getDate() < current)
		{
			int temp2 = current - availSeats[0].getDate();
			for (size_t i = 0; i <= temp2; ++i)
				availSeats.erase(availSeats.begin()); //modify
			for (int i = temp2; i >= 0; --i)
			{
				Date temp3;
				computeCurrentDate(temp3);
				temp3 + (30-i);
				AvailSeats temp(temp3, seats);
				availSeats.push_back(temp);
			}
		}
		else if (availSeats[0].getDate() == current)
		{
			availSeats.erase(availSeats.begin()); //modify
			current + 30;
			AvailSeats temp(current, seats);
			availSeats.push_back(temp);
		}
	}
}

AvailSeatsDatabase::~AvailSeatsDatabase()
{
   storeAvailSeats();
}

void AvailSeatsDatabase::decreaseAvailSeats( Date date, int timeCode, int requiredSeats )
{
	auto it = searchAvailSeats(date);
	it->setNumAvailSeats(timeCode, (it->getNumAvailSeats(timeCode) - requiredSeats));
}

bool AvailSeatsDatabase::availableTimes( Date date, int requiredSeats )
{
	auto it = searchAvailSeats(date);
	for (size_t j = 1; j <= 4; ++j)
	{
		if (it->getNumAvailSeats(j) >= requiredSeats)
		{
			return true;
		}
	}
	return false;
}

bool AvailSeatsDatabase::availableTimes( Date date, int timeCode, int requiredSeats )
{
	auto it = searchAvailSeats(date);
	if (it->getNumAvailSeats(timeCode) >= requiredSeats)
		return true;
	else
		return false;

	return false;
}

vector< AvailSeats >::iterator AvailSeatsDatabase::searchAvailSeats( Date date )
{
	for (size_t i = 0; i < availSeats.size(); ++i)
	{
		if(availSeats[i].getDate()==date)
			return availSeats.begin() + i;
	}
	
}

void AvailSeatsDatabase::loadAvailSeats()
{
	ifstream inFile("AvailSeats.dat", ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened!" << endl;
		exit(1);
		system("PAUSE");
	}
	AvailSeats temp;
	while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(AvailSeats)))
		availSeats.push_back(temp);
	inFile.close();
}

void AvailSeatsDatabase::storeAvailSeats()
{
	ofstream outFile("AvailSeats.dat", ios::binary);
	if (!outFile)
	{
		cout << "File could not be opened!" << endl;
		exit(1);
		system("PAUSE");
	}
	for (size_t i = 0; i < availSeats.size(); ++i)
		outFile.write(reinterpret_cast<char*>(&availSeats[i]), sizeof(AvailSeats));
	outFile.close();
}