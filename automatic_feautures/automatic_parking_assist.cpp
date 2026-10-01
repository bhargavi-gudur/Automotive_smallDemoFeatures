/**
 * @file automatic_parking_assist.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic Parking Assist System.
 *   It monitors parking sensor distances and
 *   provides parking guidance.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 24-06-2026
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

        cout << "Enter number of parking sensor readings: ";
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
 * @brief Automatic Parking Assist System
 */
class ParkingAssistSystem : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Parking Assist Report =====\n";

        for(float distance : distanceReadings) {

            if(distance < 0.5) {

                cout << distance
                     << " m -> STOP! Obstacle Very Close ⚠️\n";
            }
            else if(distance < 2.0) {

                cout << distance
                     << " m -> Continue Parking Slowly 🚗\n";
            }
            else {

                cout << distance
                     << " m -> Parking Space Available ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    ParkingAssistSystem parking;

    sensor = &parking;

    parking.inputReadings();

    sensor->checkStatus();

    return 0;
}