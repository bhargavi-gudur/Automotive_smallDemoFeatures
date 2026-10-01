/**
 * @file smart_power_window_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Power Window
 *   Control System.
 *   It monitors window switch status and
 *   obstacle detection to control the power window.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 18-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> windowData;

public:

    /**
     * @brief Input window control readings
     */
    void inputReadings() {

        int n;
        int windowSwitch;
        int obstacleDetected;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Window Switch (1=Close, 0=Open): ";
            cin >> windowSwitch;
            windowData.push_back(windowSwitch);

            cout << "Obstacle Detected (1=Yes, 0=No): ";
            cin >> obstacleDetected;
            windowData.push_back(obstacleDetected);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Smart Power Window Control System
 */
class SmartPowerWindow : public Sensor {

public:

    /**
     * @brief Analyze window operation
     */
    void checkStatus() override {

        cout << "\n===== Smart Power Window Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < windowData.size(); i += 2) {

            int windowSwitch = windowData[i];
            int obstacle = windowData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(windowSwitch == 1 && obstacle == 1) {

                cout << "Obstacle Detected! Window Reversed ⚠️\n";
            }
            else if(windowSwitch == 1 && obstacle == 0) {

                cout << "Window Closing ✅\n";
            }
            else {

                cout << "Window Opening\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    SmartPowerWindow window;

    sensor = &window;

    window.inputReadings();

    sensor->checkStatus();

    return 0;
}