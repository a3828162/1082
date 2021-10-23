// NorthboundTimetable.cpp
// Member-function definitions for class NorthboundTimetable.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "NorthboundTimetable.h"

extern string departureTimes[ 37 ];

extern string Station[13];

// NorthboundTimetable default constructor
// loads northbound timetable from the file "Northbound timetable.dat"
NorthboundTimetable::NorthboundTimetable()
{
   loadNorthboundTimetable();
}

void NorthboundTimetable::loadNorthboundTimetable()
{
    ifstream inFile("Northbound timetable.dat", ios::in, ios::binary);

    if (!inFile) {
        cout << "File could not be opened";
        system("pause");
        exit(1);
    }
    //inFile.open("Northbound timetable.dat", ios::binary);
    Train in;
    while (inFile.read((char*)(&in), sizeof(Train)))
        northboundTimetable.push_back(in);
    inFile.close();
}

// returns departureTimes[ station ]
string NorthboundTimetable::getDepartureTimes( string trainNumber, int station )
{
   vector< Train >::iterator it = searchTrain( trainNumber );
   return it->getDepartureTimes( station );
}

bool NorthboundTimetable::trainsAvailable( int departureTime,
     int originStation, int destinationStation )
{
    for (size_t i = 0; i < northboundTimetable.size(); ++i)
    {
        if (departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes(13 - originStation) && northboundTimetable[i].getDepartureTimes(13 - originStation) != "-" && northboundTimetable[i].getDepartureTimes(13 - destinationStation) != "-")
            return true;
    }
    return false;
}

void NorthboundTimetable::displayComingTrains( int departureTime,
     int originStation, int destinationStation )
{
    size_t a = 0;
    cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    for (size_t i = 0; i < northboundTimetable.size(); ++i)
    {
        if ((departureTimes[departureTime] <= northboundTimetable[i].getDepartureTimes(13-originStation)) && (northboundTimetable[i].getDepartureTimes(13-destinationStation) != "-"))
        {
            a++;
            cout << setw(9) << northboundTimetable[i].getTrainNumber() << setw(11) << northboundTimetable[i].getDepartureTimes(13-originStation)
                << setw(9) << northboundTimetable[i].getDepartureTimes(13-destinationStation) << endl;
        }
        if (a == 10)
            break;
    }
    return;
}

vector< Train >::iterator NorthboundTimetable::searchTrain( string trainNumber )
{
   vector< Train >::iterator it = northboundTimetable.begin();
   for( ; it != northboundTimetable.end(); ++it )
      if( it->getTrainNumber() == trainNumber )
         return it;

   return northboundTimetable.end();
}