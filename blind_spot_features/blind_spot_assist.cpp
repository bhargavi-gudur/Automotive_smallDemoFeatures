/**
 * @file blind_spot_assist.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Blind Spot Assist System.
 *   It monitors radar sensor distance readings
 *   and alerts the driver when a vehicle
 *   is detected in the blind spot.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 9-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> radarDistances;

public:

    /**
     * @brief Input radar distance readings
     */
    void inputReadings() {

        int n;
        float distance;

        cout << "Enter number of radar readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter vehicle distance (meters): ";
            cin >> distance;

            radarDistances.push_back(distance);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Blind Spot Assist System
 */
class BlindSpotAssist : public Sensor {

public:

    /**
     * @brief Analyze blind spot
     */
    void checkStatus() override {

        cout << "\n===== Blind Spot Assist Report =====\n";

        for(float distance : radarDistances) {

            if(distance <= 3.0) {

                cout << distance
                     << " m -> Vehicle in Blind Spot ⚠️ Do Not Change Lane\n";
            }
            else if(distance <= 6.0) {

                cout << distance
                     << " m -> Vehicle Approaching 🚗 Be Careful\n";
            }
            else {

                cout << distance
                     << " m -> Blind Spot Clear ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    BlindSpotAssist blindSpot;

    sensor = &blindSpot;

    blindSpot.inputReadings();

    sensor->checkStatus();

    return 0;
}