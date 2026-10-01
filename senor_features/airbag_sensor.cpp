/**
 * @file airbag_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Airbag Sensor System.
 *   It stores collision impact readings using STL vector,
 *   checks accident severity,
 *   and decides airbag deployment conditions.
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
    vector<float> impactReadings;

public:

    /**
     * @brief Input collision impact readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of impact readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter collision impact value: ";
            cin >> value;

            impactReadings.push_back(value);
        }
    }
};

/**
 * @brief Airbag Sensor Class
 */
class AirbagSensor : public Sensor {

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
     * @brief Display impact readings
     */
    void showReadings() {

        cout << "\n===== Airbag Sensor Readings =====\n";

        for(float value : impactReadings) {

            cout << value << endl;
        }
    }

    /**
     * @brief Check airbag deployment status
     */
    void checkAirbagStatus() {

        cout << "\n===== Airbag Deployment Status =====\n";

        for(float value : impactReadings) {

            if(value > 80) {

                cout << value
                     << " -> Severe Collision ⚠️ Airbag Deployed\n";
            }
            else if(value > 50) {

                cout << value
                     << " -> Moderate Collision ⚠️ Prepare Airbag\n";
            }
            else {

                cout << value
                     << " -> No Airbag Deployment Needed ✅\n";
            }
        }
    }

    /**
     * @brief Find maximum collision impact
     */
    void findMaximumImpact() {

        float maxImpact = impactReadings[0];

        for(float value : impactReadings) {

            if(value > maxImpact) {

                maxImpact = value;
            }
        }

        cout << "\nMaximum Collision Impact: "
             << maxImpact
             << endl;
    }
};

/**
 * @brief Main function
 */
int main() {

    AirbagSensor a;

    cout << "===== Airbag Sensor Monitoring System =====\n";

    a.showDateTime();

    a.inputReadings();

    a.showReadings();

    a.checkAirbagStatus();

    a.findMaximumImpact();

    return 0;
}