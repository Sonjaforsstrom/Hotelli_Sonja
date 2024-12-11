//Sonja Forsstr�m
//Hotelli
//4-5 pistett�

#include <iostream>
#include <vector> //Huoneiden dynaaminen taulukko
#include <string> 
#include <cstdlib> //Funktiot, satunnaisluvut
#include <ctime> //Auttaa satunnaisissa
#include <iomanip>  //Hinnat  tms.

using namespace std;

const int MAX_ROOMS = 300; //Enimm�is huonem��r�
const int MIN_ROOMS = 40; //Pienin huonem��r�
const double PRICE_SINGLE = 100.0; //1hh hinta
const double PRICE_DOUBLE = 150.0; //2hh hinta

// Huoneiden hallinta
struct Room {
    int number; //Huoneiden numerointi
    string type; // Huonetyypit (1hh tai 2hh)
    bool isBooked; //Tieto varauksista (onko vapaa)
};

//Varausten hallinta
struct Booking {
    int bookingNumber; //Varausnumero
    string customerName; //Asiakkaan nimi
    int roomNumber; //Huoneen numero
    int nights; //Kuinka monta y�t�
    double finalPrice; //Lopullinen hinta
};

// Funktio: Alustetaan huoneet
vector<Room> initializeRooms(int totalRooms) {
    vector<Room> rooms;
    for (int i = 0; i < totalRooms; ++i) {
        Room room;
        room.number = i + 1;
        room.type = (i < totalRooms / 2) ? "1hh" : "2hh";
        room.isBooked = false;
        rooms.push_back(room);
    }
    return rooms;
}

// Funktio: Tulosta vapaat huoneet
void displayAvailableRooms(const vector<Room>& rooms) {
    cout << "Vapaat huoneet:\n";
    for (const auto& room : rooms) {
        if (!room.isBooked) {
            cout << "Huone " << room.number << " (" << room.type << ")\n";
        }
    }
}

// Funktio: Hae vapaat huoneet
bool isRoomAvailable(const vector<Room>& rooms, int roomNumber) {
    for (const auto& room : rooms) {
        if (room.number == roomNumber && !room.isBooked) {
            return true;
        }
    }
    return false;
}

// Funktio: Varauksen tekeminen
Booking makeBooking(vector<Room>& rooms, int roomNumber, const string& name, int nights) {
    Booking booking;
    double pricePerNight = (rooms[roomNumber - 1].type == "1hh") ? PRICE_SINGLE : PRICE_DOUBLE; // Huoneen hinnan lasku
    double discountFactor = (rand() % 3 == 0) ? 0.9 : ((rand() % 3 == 1) ? 0.8 : 1.0); //Alennus: Jotta huoneiden hinnat eiv�t olisi aina t�sm�lleen samat (Satunnainen)

    booking.bookingNumber = 10000 + rand() % 90000; //Luodaan varausnumero
    booking.customerName = name;
    booking.roomNumber = roomNumber;
    booking.nights = nights;
    booking.finalPrice = nights * pricePerNight * discountFactor; //Lopullinen hinta

    rooms[roomNumber - 1].isBooked = true; //Varaus tehty

    return booking;
}

// Funktio: Hakee varauksen tiedot
void displayBooking(const Booking& booking) {
    cout << "Varausnumero: " << booking.bookingNumber << endl;
    cout << "Varaajan nimi: " << booking.customerName << endl;
    cout << "Huone numero: " << booking.roomNumber << endl;
    cout << "Oiden lukumaara: " << booking.nights << endl;
    cout << fixed << setprecision(2) << "Lopullinen hinta: " << booking.finalPrice << " euroa\n";
}

// Funktio: Hae varausnumerolla
void searchBookingByNumber(const vector<Booking>& bookings, int bookingNumber) {
    for (const auto& booking : bookings) {
        if (booking.bookingNumber == bookingNumber) {
            displayBooking(booking);
            return;
        }
    }
    cout << "Varausta ei loydy.\n";
}

    //Funktio: Hae varaus nimell�
void searchBookingByName(const vector<Booking>& bookings, const string& customerName) {
    bool found = false; { //Tarkistetaan l�ytyyk� varaus
        for (const auto& booking : bookings) {
            if (booking.customerName == customerName) {
                displayBooking(booking); //N�yt� varauksen tiedot
                found = true;
            }
        }
    }
    if (!found) {
        cout << "Varausta nimella " << customerName << " ei loydetty.\n";
    }
}
// P��ohjelma
int main() {
    srand(time(0)); //Nollataan satunnaisgeneraattori 

    int totalRooms = MIN_ROOMS + rand() % ((MAX_ROOMS - MIN_ROOMS) / 2) * 2; //Lasketaan huoneiden m��r� satunnaisesti aijemmin m��ritellylt� v�lilt�
    vector<Room> rooms = initializeRooms(totalRooms); //Vektori kaikista huoneista (varaamattomia)
    vector<Booking> bookings; //Tyhj� vektori tuleville varauksille

    int choice; //Valikon valinnat
    do {
        cout << "Tervetuloa Sonjan hotelliin! Miten voisimme auttaa tanaan? \n";
        cout << "\n--- Hotellin Varausjarjestelma ---\n";
        cout << "1. Nayta vapaat huoneet\n";
        cout << "2. Tee varaus\n";
        cout << "3. Hae varausnumerolla\n";
        cout << "4. Hae varaus nimella\n";
        cout << "5. Lopeta\n";
        cout << "Valinta: ";
        cin >> choice;

        //Eri valintojen toteutukset

        switch (choice) {
        case 1: //N�yt� vapaat huoneet
            displayAvailableRooms(rooms);
            break;
        case 2: { //Tee varaus
            string name;
            int roomNumber, nights;
            cout << "Anna varaajan nimi: ";
            cin.ignore(); //Mahdollistetaan v�lily�nnit
            getline(cin, name); //Mahdollistetaan v�lily�nnit
            cout << "Valitse huoneen numero: ";
            cin >> roomNumber;
            cout << "Anna oiden maara: ";
            cin >> nights;

            if (isRoomAvailable(rooms, roomNumber)) { //Varmistetaan onko huone vapaa
                Booking booking = makeBooking(rooms, roomNumber, name, nights); //Jos huone vapaana
                bookings.push_back(booking);
                displayBooking(booking);
            }
            else { //Jos huone ei ole vapaana
                cout << "Huone ei ole saatavilla.\n";
            }
            break;
        }
        case 3: { //Hae varausnumerolla
            int bookingNumber;
            cout << "Anna varausnumero: ";
            cin >> bookingNumber;
            searchBookingByNumber(bookings, bookingNumber); //Etsit��n varausta
            break;
        }
        case 4: { //Hae nimell�
            string customerName;
            cout << "Anna varauksen nimi: ";
            cin.ignore();
            getline(cin, customerName);
            searchBookingByName(bookings, customerName); //Etsit��n varaus
            break;
        }
        case 5: //Lopeta
            cout << "Ohjelma suljetaan.\n";
            break;
        default:
            cout << "Virheellinen valinta.\n"; //Mik�li numero ei ole 1-5
        }
    } while (choice != 5);

    return 0;
}