/**
 * @file gyroscope_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Gyroscope Sensor System.
 *   It detects vehicle/device rotation using STL vector
 *   and demonstrates OOP concepts in C++.
 * @date 28-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> readings;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of rotation readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter rotation value: ";
            cin >> value;

            readings.push_back(value);
        }
    }
};

/**
 * @brief Gyroscope Sensor Class
 */
class GyroscopeSensor : public Sensor {

public:

    /**
     * @brief Check rotation status
     */
    void checkRotation() {

        cout << "\n===== Gyroscope Sensor Status =====\n";

        for(float value : readings) {

            if(value > 180) {

                cout << value
                     << "° -> High Rotation Detected ⚠️\n";
            }
            else {

                cout << value
                     << "° -> Rotation Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum rotation
     */
    void findMaximumRotation() {

        float maxRotation = readings[0];

        for(float value : readings) {

            if(value > maxRotation) {

                maxRotation = value;
            }
        }

        cout << "\nMaximum Rotation: "
             << maxRotation
             << "°\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    GyroscopeSensor g;

    cout << "===== Gyroscope Sensor Monitoring System =====\n";

    g.inputReadings();

    g.checkRotation();

    g.findMaximumRotation();

    return 0;
}