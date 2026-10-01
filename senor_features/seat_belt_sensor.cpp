/**
 * @file seat_belt_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Seat Belt Sensor System.
 *   It stores seat belt status using STL vector,
 *   checks whether passengers have worn seat belts,
 *   and generates safety warnings.
 *   Demonstrates OOP concepts in C++.
 * @date 05-06-2026
 */

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> seatBeltStatus;

public:

    /**
     * @brief Input seat belt status
     */
    void inputStatus() {

        int n, status;

        cout << "Enter number of passengers: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Passenger "
                 << i + 1
                 << " Seat Belt (1=Worn, 0=Not Worn): ";

            cin >> status;

            seatBeltStatus.push_back(status);
        }
    }
};

/**
 * @brief Seat Belt Sensor Class
 */
class SeatBeltSensor : public Sensor {

public:

    /**
     * @brief Display current date and time
     */
    void showDateTime() {

        time_t now = time(0);

        char* dt = ctime(&now);

        cout << "\nCurrent Date & Time: "
             << dt << endl;
    }

    /**
     * @brief Display seat belt status
     */
    void showStatus() {

        cout << "\n===== Seat Belt Status =====\n";

        int passenger = 1;

        for(int status : seatBeltStatus) {

            cout << "Passenger "
                 << passenger++
                 << " : ";

            if(status == 1)
                cout << "Seat Belt Worn ✅\n";
            else
                cout << "Seat Belt Not Worn ❌\n";
        }
    }

    /**
     * @brief Check safety warnings
     */
    void checkSafety() {

        cout << "\n===== Safety Check =====\n";

        int passenger = 1;

        for(int status : seatBeltStatus) {

            if(status == 0) {

                cout << "Warning: Passenger "
                     << passenger
                     << " has not worn seat belt ⚠️\n";
            }

            passenger++;
        }
    }

    /**
     * @brief Count passengers wearing seat belts
     */
    void countSeatBelts() {

        int count = 0;

        for(int status : seatBeltStatus) {

            if(status == 1) {

                count++;
            }
        }

        cout << "\nPassengers Wearing Seat Belts: "
             << count << endl;
    }
};

/**
 * @brief Main function
 */
int main() {

    SeatBeltSensor s;

    cout << "===== Seat Belt Sensor System =====\n";

    s.showDateTime();

    s.inputStatus();

    s.showStatus();

    s.checkSafety();

    s.countSeatBelts();

    return 0;
}