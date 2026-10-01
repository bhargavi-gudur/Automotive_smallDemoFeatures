/**
 * @file ev_battery_soh_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Battery State
 *   of Health (SOH) Monitoring System.
 *   It monitors battery SOH and charge cycle count
 *   to evaluate battery condition.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 29-07-2026
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
        int soh;
        int chargeCycles;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Battery SOH (%): ";
            cin >> soh;
            batteryData.push_back(soh);

            cout << "Enter Charge Cycle Count: ";
            cin >> chargeCycles;
            batteryData.push_back(chargeCycles);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Battery SOH Monitoring System
 */
class BatterySOHMonitoring : public Sensor
{
public:

    /**
     * @brief Analyze battery health
     */
    void checkStatus() override
    {
        cout << "\n===== Battery SOH Monitoring Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < batteryData.size(); i += 2)
        {
            int soh = batteryData[i];
            int cycles = batteryData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(so