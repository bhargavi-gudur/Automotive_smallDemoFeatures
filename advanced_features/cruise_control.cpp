/**
 * @file cruise_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Cruise Control System.
 *   It monitors vehicle speed and compares it
 *   with the desired cruise speed.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 12-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> speedReadings;

public:

    void inputReadings() {

        int n, speed;

        cout << "Enter number of speed readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter vehicle speed (km/h): ";
            cin >> speed;

            speedReadings.push_back(speed);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Cruise Control Class
 */
class CruiseControl : public Sensor {

private:
    int cruiseSpeed;

public:

    void setCruiseSpeed() {

        cout << "Enter cruise speed (km/h): ";
        cin >> cruiseSpeed;
    }

    void checkStatus() override {

        cout << "\n===== Cruise Control Report =====\n";

        for(int speed : speedReadings) {

            if(speed > cruiseSpeed) {

                cout << speed
                     << " km/h -> Reduce Speed ⚠️\n";
            }
            else if(speed < cruiseSpeed) {

                cout << speed
                     << " km/h -> Increase Speed\n";
            }
            else {

                cout << speed
                     << " km/h -> Cruise Speed Maintained ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    CruiseControl cruise;

    sensor = &cruise;

    cruise.setCruiseSpeed();

    cruise.inputReadings();

    sensor->checkStatus();

    return 0;
}