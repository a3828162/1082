// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <fstream>
using namespace std;
#include "ReservationDatabase.h"

// ReservationDatabase default constructor loads reservations from the file Reservation details.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores reservations into the file Reservation details.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::loadReservations()
{
    ifstream inFile("Reservation details.dat", ios::in | ios::binary);

    if (!inFile)
    {
        ofstream m("Reservation details.dat", ios::binary | ios::out);
    }
    else
    {
        Reservation in;
        while (inFile.read((char*)(&in), sizeof(Reservation)))
            reservations.push_back(in);
    }
    inFile.close();
}

void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservation details.dat", ios::binary | ios::out);
    if (!outFile) {
        cout << "File could not be opened!" << endl;
        system("pause");
        exit(1);
    }
    for (size_t i = 0; i < reservations.size(); ++i)
        outFile.write((char*)(&reservations[i]), sizeof(Reservation));
    outFile.close();
}

bool ReservationDatabase::exist( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return true; // return true if match found

   return false; // if no matching reservation was found, return false
}

void ReservationDatabase::displayReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   it->displayReservationDetails();
}

void ReservationDatabase::cancelReservation( string idNumber, string reservationNumber )
{
   vector< Reservation >::iterator it = searchReservation( idNumber, reservationNumber );
   reservations.erase( it );
   cout << "\nReservation Cancelled.\n";
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::reduceSeats( string idNumber, string reservationNumber )
{
    size_t ad = 0, co = 0;
    cout << "\nHow many adult tickets to cancel? ";
    cin >> ad;
    cout << "\nHow many comcession tickets to cancel?";
    cin >> co;
    auto it = searchReservation(idNumber, reservationNumber);
    if ((it->getAdultTickets() - ad >= 0 && it->getConcessionTickets() - co >= 0) && (it->getAdultTickets() - ad != 0 || it->getConcessionTickets() - co != 0))
    {
        it->setAdultTickets(it->getAdultTickets() - ad);
        it->setConcessionTickets(it->getConcessionTickets() - co);
        displayReservation(idNumber, reservationNumber);
        cout << "\n\nYou have successfully reduced the number of tickets!\n";
        return;
    }
    else
    {
        cout << "\nYou don't have enough tickets!\n";
        return;
    }
}

vector< Reservation >::iterator ReservationDatabase::searchReservation( string idNumber, string reservationNumber )
{
   // loop through reservations searching for matching idNumber and reservationNumber
   for( vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it )
      if( it->getIdNumber() == idNumber && it->getReservationNumber() == reservationNumber )
         return it; // return iterator to thecurrent reservation if match found

   return reservations.end();
}