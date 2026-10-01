/**
 * @file automatic_emergency_call.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic Emergency
 *   Call (eCall) System.
 *   It monitors crash severity and GPS availability
 *   to determine whether an emergency call
 *   should be placed.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 16-07-2026
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> emergencyData;

public:

    /**
     * @brief Input crash readings
     */
    void inputReadings() {

        int n;
        int crashDetected;
        int gpsAvailable;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Crash Detected (1=Yes, 0=No): ";
            cin >> crashDetected;
            emergencyData.push_back(crashDetected);

            cout << "GPS Available (1=Yes, 0=No): ";
            cin >> gpsAvailable;
            emergencyData.push_back(gpsAvailable);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Automatic Emergency Call System
 */
class EmergencyCallSystem : public Sensor {

public:

    /**
     * @brief Check emergency conditions
     */
    void checkStatus() override {

        cout << "\n===== Automatic Emergency Call Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < emergencyData.size(); i += 2) {

            int crash = emergencyData[i];
            int gps = emergencyData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(crash == 1 && gps == 1) {

                cout << "Emergency Call Sent with GPS Location 🚑\n";
            }
            else if(crash == 1 && gps == 0) {

                cout << "Emergency Call Sent without GPS ⚠️\n";
            }
            else {

                cout << "No Emergency Detected ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    EmergencyCallSystem eCall;

    sensor = &eCall;

    eCall.inputReadings();

    sensor->checkStatus();

    return 0;
}