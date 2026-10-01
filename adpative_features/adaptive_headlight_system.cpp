/**
 * @file adaptive_headlight_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Adaptive Headlight System.
 *   It monitors steering angle readings and
 *   adjusts headlights accordingly.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 21-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> steeringAngles;

public:

    void inputReadings() {

        int n, angle;

        cout << "Enter number of steering readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter steering angle: ";
            cin >> angle;

            steeringAngles.push_back(angle);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Adaptive Headlight System Class
 */
class AdaptiveHeadlight : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Adaptive Headlight Report =====\n";

        for(int angle : steeringAngles) {

            if(angle < -20) {

                cout << angle
                     << "° -> Turn Headlights Left ↖️\n";
            }
            else if(angle > 20) {

                cout << angle
                     << "° -> Turn Headlights Right ↗️\n";
            }
            else {

                cout << angle
                     << "° -> Headlights Straight ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    AdaptiveHeadlight headlight;

    sensor = &headlight;

    headlight.inputReadings();

    sensor->checkStatus();

    return 0;
}