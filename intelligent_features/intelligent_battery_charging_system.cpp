/**
 * @file intelligent_battery_charging_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Battery
 *   Charging System. It monitors the battery's
 *   State of Charge (SOC) and charging current
 *   to control the charging process.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 24-07-2026
 */

#include<iostream>
#include<vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor
{
protected:
    vector<int> batteryData;

public:

    /**
     * @brief Input battery charging readings
     */
    void inputReadings()
    {
        int n;
        int soc;
        int chargingCurrent;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Battery SOC (%): ";
            cin >> soc;
            batteryData.push_back(soc);

            cout << "Enter Charging Current (A): ";
            cin >> chargingCurrent;
            batteryData.push_back(chargingCurrent);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Intelligent Battery Charging System
 */
class IntelligentBatteryCharging : public Sensor
{
public:

    /**
     * @brief Analyze battery charging status
     */
    void checkStatus() override
    {
        cout << "\n===== Intelligent Battery Charging Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < batteryData.size(); i += 2)
        {
            int soc = batteryData[i];
            int current = batteryData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(soc < 80 && current > 0)
            {
                cout << "Fast Charging Enabled ✅" << endl;
            }
            else if(soc >= 80 && soc < 100)
            {
                cout << "Switch to Trickle Charging ⚡" << endl;
            }
            else if(soc >= 100)
            {
                cout << "Charging Complete - Stop Charging 🔋" << endl;
            }
            else
            {
                cout << "Battery Not Charging" << endl;
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

    IntelligentBatteryCharging battery;

    sensor = &battery;

    battery.inputReadings();

    sensor->checkStatus();

    return 0;
}