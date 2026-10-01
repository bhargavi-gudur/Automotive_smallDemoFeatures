/**
 * @file light_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Light Sensor System.
 *   It monitors light intensity and controls
 *   vehicle headlights automatically.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 07-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> lightLevels;

public:

    void inputReadings() {

        int n, value;

        cout << "Enter number of light readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter light intensity (0-100): ";
            cin >> value;

            lightLevels.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Light Sensor Class
 */
class LightSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Smart Headlight Report =====\n";

        for(int level : lightLevels) {

            if(level < 30) {

                cout << level
                     << " -> Dark Environment, Headlight ON 💡\n";
            }
            else {

                cout << level
                     << " -> Sufficient Light, Headlight OFF ☀️\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    LightSensor light;

    sensor = &light;

    light.inputReadings();

    sensor->checkStatus();

    return 0;
}