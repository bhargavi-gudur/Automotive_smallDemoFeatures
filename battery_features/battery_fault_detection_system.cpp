/**
 * @file battery_fault_detection_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Battery Fault Detection
 *   System. It monitors battery voltage and
 *   temperature to detect battery faults.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 04-08-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor
{
protected:
    vector<float> batteryData;

public:

    void inputReadings()
    {
        int n;
        float voltage;
        float temperature;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Battery Voltage (V): ";
            cin >> voltage;
            batteryData.push_back(voltage);

            cout << "Battery Temperature (°C): ";
            cin >> temperature;
            batteryData.push_back(temperature);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Battery Fault Detection System
 */
class BatteryFaultDetection : public Sensor
{
public:

    void checkStatus() override
    {
        cout << "\n===== Battery Fault Detection Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < batteryData.size(); i += 2)
        {
            float voltage = batteryData[i];
            float temperature = batteryData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(voltage < 3.0)
            {
                cout << "Under Voltage Fault ⚠️" << endl;
            }
            else if(voltage > 4.20)
            {
                cout << "Over Voltage Fault ⚠️" << endl;
            }
            else if(temperature > 60)
            {
                cout << "Over Temperature Fault 🔥" << endl;
            }
            else
            {
                cout << "Battery Operating Normally ✅" << endl;
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main()
{
    Sensor *sensor;

    BatteryFaultDetection battery;

    sensor = &battery;

    battery.inputReadings();

    sensor->checkStatus();

    return 0;
}