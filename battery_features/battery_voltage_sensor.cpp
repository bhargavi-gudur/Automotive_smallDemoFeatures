/**
 * @file battery_voltage_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Battery Voltage
 *   Monitoring System.
 *   It checks battery voltage readings and
 *   generates alerts when voltage is too low
 *   or too high.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 08-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> voltageReadings;

public:

    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of voltage readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter voltage reading (V): ";
            cin >> value;

            voltageReadings.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Battery Voltage Sensor Class
 */
class BatteryVoltageSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Battery Voltage Report =====\n";

        for(float value : voltageReadings) {

            if(value < 11.5) {

                cout << value
                     << " V -> Low Battery Warning ⚠️\n";
            }
            else if(value > 14.8) {

                cout << value
                     << " V -> Over Voltage Warning ⚠️\n";
            }
            else {

                cout << value
                     << " V -> Battery Voltage Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    BatteryVoltageSensor battery;

    sensor = &battery;

    battery.inputReadings();

    sensor->checkStatus();

    return 0;
}