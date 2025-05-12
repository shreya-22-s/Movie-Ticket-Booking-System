#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Customer {
    string userid, password;

public:
    void registration();
    bool login();
    void selectmovie();
    void cancelticket();
};

void Customer::registration() {
    cout << "Registration\nEnter username and password: ";
    cin >> userid >> password;

    ofstream fout("users.txt", ios::app);
    if (fout.is_open()) {
        fout << userid << " " << password << "\n";
        fout.close();
        cout << "Your registration is successful.\n";
    } else {
        cout << "Error opening file for registration.\n";
    }
}

bool Customer::login() {
    cout << "Login\nEnter username and password: ";
    cin >> userid >> password;

    ifstream fin("users.txt");
    string stored_user, stored_pass;
    bool found = false;

    while (fin >> stored_user >> stored_pass) {
        if (userid == stored_user && password == stored_pass) {
            found = true;
            break;
        }
    }
    fin.close();

    if (found) {
        cout << "Login successful.\n";
        return true;
    } else {
        cout << "Login failed. Incorrect username or password.\n";
        return false;
    }
}

void Customer::selectmovie() {
    int movie, quantity;
    cout << "\nSelect a movie:\n1. PLAYERS (?400)\n2. SHERSHAAH (?450)\n3. BELL BOTTOM (?460)\n4. BHUJ (?500)\n";
    cin >> movie;

    cout << "How many tickets do you want to buy? ";
    cin >> quantity;

    int price = 0;
    string movieName;
    switch (movie) {
        case 1: price = 400 * quantity; movieName = "PLAYERS"; break;
        case 2: price = 450 * quantity; movieName = "SHERSHAAH"; break;
        case 3: price = 460 * quantity; movieName = "BELL BOTTOM"; break;
        case 4: price = 500 * quantity; movieName = "BHUJ"; break;
        default: cout << "Invalid movie selection\n"; return;
    }

    cout << "Movie: " << movieName << "\nTickets: " << quantity << "\nTotal Price: ?" << price << endl;

    ofstream fout("bookings.txt", ios::app);
    fout << userid << " booked " << quantity << " tickets for " << movieName << " | Total: ?" << price << "\n";
    fout.close();
}

void Customer::cancelticket() {
    string id;
    cout << "Enter your ID to cancel ticket: ";
    cin >> id;

    ofstream fout("cancellations.txt", ios::app);
    fout << id << " canceled their ticket.\n";
    fout.close();

    cout << "Ticket canceled.\n";
}

int main() {
    Customer customer;
    int choice;

    while (true) {
        cout << "\n--- Movie Ticket Booking System ---\n";
        cout << "1. Register\n2. Login\n3. Select Movie\n4. Cancel Ticket\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: customer.registration(); break;
            case 2:
                if (!customer.login()) break;
                // Optionally allow next operations only after successful login
                break;
            case 3: customer.selectmovie(); break;
            case 4: customer.cancelticket(); break;
            case 5: cout << "Exiting program.\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }

    return 0;
}

