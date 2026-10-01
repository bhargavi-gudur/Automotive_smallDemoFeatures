/**
 * @file vehicle_health_monitoring.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Vehicle Health
 *   Monitoring System.
 *   It monitors engine temperature,
 *   battery voltage and fuel level.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 05-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> sensorReadings;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of vehicle readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Engine Temperature (°C): ";
            cin >> value;
            sensorReadings.push_back(value);

            cout << "Battery Voltage (V): ";
            cin >> value;
            sensorReadings.push_back(value);

            cout << "Fuel Level (%): ";
            cin >> value;
            sensorReadings.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Vehicle Health Monitoring System
 */
class VehicleHealthMonitor : public Sensor {

public:

    /**
     * @brief Analyze vehicle health
     */
    void checkStatus() override {

        cout << "\n===== Vehicle Health Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < sensorReadings.size(); i += 3) {

            cout << "\nReading " << reading++ << endl;

            if(sensorReadings[i] > 100)
                cout << "Engine Temperature : High ⚠️\n";
            else
                cout << "Engine Temperature : Normal ✅\n";

            if(sensorReadings[i + 1] < 11.5)
                cout << "Battery Voltage : Low ⚠️\n";
            else
                cout << "Battery Voltage : Normal ✅\n";

            if(sensorReadings[i + 2] < 15)
                cout << "Fuel Level : Low ⚠️\n";
            else
                cout << "Fuel Level : Normal ✅\n";
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    VehicleHealthMonitor monitor;

    sensor = &monitor;

    monitor.inputReadings();

    sensor->checkStatus();

    return 0;
}