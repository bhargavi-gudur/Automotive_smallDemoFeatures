/**
 * @file driver_assistance_dashboard.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Driver Assistance Dashboard.
 *   It displays vehicle warnings based on
 *   speed, fuel level, and engine temperature.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 29-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> readings;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings() {

        int n, value;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter reading: ";
            cin >> value;

            readings.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Driver Assistance Dashboard
 */
class Dashboard : public Sensor {

private:

    int speedLimit = 100;

public:

    /**
     * @brief Display dashboard warnings
     */
    void checkStatus() override {

        cout << "\n===== Driver Assistance Dashboard =====\n";

        int readingNumber = 1;

        for(int value : readings) {

            cout << "\nReading " << readingNumber++ << ":\n";

            if(value > speedLimit) {

                cout << "Speed Warning: Overspeed ⚠️\n";
            }
            else {

                cout << "Speed Status: Normal ✅\n";
            }

            if(value < 15) {

                cout << "Fuel Warning: Low Fuel ⛽\n";
            }

            if(value > 110) {

                cout << "Engine Temperature Warning: High 🌡️\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    Dashboard dashboard;

    sensor = &dashboard;

    dashboard.inputReadings();

    sensor->checkStatus();

    return 0;
}