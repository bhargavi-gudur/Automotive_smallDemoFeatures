/**
 * @file advanced_tpms.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Advanced Tire Pressure
 *   Monitoring System (TPMS).
 *   It monitors tire pressure readings and
 *   generates safety warnings.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 24-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> pressureReadings;

public:

    void inputReadings() {

        int n;
        float pressure;

        cout << "Enter number of tire pressure readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter tire pressure (PSI): ";
            cin >> pressure;

            pressureReadings.push_back(pressure);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Advanced TPMS Class
 */
class TPMS : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Tire Pressure Report =====\n";

        for(float pressure : pressureReadings) {

            if(pressure < 30) {

                cout << pressure
                     << " PSI -> Low Tire Pressure ⚠️\n";
            }
            else if(pressure > 40) {

                cout << pressure
                     << " PSI -> High Tire Pressure ⚠️\n";
            }
            else {

                cout << pressure
                     << " PSI -> Tire Pressure Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    TPMS tpms;

    sensor = &tpms;

    tpms.inputReadings();

    sensor->checkStatus();

    return 0;
}