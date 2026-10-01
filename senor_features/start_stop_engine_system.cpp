/**
 * @file start_stop_engine_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Start-Stop Engine System.
 *   It monitors vehicle speed and brake pedal status
 *   to automatically stop or start the engine.
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
    vector<int> engineData;

public:

    /**
     * @brief Input vehicle readings
     */
    void inputReadings() {

        int n;
        int speed, brake;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Speed (km/h): ";
            cin >> speed;
            engineData.push_back(speed);

            cout << "Brake Pressed (1=Yes, 0=No): ";
            cin >> brake;
            engineData.push_back(brake);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Start-Stop Engine System
 */
class StartStopEngine : public Sensor {

public:

    /**
     * @brief Check engine status
     */
    void checkStatus() override {

        cout << "\n===== Start-Stop Engine Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < engineData.size(); i += 2) {

            int speed = engineData[i];
            int brake = engineData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(speed == 0 && brake == 1) {

                cout << "Engine Stopped to Save Fuel ✅\n";
            }
            else if(speed == 0 && brake == 0) {

                cout << "Engine Restarted 🚗\n";
            }
            else {

                cout << "Vehicle Moving - Engine Running\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    StartStopEngine startStop;

    sensor = &startStop;

    startStop.inputReadings();

    sensor->checkStatus();

    return 0;
}