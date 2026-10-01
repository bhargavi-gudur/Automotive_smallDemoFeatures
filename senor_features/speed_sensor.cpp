/**
 * @file speed_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Vehicle Speed Sensor System.
 *   It stores speed readings using STL vector
 *   and checks vehicle speed conditions.
 *   Demonstrates OOP concepts in C++.
 * @date 31-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> speedReadings;

public:

    /**
     * @brief Input speed readings
     */
    void inputReadings() {

        int n, value;

        cout << "Enter number of speed readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter vehicle speed: ";
            cin >> value;

            speedReadings.push_back(value);
        }
    }
};

/**
 * @brief Speed Sensor Class
 */
class SpeedSensor : public Sensor {

public:

    /**
     * @brief Display speed readings
     */
    void showReadings() {

        cout << "\n===== Vehicle Speed Readings =====\n";

        for(int value : speedReadings) {

            cout << value << " km/h\n";
        }
    }

    /**
     * @brief Check speed status
     */
    void checkSpeed() {

        cout << "\n===== Speed Sensor Status =====\n";

        for(int value : speedReadings) {

            if(value > 120) {

                cout << value
                     << " km/h -> Overspeed Warning ⚠️\n";
            }
            else if(value < 20) {

                cout << value
                     << " km/h -> Low Speed\n";
            }
            else {

                cout << value
                     << " km/h -> Speed Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum speed
     */
    void findMaximumSpeed() {

        int maxSpeed = speedReadings[0];

        for(int value : speedReadings) {

            if(value > maxSpeed) {

                maxSpeed = value;
            }
        }

        cout << "\nMaximum Vehicle Speed: "
             << maxSpeed
             << " km/h\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    SpeedSensor s;

    cout << "===== Vehicle Speed Sensor System =====\n";

    s.inputReadings();

    s.showReadings();

    s.checkSpeed();

    s.findMaximumSpeed();

    return 0;
}