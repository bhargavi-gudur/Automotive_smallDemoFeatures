/**
 * @file fuel_level_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Fuel Level Sensor System.
 *   It stores fuel readings using STL vector
 *   and checks fuel level conditions in a vehicle.
 *   Demonstrates OOP concepts in C++.
 * @date 01-06-2026
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> fuelReadings;

public:

    /**
     * @brief Input fuel readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of fuel readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter fuel level (%): ";
            cin >> value;

            fuelReadings.push_back(value);
        }
    }
};

/**
 * @brief Fuel Level Sensor Class
 */
class FuelLevelSensor : public Sensor {

public:

    /**
     * @brief Display fuel readings
     */
    void showReadings() {

        cout << "\n===== Fuel Level Readings =====\n";

        for(float value : fuelReadings) {

            cout << value << " %\n";
        }
    }

    /**
     * @brief Check fuel level status
     */
    void checkFuelLevel() {

        cout << "\n===== Fuel Status =====\n";

        for(float value : fuelReadings) {

            if(value < 15) {

                cout << value
                     << "% -> Low Fuel Warning ⚠️\n";
            }
            else if(value > 100) {

                cout << value
                     << "% -> Invalid Fuel Reading ❌\n";
            }
            else {

                cout << value
                     << "% -> Fuel Level Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum fuel level using STL
     */
    void findMaximumFuel() {

        float maxFuel =
            *max_element(fuelReadings.begin(),
                         fuelReadings.end());

        cout << "\nMaximum Fuel Level: "
             << maxFuel
             << " %\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    FuelLevelSensor f;

    cout << "===== Fuel Level Sensor System =====\n";

    f.inputReadings();

    f.showReadings();

    f.checkFuelLevel();

    f.findMaximumFuel();

    return 0;
}