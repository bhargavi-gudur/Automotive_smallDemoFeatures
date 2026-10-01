/**
 * @file pressure_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Pressure Sensor System.
 *   It stores pressure readings using STL vector,
 *   checks pressure conditions,
 *   and displays current system date and time.
 *   Demonstrates OOP concepts in C++.
 * @date 02-06-2026
 */

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> pressureReadings;

public:

    /**
     * @brief Input pressure readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of pressure readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter pressure value: ";
            cin >> value;

            pressureReadings.push_back(value);
        }
    }
};

/**
 * @brief Pressure Sensor Class
 */
class PressureSensor : public Sensor {

public:

    /**
     * @brief Show current date and time
     */
    void showDateTime() {

        time_t now = time(0);

        char* dt = ctime(&now);

        cout << "\nCurrent Date & Time: "
             << dt << endl;
    }

    /**
     * @brief Display pressure readings
     */
    void showReadings() {

        cout << "\n===== Pressure Readings =====\n";

        for(float value : pressureReadings) {

            cout << value << " Pa\n";
        }
    }

    /**
     * @brief Check pressure conditions
     */
    void checkPressure() {

        cout << "\n===== Pressure Status =====\n";

        for(float value : pressureReadings) {

            if(value < 20) {

                cout << value
                     << " Pa -> Low Pressure Warning ⚠️\n";
            }
            else if(value > 100) {

                cout << value
                     << " Pa -> High Pressure Warning ⚠️\n";
            }
            else {

                cout << value
                     << " Pa -> Pressure Normal ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum pressure
     */
    void findMaximumPressure() {

        float maxPressure = pressureReadings[0];

        for(float value : pressureReadings) {

            if(value > maxPressure) {

                maxPressure = value;
            }
        }

        cout << "\nMaximum Pressure: "
             << maxPressure
             << " Pa\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    PressureSensor p;

    cout << "===== Pressure Sensor Monitoring System =====\n";

    p.showDateTime();

    p.inputReadings();

    p.showReadings();

    p.checkPressure();

    p.findMaximumPressure();

    return 0;
}