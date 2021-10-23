#include <iostream>
#include "ReservationHistory.h" // ReservationHistory class definition

extern int inputAnInteger( int begin, int end );

// ReservationHistory default constructor
ReservationHistory::ReservationHistory( ReservationDatabase &theReservationDatabase,
                                        SouthboundTimetable &theSouthboundTimetable,
                                        NorthboundTimetable &theNorthboundTimetable )
   : idNumber(),
     reservationNumber(),
     reservationDatabase( theReservationDatabase ),
     southboundTimetable( theSouthboundTimetable ),
     northboundTimetable( theNorthboundTimetable )
{
} // end ReservationHistory default constructor

void ReservationHistory::execute()
{
    string ID, ReNum;
    cout << "Enter ID Number: ";
    cin >> ID;
    cout << "\nEnter Reservation Number: ";
    cin >> ReNum;
    while (1)
    {
        int temp = 0;
        if (reservationDatabase.exist(ID, ReNum))
        {
            cout << "\nReservation Details\n";
            reservationDatabase.displayReservation(ID, ReNum);
            cout << "\n\nEnter Your Choice\n1. Cancellation\n2. Reduce\n3. End\n";
            do cout << "? ";
            while ((temp = inputAnInteger(1, 3)) == -1);
            switch (temp)
            {
            case 1:
                reservationDatabase.cancelReservation(ID, ReNum);
                break;
            case 2:
                reservationDatabase.reduceSeats(ID, ReNum);
                break;
            case 3:
                return;
            default:
                break;
            }
            break;
        }
        else
        {
            cout << "\nReservation record not found.\n";
            return;
        }
    }
}