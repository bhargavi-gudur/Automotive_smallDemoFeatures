/**
 * @file vehicle_stability_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Vehicle Stability Control (VSC) System.
 *   It monitors vehicle slip readings and generates
 *   stability control actions to prevent skidding.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 18-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> slipReadings;

public:

    /**
     * @brief Input slip readings
     */
    void inputReadings() {

        int n;
        float slipValue;

        cout << "Enter number of slip readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter wheel slip percentage: ";
            cin >> slipValue;

            slipReadings.push_back(slipValue);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Vehicle Stability Control Class
 */
class VehicleStabilityControl : public Sensor {

public:

    /**
     * @brief Check vehicle stability
     */
    void checkStatus() override {

        cout << "\n===== Vehicle Stability Control Report =====\n";

        for(float slip : slipReadings) {

            if(slip > 30) {

                cout << slip
                     << "% -> High Skid Risk! Stability Control Activated ⚠️\n";
            }
            else if(slip > 15) {

                cout << slip
                     << "% -> Moderate Slip Detected 🚗\n";
            }
            else {

                cout << slip
                     << "% -> Vehicle Stable ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    VehicleStabilityControl vsc;

    sensor = &vsc;

    vsc.inputReadings();

    sensor->checkStatus();

    return 0;
}