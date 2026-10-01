/**
 * @file smart_tire_wear_monitoring.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Tire Wear Monitoring System.
 *   It monitors tire tread depth readings and
 *   generates maintenance alerts.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 12-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> treadDepths;

public:

    /**
     * @brief Input tire tread depth readings
     */
    void inputReadings() {

        int n;
        float depth;

        cout << "Enter number of tire readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter tread depth (mm): ";
            cin >> depth;

            treadDepths.push_back(depth);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Smart Tire Wear Monitoring System
 */
class TireWearMonitoring : public Sensor {

public:

    /**
     * @brief Check tire wear condition
     */
    void checkStatus() override {

        cout << "\n===== Tire Wear Monitoring Report =====\n";

        int tireNumber = 1;

        for(float depth : treadDepths) {

            cout << "Tire " << tireNumber++ << " : ";

            if(depth < 1.6) {

                cout << depth
                     << " mm -> Replace Tire Immediately ⚠️\n";
            }
            else if(depth < 3.0) {

                cout << depth
                     << " mm -> Tire Wear Detected, Service Soon\n";
            }
            else {

                cout << depth
                     << " mm -> Tire Condition Good ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    TireWearMonitoring tire;

    sensor = &tire;

    tire.inputReadings();

    sensor->checkStatus();

    return 0;
}