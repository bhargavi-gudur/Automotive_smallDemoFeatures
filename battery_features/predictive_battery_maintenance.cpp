/**
 * @file predictive_battery_maintenance.cpp
 * @author Gandla Bhargavi
 * @brief Predictive Battery Maintenance System
 * @date 06-08-2026
 */

#include <iostream>
#include <map>
using namespace std;

/**
 * @brief Base Class
 */
class Sensor
{
protected:
    map<string, float> batteryParameters;

public:

    virtual void inputData() = 0;

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Predictive Battery Maintenance
 */
class BatteryMaintenance : public Sensor
{
public:

    void inputData() override
    {
        float value;

        cout << "Enter Battery Voltage (V): ";
        cin >> value;
        batteryParameters["Voltage"] = value;

        cout << "Enter Battery Temperature (°C): ";
        cin >> value;
        batteryParameters["Temperature"] = value;

        cout << "Enter State of Health (%): ";
        cin >> value;
        batteryParameters["SOH"] = value;

        cout << "Enter Charge Cycles: ";
        cin >> value;
        batteryParameters["ChargeCycles"] = value;
    }

    void checkStatus() override
    {
        cout << "\n===== Battery Maintenance Report =====\n";

        for(const auto &parameter : batteryParameters)
        {
            cout << parameter.first
                 << " : "
                 << parameter.second
                 << endl;
        }

        if(batteryParameters["Voltage"] < 3.2)
        {
            cout << "\nLow Battery Voltage Detected ⚠️" << endl;
        }

        if(batteryParameters["Temperature"] > 50)
        {
            cout << "Battery Overheating ⚠️" << endl;
        }

        if(batteryParameters["SOH"] < 80)
        {
            cout << "Battery Health Degraded ⚠️" << endl;
        }

        if(batteryParameters["ChargeCycles"] > 1500)
        {
            cout << "Battery Replacement Recommended 🔋" << endl;
        }

        if(batteryParameters["Voltage"] >= 3.2 &&
           batteryParameters["Temperature"] <= 50 &&
           batteryParameters["SOH"] >= 80 &&
           batteryParameters["ChargeCycles"] <= 1500)
        {
            cout << "Battery Condition Healthy ✅" << endl;
        }
    }
};

int main()
{
    Sensor *sensor;

    BatteryMaintenance battery;

    sensor = &battery;

    sensor->inputData();

    sensor->checkStatus();

    return 0;
}