/**
 * @file hill_start_assist.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Hill Start Assist System.
 *   It monitors road slope and brake pedal status
 *   to determine whether Hill Start Assist
 *   should be activated.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 13-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> hillData;

public:

    /**
     * @brief Input hill start readings
     */
    void inputReadings() {

        int n;
        int slopeAngle;
        int brakePressed;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Road Slope (degrees): ";
            cin >> slopeAngle;

            hillData.push_back(slopeAngle);

            cout << "Brake Pressed (1=Yes, 0=No): ";
            cin >> brakePressed;

            hillData.push_back(brakePressed);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Hill Start Assist System
 */
class HillStartAssist : public Sensor {

public:

    /**
     * @brief Check hill assist conditions
     */
    void checkStatus() override {

        cout << "\n===== Hill Start Assist Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < hillData.size(); i += 2) {

            int slope = hillData[i];
            int brake = hillData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(slope >= 10 && brake == 1) {

                cout << "Hill Start Assist Activated ✅\n";
            }
            else if(slope >= 10 && brake == 0) {

                cout << "Warning: Vehicle May Roll Back ⚠️\n";
            }
            else {

                cout << "Normal Driving - Hill Assist Not Required\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    HillStartAssist hill;

    sensor = &hill;

    hill.inputReadings();

    sensor->checkStatus();

    return 0;
}