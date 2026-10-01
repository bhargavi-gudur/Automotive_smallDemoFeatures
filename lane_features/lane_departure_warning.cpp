/**
 * @file lane_departure_warning.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Lane Departure Warning System.
 *   It checks vehicle lane position and generates warnings.
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
    vector<float> lanePositions;

public:

    void inputReadings() {

        int n;
        float position;

        cout << "Enter number of lane readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter lane position: ";
            cin >> position;

            lanePositions.push_back(position);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Lane Departure Warning Class
 */
class LaneDepartureSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Lane Departure Report =====\n";

        for(float position : lanePositions) {

            if(position < -0.5) {

                cout << position
                     << " -> Vehicle Drifting Left ⚠️\n";
            }
            else if(position > 0.5) {

                cout << position
                     << " -> Vehicle Drifting Right ⚠️\n";
            }
            else {

                cout << position
                     << " -> Lane Position Safe ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    LaneDepartureSensor lane;

    sensor = &lane;

    lane.inputReadings();

    sensor->checkStatus();

    return 0;
}