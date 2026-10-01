/**
 * @file adaptive_cruise_speed_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Adaptive Cruise
 *   Speed Control System.
 *   It monitors vehicle speed and front vehicle
 *   distance to adjust cruise speed automatically.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 15-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> sensorData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings() {

        int n;
        int speed;
        int distance;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Speed (km/h): ";
            cin >> speed;
            sensorData.push_back(speed);

            cout << "Distance to Front Vehicle (m): ";
            cin >> distance;
            sensorData.push_back(distance);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Adaptive Cruise Speed Control
 */
class AdaptiveCruiseControl : public Sensor {

private:

    int setSpeed = 80;

public:

    /**
     * @brief Check cruise control conditions
     */
    void checkStatus() override {

        cout << "\n===== Adaptive Cruise Control Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < sensorData.size(); i += 2) {

            int speed = sensorData[i];
            int distance = sensorData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(distance < 20) {

                cout << "Reduce Speed! Vehicle Ahead ⚠️\n";
            }
            else if(speed < setSpeed) {

                cout << "Increase Speed to "
                     << setSpeed
                     << " km/h 🚗\n";
            }
            else {

                cout << "Cruise Speed Maintained ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    AdaptiveCruiseControl acc;

    sensor = &acc;

    acc.inputReadings();

    sensor->checkStatus();

    return 0;
}