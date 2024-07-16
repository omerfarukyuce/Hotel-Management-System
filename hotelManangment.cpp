#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Room class
class Room {
protected:
    string roomNumber;
    string status;

public:
    Room() {}
    Room(string number, string status) : roomNumber(number), status(status) {}

    void setStatus(string newStatus) {
        status = newStatus;
    }

    string getStatus() const {
        return status;
    }

    string getRoomNumber() const {
        return roomNumber;
    }
};

// SuitRoom class (derived from Room)
class SuitRoom : public Room {
public:
    SuitRoom(string number, string status) : Room(number, status) {}
};

// StandardRoom class (derived from Room)
class StandardRoom : public Room {
public:
    StandardRoom(string number, string status) : Room(number, status) {}
};

// Hotel class
class Hotel {
private:
    static const int totalRooms = 10;
    Room* rooms[totalRooms];

public:
    Hotel() {
        for (int i = 0; i < totalRooms; ++i) {
            if (i < 5)
                rooms[i] = new SuitRoom("S" + to_string(i + 1), "Available");
            else
                rooms[i] = new StandardRoom("R" + to_string(i - 4), "Available");
        }
    }

    void displayRooms() {
        cout << "Room Status:" << endl;
        for (int i = 0; i < totalRooms; ++i) {
            cout << "Room " << rooms[i]->getRoomNumber() << ": " << rooms[i]->getStatus() << endl;
        }
    }

    void updateRoomStatus(string roomNumber, string newStatus) {
        for (int i = 0; i < totalRooms; ++i) {
            if (rooms[i]->getRoomNumber() == roomNumber) {
                rooms[i]->setStatus(newStatus);
                cout << "Room " << roomNumber << " status updated." << endl;
                return;
            }
        }
        cout << "Room not found!" << endl;
    }

    void saveToFile() {
        ofstream outFile("hotel_status.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < totalRooms; ++i) {
                outFile << rooms[i]->getRoomNumber() << " " << rooms[i]->getStatus() << endl;
            }
            outFile.close();
            cout << "Hotel status saved to file." << endl;
        }
        else {
            cout << "Unable to open file!" << endl;
        }
    }

    void retrieveFromFile() {
        ifstream inFile("hotel_status.txt");
        if (inFile.is_open()) {
            string roomNumber, status;
            while (inFile >> roomNumber >> status) {
                cout << "Room " << roomNumber << ": " << status << endl;
            }
            inFile.close();
        }
        else {
            cout << "Unable to open file!" << endl;
        }
    }

    ~Hotel() {
        for (int i = 0; i < totalRooms; ++i) {
            delete rooms[i];
        }
    }
};

int main() {
    Hotel hotel;
    int choice;
    string roomNumber, newStatus;

    do {
        cout << "\n--- Hotel Management System ---" << endl;
        cout << "1. Show Rooms" << endl;
        cout << "2. Update Room Status" << endl;
        cout << "3. Save Hotel Status to File" << endl;
        cout << "4. Load Hotel Status from File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "'S' for suit rooms. 'R' for standard rooms. ";
            hotel.displayRooms();
            break;
        case 2:
            cout << "Enter room number: ";
            cin >> roomNumber;
            cout << "Enter new status (Occupied/Available/Cleaning): ";
            cin >> newStatus;
            hotel.updateRoomStatus(roomNumber, newStatus);
            break;
        case 3:
            hotel.saveToFile();
            break;
        case 4:
            hotel.retrieveFromFile();
            break;
        case 0:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
