// FlightSchedule.cpp
// Member-function definitions for class SouthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SouthboundTimetable.h"

extern string departureTimes[ 37 ];

// SouthboundTimetable default constructor
// loads southbound timetable from the file "Southbound timetable.dat"
SouthboundTimetable::SouthboundTimetable()
{
   loadSouthboundTimetable();
}

void SouthboundTimetable::loadSouthboundTimetable()
{
    ifstream inFile("Southbound timetable.dat", ios::in, ios::binary);

    if (!inFile) {
        cout << "File could not be opened";
        system("pause");
        exit(1);
    }
    //inFile.open("Northbound timetable.dat", ios::binary);
    Train in;
    while (inFile.read((char*)(&in), sizeof(Train)))
        southboundTimetable.push_back(in);
    inFile.close();
}

// returns departureTimes[ station ]
string SouthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool SouthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (size_t i = 0; i < southboundTimetable.size(); ++i)
    {
        if (departureTimes[departureTime] <= southboundTimetable[i].getDepartureTimes(originStation) && southboundTimetable[i].getDepartureTimes(originStation) != "-" && southboundTimetable[i].getDepartureTimes(destinationStation) != "-")
            return true;
    }
    return false;
}

void SouthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    size_t a = 0;
    cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    for (size_t i = 0; i < southboundTimetable.size(); ++i)
    {
        if ((departureTimes[departureTime] <= southboundTimetable[i].getDepartureTimes(originStation)) && (southboundTimetable[i].getDepartureTimes(destinationStation) != "-"))
        {
            a++;
            cout << setw(9) << southboundTimetable[i].getTrainNumber() << setw(11) << southboundTimetable[i].getDepartureTimes(originStation)
                << setw(9) << southboundTimetable[i].getDepartureTimes(destinationStation) << endl;
        }
        if (a == 10)
            break;
    }
    return;
}

vector< Train >::iterator SouthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = southboundTimetable.begin();
   for( ; it != southboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return southboundTimetable.end();
}