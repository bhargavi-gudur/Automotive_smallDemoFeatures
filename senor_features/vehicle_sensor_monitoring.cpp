/**
 * @file vehicle_sensor_monitoring.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive Vehicle Sensor Monitoring System.
 *
 *   The system monitors a fixed set of six sensor
 *   channels using the STL array container.
 *   Each sensor value is checked against a safe range.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL array
 *   - Range-based for loop
 *
 * @date 14-08-2026
 */

#include <array>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/**
 * @class Sensor
 * @brief Abstract base class for vehicle sensors.
 */
class Sensor
{
public:

    /**
     * @brief Accept sensor data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Analyze sensor data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Sensor() = default;
};

/**
 * @class VehicleSensorMonitor
 * @brief Monitors a fixed set of vehicle sensor values.
 */
class VehicleSensorMonitor : public Sensor
{
private:

    /**
     * @brief Fixed number of vehicle sensor readings.
     */
    array<float, 6> sensorValues{};

    /**
     * @brief Names corresponding to sensor channels.
     */
    const array<string, 6> sensorNames =
    {
        "Engine Temperature",
        "Battery Voltage",
        "Oil Pressure",
        "Coolant Temperature",
        "Brake Pressure",
        "Engine RPM"
    };

public:

    /**
     * @brief Input sensor values.
     */
    void inputData() override
    {
        cout << "===== Vehicle Sensor Input =====\n";

        for(size_t i = 0; i < sensorValues.size(); ++i)
        {
            cout << "Enter "
                 << sensorNames[i]
                 << ": ";

            cin >> sensorValues[i];
        }
    }

    /**
     * @brief Analyze vehicle sensor values.
     */
    void processData() override
    {
        cout << "\n===== Vehicle Sensor Report =====\n";

        for(size_t i = 0; i < sensorValues.size(); ++i)
        {
            cout << left
                 << setw(25)
                 << sensorNames[i]
                 << ": "
                 << sensorValues[i];

            bool fault = false;

            if(i == 0 && sensorValues[i] > 110)
                fault = true;

            else if(i == 1 &&
                    (sensorValues[i] < 11 ||
                     sensorValues[i] > 15))
                fault = true;

            else if(i == 2 && sensorValues[i] < 20)
                fault = true;

            else if(i == 3 && sensorValues[i] > 105)
                fault = true;

            else if(i == 4 && sensorValues[i] < 30)
                fault = true;

            else if(i == 5 && sensorValues[i] > 6000)
                fault = true;

            if(fault)
            {
                cout << " -> FAULT DETECTED ⚠️";
            }
            else
            {
                cout << " -> NORMAL";
            }

            cout << endl;
        }
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    Sensor* sensor =
        new VehicleSensorMonitor();

    sensor->inputData();

    sensor->processData();

    delete sensor;

    return 0;
}