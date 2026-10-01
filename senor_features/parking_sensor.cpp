/**
 * @file parking_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Parking Sensor System.
 *   It stores obstacle distance readings using STL vector,
 *   checks parking safety conditions,
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
    vector<float> distanceReadings;

public:

    /**
     * @brief Input obstacle distance readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of distance readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter obstacle distance (cm): ";
            cin >> value;

            distanceReadings.push_back(value);
        }
    }
};

/**
 * @brief Parking Sensor Class
 */
class ParkingSensor : public Sensor {

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
     * @brief Display distance readings
     */
    void showReadings() {

        cout << "\n===== Parking Sensor Readings =====\n";

        for(float value : distanceReadings) {

            cout << value << " cm\n";
        }
    }

    /**
     * @brief Check parking conditions
     */
    void checkParkingStatus() {

        cout << "\n===== Parking Sensor Status =====\n";

        for(float value : distanceReadings) {

            if(value < 20) {

                cout << value
                     << " cm -> STOP! Obstacle Very Close ⚠️\n";
            }
            else if(value < 50) {

                cout << value
                     << " cm -> Slow Down 🚗\n";
            }
            else {

                cout << value
                     << " cm -> Safe Distance ✅\n";
            }
        }
    }

    /**
     * @brief Find minimum obstacle distance
     */
    void findMinimumDistance() {

        float minDistance = distanceReadings[0];

        for(float value : distanceReadings) {

            if(value < minDistance) {

                minDistance = value;
            }
        }

        cout << "\nMinimum Obstacle Distance: "
             << minDistance
             << " cm\n";
    }
};

/**
 * @brief Main function
 */
int main() {

    ParkingSensor p;

    cout << "===== Parking Sensor Monitoring System =====\n";

    p.showDateTime();

    p.inputReadings();

    p.showReadings();

    p.checkParkingStatus();

    p.findMinimumDistance();

    return 0;
}