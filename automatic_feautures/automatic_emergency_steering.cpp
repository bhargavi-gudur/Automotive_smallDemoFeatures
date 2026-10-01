/**
 * @file automatic_emergency_steering.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic Emergency
 *   Steering System (AESS).
 *   It monitors obstacle distance readings and
 *   recommends steering actions.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 26-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> obstacleDistances;

public:

    /**
     * @brief Input obstacle distance readings
     */
    void inputReadings() {

        int n;
        float distance;

        cout << "Enter number of obstacle readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter obstacle distance (meters): ";
            cin >> distance;

            obstacleDistances.push_back(distance);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Automatic Emergency Steering System
 */
class EmergencySteeringSystem : public Sensor {

public:

    /**
     * @brief Check steering requirement
     */
    void checkStatus() override {

        cout << "\n===== Emergency Steering Report =====\n";

        for(float distance : obstacleDistances) {

            if(distance < 2.0) {

                cout << distance
                     << " m -> Emergency Steering Activated ⚠️\n";
            }
            else if(distance < 5.0) {

                cout << distance
                     << " m -> Prepare to Steer 🚗\n";
            }
            else {

                cout << distance
                     << " m -> Path Clear ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    EmergencySteeringSystem aess;

    sensor = &aess;

    aess.inputReadings();

    sensor->checkStatus();

    return 0;
}