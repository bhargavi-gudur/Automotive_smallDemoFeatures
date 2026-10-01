/**
 * @file rain_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Rain Sensor System.
 *   It monitors rain intensity and controls
 *   windshield wiper operation.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 06-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> rainLevels;

public:

    void inputReadings() {

        int n, value;

        cout << "Enter number of rain readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter rain intensity (0-100): ";
            cin >> value;

            rainLevels.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Rain Sensor Class
 */
class RainSensor : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Rain Sensor Report =====\n";

        for(int level : rainLevels) {

            if(level == 0) {

                cout << level
                     << " -> No Rain, Wiper OFF\n";
            }
            else if(level <= 40) {

                cout << level
                     << " -> Light Rain, Wiper LOW Speed\n";
            }
            else if(level <= 70) {

                cout << level
                     << " -> Moderate Rain, Wiper MEDIUM Speed\n";
            }
            else {

                cout << level
                     << " -> Heavy Rain, Wiper HIGH Speed\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    RainSensor rain;

    sensor = &rain;

    rain.inputReadings();

    sensor->checkStatus();

    return 0;
}