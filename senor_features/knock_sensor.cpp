/**
 * @file knock_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Knock Sensor System.
 *   It stores engine vibration readings using STL vector,
 *   checks engine knocking conditions,
 *   and displays current system date and time.
 *   Demonstrates OOP concepts in C++.
 * @date 03-06-2026
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
    vector<float> knockReadings;

public:

    /**
     * @brief Input knock sensor readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of knock readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter engine vibration value: ";
            cin >> value;

            knockReadings.push_back(value);
        }
    }
};

/**
 * @brief Knock Sensor Class
 */
class KnockSensor : public Sensor {

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
     * @brief Display knock readings
     */
    void showReadings() {

        cout << "\n===== Knock Sensor Readings =====\n";

        for(float value : knockReadings) {

            cout << value << endl;
        }
    }

    /**
     * @brief Check engine knocking conditions
     */
    void checkKnocking() {

        cout << "\n===== Engine Knock Status =====\n";

        for(float value : knockReadings) {

            if(value > 80) {

                cout << value
                     << " -> Severe Engine Knock ⚠️\n";
            }
            else if(value > 50) {

                cout << value
                     << " -> Moderate Engine Knock ⚠️\n";
            }
            else {

                cout << value
                     << " -> Engine Running Smoothly ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum knock value
     */
    void findMaximumKnock() {

        float maxKnock = knockReadings[0];

        for(float value : knockReadings) {

            if(value > maxKnock) {

                maxKnock = value;
            }
        }

        cout << "\nMaximum Knock Value: "
             << maxKnock
             << endl;
    }
};

/**
 * @brief Main function
 */
int main() {

    KnockSensor k;

    cout << "===== Knock Sensor Monitoring System =====\n";

    k.showDateTime();

    k.inputReadings();

    k.showReadings();

    k.checkKnocking();

    k.findMaximumKnock();

    return 0;
}