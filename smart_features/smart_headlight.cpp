/**
 * @file smart_headlight.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Headlight Control System
 *   using STL map in C++.
 *   It controls headlights based on
 *   night mode, rain, and opposite vehicle detection.
 * @date 25-05-2026
 */

#include <iostream>
#include <map>
using namespace std;

/**
 * @brief Class for Smart Headlight System
 */
class SmartHeadlight {

private:

    // Map to store sensor conditions
    map<string, bool> sensorData;

public:

    /**
     * @brief Input sensor conditions
     */
    void inputData() {

        int value;

        cout << "Is it Night Time? (1 = Yes, 0 = No): ";
        cin >> value;
        sensorData["Night"] = value;

        cout << "Is Rain Detected? (1 = Yes, 0 = No): ";
        cin >> value;
        sensorData["Rain"] = value;

        cout << "Is Opposite Vehicle Detected? (1 = Yes, 0 = No): ";
        cin >> value;
        sensorData["Vehicle"] = value;
    }

    /**
     * @brief Control headlight system
     */
    void controlHeadlight() {

        cout << "\n===== Headlight Status =====\n";

        // Night condition
        if(sensorData["Night"]) {

            cout << "Headlight ON 🌙\n";

            // Vehicle detection
            if(sensorData["Vehicle"]) {

                cout << "Opposite Vehicle Detected\n";
                cout << "Switching to LOW Beam 🚗\n";
            }
            else {

                cout << "HIGH Beam Activated 🔆\n";
            }
        }
        else {

            cout << "Day Time → Headlight OFF ☀️\n";
        }

        // Rain condition
        if(sensorData["Rain"]) {

            cout << "Rain Detected 🌧️\n";
            cout << "Fog Lights ON\n";
        }
    }

    /**
     * @brief Display sensor data
     */
    void showSensorData() {

        cout << "\nSensor Data:\n";

        for(auto data : sensorData) {

            cout << data.first
                 << " : "
                 << data.second
                 << endl;
        }
    }
};

/**
 * @brief Main function
 */
int main() {

    SmartHeadlight s;

    cout << "===== Smart Headlight Control System =====\n";

    s.inputData();

    s.showSensorData();

    s.controlHeadlight();

    return 0;
}