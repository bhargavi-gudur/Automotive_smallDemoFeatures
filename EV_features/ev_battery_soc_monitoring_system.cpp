/**
 * @file ev_battery_soc_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Battery State
 *   of Charge (SOC) Monitoring System.
 *   It monitors battery SOC and charging status
 *   to provide battery health information.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 28-07-2026
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
     * @brief Input battery readings
     */
    void inputReadings()
    {
        int n;
        int soc;
        int chargingStatus;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Battery SOC (%): ";
            cin >> soc;
            batteryData.push_back(soc);

            cout << "Charging Status (1=Charging, 0=Not Charging): ";
            cin >> chargingStatus;
            batteryData.push_back(chargingStatus);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief EV Battery SOC Monitoring System
 */
class BatterySOCMonitoring : public Sensor
{
public:

    /**
     * @brief Analyze battery SOC
     */
    void checkStatus() override
    {
        cout << "\n===== Battery SOC Monitoring Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < batteryData.size(); i += 2)
        {
            int soc = batteryData[i];
            int charging = batteryData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(soc < 20 && charging == 0)
            {
                cout << "Low Battery! Charge Immediately ⚠️" << endl;
            }
            else if(soc < 20 && charging == 1)
            {
                cout << "Battery Charging - Low SOC 🔋" << endl;
            }
            else if(soc >= 20 && soc <= 80)
            {
                cout << "Battery Charge Normal ✅" << endl;
            }
            else
            {
                cout << "Battery Fully Charged 🚗" << endl;
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

    BatterySOCMonitoring socMonitor;

    sensor = &socMonitor;

    socMonitor.inputReadings();

    sensor->checkStatus();

    return 0;
}