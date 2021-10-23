#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string.h>
#include <ctime>
using namespace std;

int adultTicketPrice[13][13] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char Station[12][9] =
{
 "Nangang", "Taipei", "Banqiao" , "Taoyuan",
 "Hsinchu", "Miaoli", "Taichung","Changhua",
 "Yunlin" , "Chiayi", "Tainan"  ,"Zuoying"
};

char departureTimes[37][8] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };

struct Reservation
{
    char reservationNumber[12]; // used to identify a reservation  訂位代號
    char trainNumber[8]; // used to identify a train  車次號碼
    char idNumber[12]; // the id number of the contact person  取票人的身分證字號
    char phone[12]; // the (local or mobile) phone number of the contact person  取票人的聯絡電話
    char date[12]; // outbound date  搭乘日期
    int originStation; // the origin station code  起程站代碼
    int destinationStation; // the destination station code  到達站代碼
    int carClass; // the car class code; 1:standard car, 2:business car  車廂種類; 1:標準車廂, 2:商務車廂
    int adultTickets; // the number of adult tickets  全票張數
    int concessionTickets; // the number of concession tickets  優待票張數
};

struct Train
{
    char trainNumber[8]; // used to identify a train  車次號碼
    char departureTimes[13][8]; // the departure time of a train for each station  火車在各站的離站時間
};

class BOOK
{
public:
    BOOK();
	~BOOK();
    int InputAnInteger(int begin, int end);
	void LoadNorthBound();
	void LoadSouthBound();
    void LoadRe();
    void Booking();
    void NorthBooking();
    void SouthBooking();
    void Display();
    void Booking_History();
    bool Set();
    void Cancellation();
    void Reduce();
    void Save();
private:
    vector < Train > NorthTrain;
    vector < Train > SouthTrain;
    vector < Reservation > Re;
    Reservation ReservationDetail;
};

BOOK::BOOK()
    :ReservationDetail()
{
    LoadNorthBound();
    LoadSouthBound();
    LoadRe();
}

BOOK::~BOOK()
{
}

int BOOK::InputAnInteger(int begin, int end)
{
    char a[50];
    cin.getline(a, 50);
    if (!strlen(a)) {
        cin.getline(a, 50);
    }
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] < '0' || a[i]>'9') {
            return -1;
        }
    }

    int n = atoi(a);

    if (n >= begin && n <= end) {
        return n;
    }
    else {
        return -1;
    }
}

void BOOK::LoadNorthBound()
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
        NorthTrain.push_back(in);
    inFile.close();
}

void BOOK::LoadSouthBound()
{
    ifstream inFile("Southbound timetable.dat", ios::in | ios::binary);

    if (!inFile) {
        cout << "File could not be opened";
        system("pause");
        exit(1);
    }
    //inFile.open("Northbound timetable.dat", ios::binary);
    Train in;
    while (inFile.read((char*)(&in), sizeof(Train)))
        SouthTrain.push_back(in);
    inFile.close();
}

void BOOK::LoadRe()
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
            Re.push_back(in);
    }
    inFile.close();
}

void BOOK::Booking()
{
    while (1)
    {
        cout << "\nOriginal Station\n";
        for (int i = 0; i < 12; i++)
            cout << i + 1 << ". " << Station[i] << endl;
        do cout << "? ";
        while ((ReservationDetail.originStation = InputAnInteger(1, 12)) == -1);
        cout << "\nDestination Station\n";
        for (int i = 0; i < 12; i++)
            cout << i + 1 << ". " << Station[i] << endl;
        do cout << "? ";
        while ((ReservationDetail.destinationStation = InputAnInteger(1, 12)) == -1);
        if (ReservationDetail.originStation != ReservationDetail.destinationStation)
            break;
        else
            cout << "\nYou can't choose same station!\n";
    }

    if (ReservationDetail.originStation < ReservationDetail.destinationStation)
        SouthBooking();
    else if (ReservationDetail.originStation > ReservationDetail.destinationStation)
        NorthBooking();
    Re.push_back(ReservationDetail);
}

void BOOK::NorthBooking()
{
    int DepartureTime;
    cout << "\nCar Class\n1. Standard Car\n2. Business Car\n";
    do cout << "? ";
    while ((ReservationDetail.carClass = InputAnInteger(1, 2)) == -1);
    if (ReservationDetail.carClass == 2 && (ReservationDetail.originStation >= 1 && ReservationDetail.originStation <= 3) && (ReservationDetail.destinationStation >= 1 && ReservationDetail.destinationStation <= 3))
    {
        cout << "\nDon't have train!\n\n";
        return;
    }
    cout << "\nDeparture Date: ";
    cin >> ReservationDetail.date;
    cout << "\nDeparture Time\n";
    for (int i = 1; i < 37; ++i)
        cout << i << ". " << departureTimes[i] << endl;
    do cout << "? ";
    while ((DepartureTime = InputAnInteger(1, 37)) == -1);
    cout << "\nHow many adult tickets? ";
    cin >> ReservationDetail.adultTickets;
    cout << "\nHow many concession tickets? ";
    cin >> ReservationDetail.concessionTickets;
    cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    unsigned int j = 0;
    vector < Train > in;
    for (unsigned int i = 0; i < NorthTrain.size(); ++i)
    {
        if (strcmp(departureTimes[DepartureTime], NorthTrain[i].departureTimes[13 - ReservationDetail.originStation]) != 1 && strcmp(NorthTrain[i].departureTimes[13 - ReservationDetail.destinationStation] , "-")!=0)
        {
            j++;
            cout << setw(9) << NorthTrain[i].trainNumber << setw(11) << NorthTrain[i].departureTimes[13-ReservationDetail.originStation]
                << setw(9) << NorthTrain[i].departureTimes[13-ReservationDetail.destinationStation] << endl;
            in.push_back(NorthTrain[i]);
        }
        if (j == 10)
            break;
    }
    if (j == 0)
    {
        cout << "\nNo Train!\n";
        return;
    }
    while (1)
    {
        cout << "\nEnter Train Number: ";
        cin >> ReservationDetail.trainNumber;
        bool h = false;
        for (size_t i = 0; i < in.size(); ++i)
            if (strcmp(ReservationDetail.trainNumber, in[i].trainNumber) == 0)
            {
                h = true;
                break;
            }
        if (h)
            break;
        cout << "\nPlease Enter Right Train Number!\n";
    }
    cout << "\nTrip Details\n";
    Display();
    cout << "\n\nEnter Contact Person Information\n\nID number: ";
    cin >> ReservationDetail.idNumber;
    cout << "\nPhone: ";
    cin >> ReservationDetail.phone;
    srand(unsigned(time(0)));
    for (size_t i = 0; i < 8; ++i)
        ReservationDetail.reservationNumber[i] = rand() % 10 + '0';
    ReservationDetail.reservationNumber[8] = '/0';
    cout << "\nReservation Number: " << ReservationDetail.reservationNumber;
    cout << "\n\nReservation Completed!\n\n";
}

void BOOK::SouthBooking()
{
    int DepartureTime;
    cout << "\nCar Class\n1. Standard Car\n2. Business Car\n";
    do cout << "? ";
    while ((ReservationDetail.carClass = InputAnInteger(1, 2)) == -1);
    if (ReservationDetail.carClass == 2 && (ReservationDetail.originStation >= 1 && ReservationDetail.originStation <= 3) && (ReservationDetail.destinationStation >= 1 && ReservationDetail.destinationStation <= 3))
    {
        cout << "\nDon't have train!\n\n";
        return;
    }
    cout << "\nDeparture Date: ";
    cin >> ReservationDetail.date;
    cout << "\nDeparture Time\n";
    for (int i = 1; i < 37; ++i)
        cout << i << ". " << departureTimes[i] << endl;
    do cout << "? ";
    while ((DepartureTime = InputAnInteger(1, 37)) == -1);
    cout << "\nHow many adult tickets? ";
    cin >> ReservationDetail.adultTickets;
    cout << "\nHow many concession tickets? ";
    cin >> ReservationDetail.concessionTickets;
    cout << setw(9) << "\nTrain NO." << setw(11) << "Departure" << setw(9) << "Arrival" << endl;
    unsigned int j = 0;
    vector < Train > in;
    for (unsigned int i = 0; i < SouthTrain.size(); ++i)
    {
        if (strcmp(departureTimes[DepartureTime], SouthTrain[i].departureTimes[ReservationDetail.originStation]) != 1 && strcmp(SouthTrain[i].departureTimes[ReservationDetail.destinationStation], "-"))
        {
            j++;
            cout << setw(9) << SouthTrain[i].trainNumber << setw(11) << SouthTrain[i].departureTimes[ReservationDetail.originStation]
                << setw(9) << SouthTrain[i].departureTimes[ReservationDetail.destinationStation] << endl;
            in.push_back(SouthTrain[i]);
        }
        if (j == 10)
            break;
    }
    if (j == 0)
    {
        cout << "\nNo Train!\n";
        return;
    }
    while (1)
    {
        cout << "\nEnter Train Number: ";
        cin >> ReservationDetail.trainNumber;
        bool h = false;
        for (size_t i = 0; i < in.size(); ++i)
            if (strcmp(ReservationDetail.trainNumber, in[i].trainNumber) == 0)
            {
                h = true;
                break;
            }
        if (h)
            break;
        cout << "\nPlease Enter Right Train Number!\n";
    }
    cout << "\nTrip Details\n";
    Display();
    cout << "\n\nEnter Contact Person Information\n\nID number: ";
    cin >> ReservationDetail.idNumber;
    cout << "\nPhone: ";
    cin >> ReservationDetail.phone;
    srand(unsigned(time(0)));
    for (size_t i = 0; i < 8; ++i)
        ReservationDetail.reservationNumber[i] = rand() % 10 + '0';
    ReservationDetail.reservationNumber[8] = '/0';
    cout << "\nReservation Number: " << ReservationDetail.reservationNumber;
    cout << "\n\nReservation Completed!\n\n";
}

void BOOK::Display()
{
    cout << endl;
    cout << setw(10) << "Date" << setw(11) << "Train NO." << setw(10) << "From" << setw(10) << "To" << setw(11)
        << "Departure" << setw(9) << "Arrival" << setw(8) << "Adult" << setw(12) << "Concession" << setw(6) << "Fare"
        << setw(10) << "Class" << endl;
    cout << setw(10) << ReservationDetail.date << setw(11) << ReservationDetail.trainNumber;
    if (ReservationDetail.originStation < ReservationDetail.destinationStation)
    {
        cout << setw(10) << Station[ ReservationDetail.originStation-1]
            << setw(10) << Station[ ReservationDetail.destinationStation-1];
        size_t q = 0;
        for (q = 0; q < SouthTrain.size(); ++q)
            if (!strcmp(SouthTrain[q].trainNumber, ReservationDetail.trainNumber))
                break;
        cout << setw(11) << SouthTrain[q].departureTimes[ ReservationDetail.originStation]
            << setw(9) << SouthTrain[q].departureTimes[ ReservationDetail.destinationStation];
        if (ReservationDetail.carClass == 1)
        {
            cout << setw(6) << adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation]
                << "*" << ReservationDetail.adultTickets
                << setw(10) << adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation] / 2
                << "*" << ReservationDetail.concessionTickets
                << setw(6) << (adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation]) * ReservationDetail.adultTickets + (adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation] / 2) * ReservationDetail.concessionTickets
                << setw(10) << "Standard";
        }
        else
        {
            cout << setw(6) << adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation]
                << "*" << ReservationDetail.adultTickets
                << setw(10) << adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation] / 2
                << "*" << ReservationDetail.concessionTickets
                << setw(6) << (adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation]) * ReservationDetail.adultTickets + (adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation] / 2) * ReservationDetail.concessionTickets
                << setw(10) << "Bussiness";
        }
    }
    else
    {
        cout << setw(10) << Station[ReservationDetail.originStation-1]
            << setw(10) << Station[ReservationDetail.destinationStation-1];
        size_t q = 0;
        for (q = 0; q < NorthTrain.size(); ++q)
            if (!strcmp(NorthTrain[q].trainNumber , ReservationDetail.trainNumber))
                break;
        
        cout << setw(11) << NorthTrain[q].departureTimes[13-ReservationDetail.originStation]
            << setw(9) << NorthTrain[q].departureTimes[13-ReservationDetail.destinationStation];

        if (ReservationDetail.carClass == 1)
        {
            cout << setw(6) << adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation]
                << "*" << ReservationDetail.adultTickets
                << setw(10) << adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation] / 2
                << "*" << ReservationDetail.concessionTickets
                << setw(6) << (adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation]) * ReservationDetail.adultTickets + (adultTicketPrice[ReservationDetail.originStation][ReservationDetail.destinationStation] / 2) * ReservationDetail.concessionTickets
                << setw(10) << "Standard";
        }
        else
        {
            cout << setw(6) << adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation]
                << "*" << ReservationDetail.adultTickets
                << setw(10) << adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation] / 2
                << "*" << ReservationDetail.concessionTickets
                << setw(6) << (adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation]) * ReservationDetail.adultTickets + (adultTicketPrice[ReservationDetail.destinationStation][ReservationDetail.originStation] / 2) * ReservationDetail.concessionTickets
                << setw(10) << "Bussiness";
        }
    }
}

void BOOK::Booking_History()
{
    while (1)
    {
        if (Set())
            break;
        else
            cout << "\nWrong!" << endl;
    }
    cout << "\nReservation Detials\n";
    Display();

    cout << "\n\nEnter Your Choice\n1. Cancellation\n2. Reduce\n3. End\n?";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        Cancellation();
        return;
    case 2:
        Reduce();
        return;
    case 3:
        return;
    default:
        break;
    }
}

bool BOOK::Set()
{
    cout << "\nEnter ID Number: ";
    char ID[12], RN[12];
    cin >> ID;
    cout << "\nEnter Reservation Number: ";
    cin >> RN;
    for (size_t i = 0; i < Re.size(); ++i)
        if (strcmp(ID, Re[i].idNumber) == 0 && strcmp(RN, Re[i].reservationNumber) == 0)
        {
            ReservationDetail = Re[i];
            return true;
        }
    return false;
}

void BOOK::Cancellation()
{
    cout << Re.size() << endl;
    for (size_t i = 0; i < Re.size(); ++i)
    {
        if (strcmp(ReservationDetail.reservationNumber, Re[i].reservationNumber) == 0)
        {
            Re.erase(Re.begin() + i);
            cout << "Hello" << endl;
            break;
        }
    }

    cout << "\nReservation Cancelled.\n" << endl;
    return;
}

void BOOK::Reduce()
{
    while (1)
    {
        int a = 0, b = 0;
        cout << "\nHow many adult tickets to cancel? ";
        cin >> a;
        cout << "\nHow many concession tickets to cancel? ";
        cin >> b;
        if (ReservationDetail.adultTickets > a&& ReservationDetail.concessionTickets > b)
        {
            ReservationDetail.adultTickets -= a;
            ReservationDetail.concessionTickets -= b;
            Display();
            cout << "\n\nYou have successfully reduced the number of tickets!\n" << endl;
            for (size_t i = 0; i < Re.size(); ++i)
                if (strcmp(ReservationDetail.idNumber, Re[i].idNumber) == 0 && strcmp(ReservationDetail.reservationNumber, Re[i].reservationNumber) == 0)
                {
                    Re[i].adultTickets -= a;
                    Re[i].concessionTickets -= b;
                }
            return;
        }
        else if ((ReservationDetail.adultTickets == a && ReservationDetail.concessionTickets > b) || (ReservationDetail.adultTickets > a && ReservationDetail.concessionTickets == b))
        {
            ReservationDetail.adultTickets -= a;
            ReservationDetail.concessionTickets -= b;
            Display();
            cout << "\n\nYou have successfully reduced the number of tickets!\n" << endl;
            for (size_t i = 0; i < Re.size(); ++i)
                if (strcmp(ReservationDetail.idNumber, Re[i].idNumber) == 0 && strcmp(ReservationDetail.reservationNumber, Re[i].reservationNumber) == 0)
                {
                    Re[i].adultTickets -= a;
                    Re[i].concessionTickets -= b;
                }
            return;
        }
        else
        {
            cout << "Tickets couldn't less than 0!" << endl;
            return;
        }
    }
}

void BOOK::Save()
{
    ofstream outFile("Reservation details.dat", ios::binary | ios::out);
    if (!outFile) {
        cout << "File could not be opened!" << endl;
        system("pause");
        exit(1);
    }
    for (size_t i = 0; i < Re.size(); ++i)
        outFile.write((char*)(&Re[i]), sizeof(Reservation));
    outFile.close();
}
#endif // !BOOK_H

