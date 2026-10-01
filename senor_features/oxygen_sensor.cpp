/**
 * @file oxygen_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Oxygen Sensor System
 *   used in vehicles.
 *   It stores oxygen sensor readings using STL vector
 *   and checks whether oxygen level is normal or low.
 *   Demonstrates OOP and STL concepts in C++.
 * @date 26-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Class for Oxygen Sensor System
 */
class OxygenSensor {

private:

    vector<float> oxygenLevels;

public:

    /**
     * @brief Store oxygen sensor readings
     */
    void inputLevels() {

        int n;
        float value;

        cout << "Enter number of oxygen readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter oxygen level: ";
            cin >> value;

            oxygenLevels.push_back(value);
        }
    }

    /**
     * @brief Display oxygen readings
     */
    void showLevels() {

        cout << "\nOxygen Sensor Readings:\n";

        for(float value : oxygenLevels) {

            cout << value << endl;
        }
    }

    /**
     * @brief Check oxygen status
     */
    void checkLevels() {

        cout << "\n===== Oxygen Status =====\n";

        for(float value : oxygenLevels) {

            if(value < 18.0) {

                cout << value
                     << " -> Low Oxygen Level ⚠️\n";
            }
            else {

                cout << value
                     << " -> Normal Oxygen Level ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum oxygen level
     */
    void findMaximum() {

        float maxLevel = oxygenLevels[0];

        for(float value : oxygenLevels) {

            if(value > maxLevel) {

                maxLevel = value;
            }
        }

        cout << "\nMaximum Oxygen Level: "
             << maxLevel
             << endl;
    }
};

/**
 * @brief Main function
 */
int main() {

    OxygenSensor o;

    cout << "===== Oxygen Sensor Monitoring System =====\n";

    o.inputLevels();

    o.showLevels();

    o.checkLevels();

    o.findMaximum();

    return 0;
}