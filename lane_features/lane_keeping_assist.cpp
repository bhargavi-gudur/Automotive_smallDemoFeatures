/**
 * @file lane_keeping_assist.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Lane Keeping Assist System (LKAS).
 *   It monitors lane offset readings and
 *   provides steering assistance.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 27-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> laneOffsets;

public:

    /**
     * @brief Input lane offset readings
     */
    void inputReadings() {

        int n;
        float offset;

        cout << "Enter number of lane offset readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter lane offset (meters): ";
            cin >> offset;

            laneOffsets.push_back(offset);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Lane Keeping Assist System
 */
class LaneKeepingAssist : public Sensor {

public:

    /**
     * @brief Check lane position
     */
    void checkStatus() override {

        cout << "\n===== Lane Keeping Assist Report =====\n";

        for(float offset : laneOffsets) {

            if(offset < -0.5) {

                cout << offset
                     << " m -> Steering Right Required ⚠️\n";
            }
            else if(offset > 0.5) {

                cout << offset
                     << " m -> Steering Left Required ⚠️\n";
            }
            else {

                cout << offset
                     << " m -> Vehicle Centered in Lane ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    LaneKeepingAssist lkas;

    sensor = &lkas;

    lkas.inputReadings();

    sensor->checkStatus();

    return 0;
}