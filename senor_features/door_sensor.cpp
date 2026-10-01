/**
 * @file door_sensor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Door Sensor Monitoring System.
 *   It checks door status and generates warnings
 *   if any door is open.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 09-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> doorStatus;

public:

    /**
     * @brief Input door status
     */
    void inputReadings() {

        int n, status;

        cout << "Enter number of doors: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Door "
                 << i + 1
                 << " Status (1=Closed, 0=Open): ";

            cin >> status;

            doorStatus.push_back(status);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Door Sensor Class
 */
class DoorSensor : public Sensor {

public:

    /**
     * @brief Check door conditions
     */
    void checkStatus() override {

        cout << "\n===== Door Sensor Report =====\n";

        int doorNumber = 1;

        for(int status : doorStatus) {

            if(status == 1) {

                cout << "Door "
                     << doorNumber
                     << " -> Closed ✅\n";
            }
            else {

                cout << "Door "
                     << doorNumber
                     << " -> Open ⚠️ Close Door\n";
            }

            doorNumber++;
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    DoorSensor door;

    sensor = &door;

    door.inputReadings();

    sensor->checkStatus();

    return 0;
}