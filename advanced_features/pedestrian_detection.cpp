/**
 * @file pedestrian_detection.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Pedestrian Detection System.
 *   It monitors pedestrian distance readings and
 *   generates driver warnings.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 25-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> pedestrianDistances;

public:

    /**
     * @brief Input pedestrian distance readings
     */
    void inputReadings() {

        int n;
        float distance;

        cout << "Enter number of pedestrian distance readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter pedestrian distance (meters): ";
            cin >> distance;

            pedestrianDistances.push_back(distance);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Pedestrian Detection System
 */
class PedestrianDetection : public Sensor {

public:

    /**
     * @brief Check pedestrian distance
     */
    void checkStatus() override {

        cout << "\n===== Pedestrian Detection Report =====\n";

        for(float distance : pedestrianDistances) {

            if(distance < 2.0) {

                cout << distance
                     << " m -> Emergency Brake Required ⚠️\n";
            }
            else if(distance < 5.0) {

                cout << distance
                     << " m -> Slow Down! Pedestrian Ahead 🚶\n";
            }
            else {

                cout << distance
                     << " m -> Road Clear ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    PedestrianDetection pedestrian;

    sensor = &pedestrian;

    pedestrian.inputReadings();

    sensor->checkStatus();

    return 0;
}