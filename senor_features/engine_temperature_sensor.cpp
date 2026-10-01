/**
 * @file engine_temperature_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a real-time Engine Temperature
 *   Monitoring System using STL vector in C++.
 *   It checks engine temperature readings
 *   and warns about overheating conditions.
 * @date 30-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> temperatureReadings;

public:

    /**
     * @brief Input temperature readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of temperature readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter engine temperature: ";
            cin >> value;

            temperatureReadings.push_back(value);
        }
    }
};

/**
 * @brief Engine Temperature Sensor Class
 */
class TemperatureSensor : public Sensor {

public:

    /**
     * @brief Display temperature readings
     */
    void showReadings() {

        cout << "\n===== Engine Temperature Readings =====\n";

        for(float value : temperatureReadings) {

            cout << value << " °C\n";
        }
    }

    /**
     * @brief Check engine temperature status
     */
    void checkTemperature() {

        cout << "\n===== Engine Temperature Status =====\n";

        for(float value : temperatureReadings) {

            if(value > 100) {

                cout << value
                     << " °C -> Engine Overheating ⚠️\n";
            }
            else if(value < 40) {

                cout << value
                     << " °C -> Engine Cold\n";
            }
            else {

                cout << value
                     << " °C -> Temperature Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum temperature
     */
    void findMaximumTemperature() {

        float maxTemp = temperatureReadings[0];

        for(float value : temperatureReadings) {

            if(value > maxTemp) {

                maxTemp = value;
            }
        }

        cout << "\nMaximum Engine Temperature: "
             << maxTemp
             << " °C\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    TemperatureSensor t;

    cout << "===== Engine Temperature Monitoring System =====\n";

    t.inputReadings();

    t.showReadings();

    t.checkTemperature();

    t.findMaximumTemperature();

    return 0;
}