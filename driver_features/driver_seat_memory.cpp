/**
 * @file driver_seat_memory.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Driver Seat Memory System.
 *   It stores seat position readings and
 *   restores the saved seat position.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 10-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> seatPositions;

public:

    /**
     * @brief Input seat position readings
     */
    void inputReadings() {

        int n, position;

        cout << "Enter number of seat positions: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter seat position (" << i + 1 << "): ";
            cin >> position;

            seatPositions.push_back(position);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Driver Seat Memory System
 */
class DriverSeatMemory : public Sensor {

public:

    /**
     * @brief Save and restore seat position
     */
    void checkStatus() override {

        cout << "\n===== Driver Seat Memory Report =====\n";

        if(seatPositions.empty()) {

            cout << "No seat position stored.\n";
            return;
        }

        cout << "Saved Seat Positions:\n";

        for(int position : seatPositions) {

            cout << "Position : " << position << endl;
        }

        cout << "\nRestoring Driver Seat Position...\n";
        cout << "Seat Adjusted to Position : "
             << seatPositions.back()
             << " ✅\n";
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    DriverSeatMemory seat;

    sensor = &seat;

    seat.inputReadings();

    sensor->checkStatus();

    return 0;
}