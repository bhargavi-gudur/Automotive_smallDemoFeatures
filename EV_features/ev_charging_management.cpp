/**
 * @file ev_charging_management.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Charging
 *   Management System.
 *   It monitors battery charge levels and
 *   controls the charging process.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 02-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> batteryLevels;

public:

    /**
     * @brief Input battery charge levels
     */
    void inputReadings() {

        int n, level;

        cout << "Enter number of battery readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter battery charge (%): ";
            cin >> level;

            batteryLevels.push_back(level);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief EV Charging Management System
 */
class EVChargingSystem : public Sensor {

public:

    /**
     * @brief Check charging status
     */
    void checkStatus() override {

        cout << "\n===== EV Charging Report =====\n";

        for(int level : batteryLevels) {

            if(level < 20) {

                cout << level
                     << "% -> Fast Charging Required ⚡\n";
            }
            else if(level < 80) {

                cout << level
                     << "% -> Charging in Progress 🔋\n";
            }
            else if(level <= 100) {

                cout << level
                     << "% -> Battery Fully Charged ✅\n";
            }
            else {

                cout << level
                     << "% -> Invalid Battery Reading ❌\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    EVChargingSystem ev;

    sensor = &ev;

    ev.inputReadings();

    sensor->checkStatus();

    return 0;
}