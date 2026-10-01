/**
 * @file battery_cell_balancing.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Battery Cell Balancing System.
 *   It monitors battery cell voltages and
 *   recommends balancing actions.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 04-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> cellVoltages;

public:

    /**
     * @brief Input battery cell voltages
     */
    void inputReadings() {

        int n;
        float voltage;

        cout << "Enter number of battery cells: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter Cell " << i + 1 << " Voltage (V): ";
            cin >> voltage;

            cellVoltages.push_back(voltage);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Battery Cell Balancing System
 */
class BatteryCellBalancing : public Sensor {

public:

    /**
     * @brief Check cell voltage status
     */
    void checkStatus() override {

        cout << "\n===== Battery Cell Balancing Report =====\n";

        int cell = 1;

        for(float voltage : cellVoltages) {

            cout << "Cell " << cell << " : ";

            if(voltage < 3.2) {

                cout << voltage
                     << " V -> Low Voltage ⚠️ Balance Required\n";
            }
            else if(voltage > 4.2) {

                cout << voltage
                     << " V -> High Voltage ⚠️ Stop Charging\n";
            }
            else {

                cout << voltage
                     << " V -> Cell Healthy ✅\n";
            }

            cell++;
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    BatteryCellBalancing battery;

    sensor = &battery;

    battery.inputReadings();

    sensor->checkStatus();

    return 0;
}