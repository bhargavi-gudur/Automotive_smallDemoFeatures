/**
 * @file collision_avoidance_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Collision Avoidance System.
 *   It monitors obstacle distance readings and
 *   generates collision warnings.
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
 * @brief Collision Avoidance Sensor
 */
class CollisionAvoidanceSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Collision Avoidance Report =====\n";

        for(float distance : distanceReadings) {

            if(distance < 5) {

                cout << distance
                     << " m -> Collision Risk! Brake Immediately ⚠️\n";
            }
            else if(distance < 15) {

                cout << distance
                     << " m -> Reduce Speed 🚗\n";
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

    CollisionAvoidanceSensor collision;

    sensor = &collision;

    collision.inputReadings();

    sensor->checkStatus();

    return 0;
}