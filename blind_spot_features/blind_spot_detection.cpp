/**
 * @file blind_spot_detection.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Blind Spot Detection System.
 *   It monitors nearby vehicle distances and
 *   generates blind spot warnings.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 14-06-2026
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

        cout << "Enter number of sensor readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter vehicle distance (meters): ";
            cin >> distance;

            distanceReadings.push_back(distance);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Blind Spot Detection Class
 */
class BlindSpotSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Blind Spot Detection Report =====\n";

        for(float distance : distanceReadings) {

            if(distance <= 5) {

                cout << distance
                     << " m -> Vehicle in Blind Spot ⚠️\n";
            }
            else {

                cout << distance
                     << " m -> Safe to Change Lane ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    BlindSpotSensor blindSpot;

    sensor = &blindSpot;

    blindSpot.inputReadings();

    sensor->checkStatus();

    return 0;
}