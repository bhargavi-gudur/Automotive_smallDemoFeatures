/**
 * @file driver_drowsiness_detection.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Driver Drowsiness
 *   Detection System.
 *   It monitors eye-closure duration readings
 *   and generates driver alerts.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 16-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> eyeClosureReadings;

public:

    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter eye closure duration (seconds): ";
            cin >> value;

            eyeClosureReadings.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Driver Drowsiness Sensor
 */
class DrowsinessSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Driver Drowsiness Report =====\n";

        for(float value : eyeClosureReadings) {

            if(value > 3.0) {

                cout << value
                     << " sec -> Driver Drowsy ⚠️ Take a Break\n";
            }
            else {

                cout << value
                     << " sec -> Driver Alert ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    DrowsinessSensor drowsiness;

    sensor = &drowsiness;

    drowsiness.inputReadings();

    sensor->checkStatus();

    return 0;
}