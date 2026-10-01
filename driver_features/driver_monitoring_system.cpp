/**
 * @file driver_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Driver Monitoring System.
 *   It monitors driver attention levels and
 *   generates safety alerts.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 22-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> attentionLevels;

public:

    void inputReadings() {

        int n, value;

        cout << "Enter number of attention readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter attention level (0-100): ";
            cin >> value;

            attentionLevels.push_back(value);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Driver Monitoring System
 */
class DriverMonitoringSystem : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Driver Monitoring Report =====\n";

        for(int level : attentionLevels) {

            if(level < 30) {

                cout << level
                     << " -> Driver Distracted ⚠️\n";
            }
            else if(level < 60) {

                cout << level
                     << " -> Driver Attention Moderate 🚗\n";
            }
            else {

                cout << level
                     << " -> Driver Alert ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    DriverMonitoringSystem dms;

    sensor = &dms;

    dms.inputReadings();

    sensor->checkStatus();

    return 0;
}