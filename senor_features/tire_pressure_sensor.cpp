/**
 * @file tire_pressure_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Tire Pressure Monitoring System (TPMS).
 *   It stores tire pressure readings using STL vector
 *   and checks whether tire pressure is normal or low.
 *   Demonstrates OOP concepts in C++.
 * @date 29-05-2026
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
     * @brief Input tire pressure readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of tire pressure readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter tire pressure value: ";
            cin >> value;

            readings.push_back(value);
        }
    }
};

/**
 * @brief Tire Pressure Sensor Class
 */
class TirePressureSensor : public Sensor {

public:

    /**
     * @brief Check tire pressure status
     */
    void checkPressure() {

        cout << "\n===== Tire Pressure Status =====\n";

        for(float value : readings) {

            if(value < 30) {

                cout << value
                     << " PSI -> Low Tire Pressure ⚠️\n";
            }
            else if(value > 40) {

                cout << value
                     << " PSI -> High Tire Pressure ⚠️\n";
            }
            else {

                cout << value
                     << " PSI -> Tire Pressure Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum tire pressure
     */
    void findMaximumPressure() {

        float maxPressure = readings[0];

        for(float value : readings) {

            if(value > maxPressure) {

                maxPressure = value;
            }
        }

        cout << "\nMaximum Tire Pressure: "
             << maxPressure
             << " PSI\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    TirePressureSensor t;

    cout << "===== Tire Pressure Monitoring System =====\n";

    t.inputReadings();

    t.checkPressure();

    t.findMaximumPressure();

    return 0;
}