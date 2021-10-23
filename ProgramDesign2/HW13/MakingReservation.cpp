// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

extern int inputAnInteger( int begin, int end );

extern string departureTimes[ 37 ];

extern string Station[13];

// MakingReservation constructor
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      SouthboundTimetable &theSouthboundTimetable,
                                      NorthboundTimetable &theNorthboundTimetable )
   : reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
}

void MakingReservation::execute()
{
   if( chooseTrain() ) // displays timetables for 10 coming trains, then let user choose a train
   {
      inputReservationDetails();

      inputContactPersonInfo();

      reservationDatabase.addReservation( reservation );

      cout << "\nReservation Completed!\n";
   }
   else
      cout << "\nSorry! No train is available!\n";
}

bool MakingReservation::chooseTrain()
{
    size_t temp = 0, temptime = 0;
    while (1)
    {
        cout << "Origin Station\n";
        for (size_t i = 1; i <= 12; ++i)
            cout << i << ". " << Station[i] << endl;
        do cout << "? ";
        while ((temp = inputAnInteger(1, 12)) == -1);
        reservation.setOriginStation(temp);
        cout << "\nDestination Station\n";
        for (size_t i = 1; i <= 12; ++i)
            cout << i << ". " << Station[i] << endl;
        do cout << "? ";
        while ((temp = inputAnInteger(1, 12)) == -1);
        reservation.setDestinationStation(temp);
        if (reservation.getOriginStation() != reservation.getDestinationStation())
            break;
    }
    cout << "\nDeparture Time\n";
    for (size_t i = 1; i <= 36; ++i)
        cout << i << ". " << departureTimes[i] << endl;
    do cout << "? ";
    while ((temptime = inputAnInteger(1, 36)) == -1);
    if (reservation.getOriginStation() > reservation.getDestinationStation())
    {
        if (!northboundTimetable.trainsAvailable(temptime, reservation.getOriginStation(), reservation.getDestinationStation()))
            return false;
        northboundTimetable.displayComingTrains(temptime, reservation.getOriginStation(), reservation.getDestinationStation());
    }
    else
    {
        if (!southboundTimetable.trainsAvailable(temptime, reservation.getOriginStation(), reservation.getDestinationStation()))
            return false;
        southboundTimetable.displayComingTrains(temptime, reservation.getOriginStation(), reservation.getDestinationStation());
    }
    string tr;
    cout << "\nEnter Train Number: ";
    cin >> tr;
    reservation.setTrainNumber(tr);
    return true;
}

void MakingReservation::inputReservationDetails()
{
   cout << "\nCar Class\n" << "1. Standard Car\n" << "2. Business Car";
   int carClass;
   do cout << "\n? ";
   while( ( carClass = inputAnInteger( 1, 2 ) ) == -1 );
   
   reservation.setCarClass( carClass );

	cout << "\nDeparture Date: ";

   char date[12];
   cin >> date;
   reservation.setDate( date );
   cin.ignore();

	cout << "\nHow many adult tickets? ";

   int adultTickets;
   cin >> adultTickets;
   reservation.setAdultTickets( adultTickets );

	cout << "\nHow many concession tickets? ";

   int concessionTickets;
   cin >> concessionTickets;
   reservation.setConcessionTickets( concessionTickets );

   cout << "\nTrip Details\n";
   reservation.displayReservationDetails();
}

void MakingReservation::inputContactPersonInfo()
{
   cout << "\n\nEnter Contact Person Information\n\n";

   cout << "ID Number: ";
   string idNumber;
   cin >> idNumber;
   reservation.setIdNumber( idNumber );

   cout << "\nPhone: ";
   string phone;
   cin >> phone;
   cin.ignore();
   reservation.setPhone( phone );

   srand( static_cast< unsigned int >( time( 0 ) ) );
   char reservationNumber[ 12 ];
   for( int i = 0; i < 8; i++ )
      reservationNumber[ i ] = rand() % 10 + '0';
   reservationNumber[ 8 ] = '\0';
   reservation.setReservationNumber( reservationNumber );
   
	cout << "\nReservation Number: " << reservationNumber << endl;
}