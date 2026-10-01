/**
 * @file ev_regenerative_braking.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Regenerative
 *   Braking System.
 *   It monitors braking force and
 *   calculates battery energy recovery.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 08-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> brakeForces;

public:

    /**
     * @brief Input brake force readings
     */
    void inputReadings() {

        int n, value;

        cout << "Enter number of brake readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter brake force (%): ";
            cin >> value;

            brakeForces.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief EV Regenerative Braking System
 */
class RegenerativeBraking : public Sensor {

public:

    /**
     * @brief Analyze braking force
     */
    void checkStatus() override {

        cout << "\n===== EV Regenerative Braking Report =====\n";

        for(int force : brakeForces) {

            if(force >= 70) {

                cout << force
                     << "% -> High Energy Recovery 🔋⚡\n";
            }
            else if(force >= 30) {

                cout << force
                     << "% -> Medium Energy Recovery 🔋\n";
            }
            else {

                cout << force
                     << "% -> Low Energy Recovery ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    RegenerativeBraking regen;

    sensor = &regen;

    regen.inputReadings();

    sensor->checkStatus();

    return 0;
}