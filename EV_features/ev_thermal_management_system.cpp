/**
 * @file ev_thermal_management_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Thermal Management
 *   System. It monitors battery temperature and
 *   coolant level to determine whether the cooling
 *   system should be activated.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 23-07-2026
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
    vector<int> thermalData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int batteryTemp;
        int coolantLevel;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Battery Temperature (°C): ";
            cin >> batteryTemp;
            thermalData.push_back(batteryTemp);

            cout << "Coolant Level (%): ";
            cin >> coolantLevel;
            thermalData.push_back(coolantLevel);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief EV Thermal Management System
 */
class EVThermalManagement : public Sensor
{
public:

    /**
     * @brief Analyze battery temperature
     */
    void checkStatus() override
    {
        cout << "\n===== EV Thermal Management Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < thermalData.size(); i += 2)
        {
            int batteryTemp = thermalData[i];
            int coolantLevel = thermalData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(batteryTemp > 45 && coolantLevel > 30)
            {
                cout << "Cooling System Activated ✅" << endl;
            }
            else if(batteryTemp > 45 && coolantLevel <= 30)
            {
                cout << "Warning! Low Coolant Level - Battery Overheating ⚠️" << endl;
            }
            else
            {
                cout << "Battery Temperature Normal" << endl;
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

    EVThermalManagement thermal;

    sensor = &thermal;

    thermal.inputReadings();

    sensor->checkStatus();

    return 0;
}