/**
 * @file ev_battery_management.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Battery Management System.
 *   It monitors battery temperature readings
 *   and generates battery health alerts.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 19-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> batteryTemperatures;

public:

    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of battery temperature readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter battery temperature (°C): ";
            cin >> value;

            batteryTemperatures.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief EV Battery Management System
 */
class BatteryManagementSystem : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== EV Battery Health Report =====\n";

        for(float temp : batteryTemperatures) {

            if(temp > 60) {

                cout << temp
                     << " °C -> Battery Overheating ⚠️\n";
            }
            else if(temp < 0) {

                cout << temp
                     << " °C -> Battery Too Cold ⚠️\n";
            }
            else {

                cout << temp
                     << " °C -> Battery Operating Normally ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    BatteryManagementSystem bms;

    sensor = &bms;

    bms.inputReadings();

    sensor->checkStatus();

    return 0;
}