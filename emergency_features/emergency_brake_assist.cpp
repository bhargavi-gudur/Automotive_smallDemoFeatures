/**
 * @file emergency_brake_assist.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Emergency Brake Assist System.
 *   It monitors obstacle distance readings and
 *   decides whether emergency braking is required.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 17-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> distanceReadings;

public:

    void inputReadings() {

        int n;
        float distance;

        cout << "Enter number of distance readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter obstacle distance (meters): ";
            cin >> distance;

            distanceReadings.push_back(distance);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Emergency Brake Assist Class
 */
class EmergencyBrakeAssist : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Emergency Brake Assist Report =====\n";

        for(float distance : distanceReadings) {

            if(distance < 3) {

                cout << distance
                     << " m -> Emergency Brake Applied ⚠️\n";
            }
            else if(distance < 10) {

                cout << distance
                     << " m -> Brake Warning 🚗\n";
            }
            else {

                cout << distance
                     << " m -> Safe Distance ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    EmergencyBrakeAssist eba;

    sensor = &eba;

    eba.inputReadings();

    sensor->checkStatus();

    return 0;
}