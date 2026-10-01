/**
 * @file ev_battery_pressure_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery pressure sensor monitoring and leak detection.
 * @date 14-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one battery pressure sensor
struct PressureSensor
{
    int sensorId;
    string location;
    double pressureKpa;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryPressureMonitor : public EVSensorSystem
{
private:
    vector<PressureSensor> sensors;

    unordered_map<string, double> pressureLimits{
        {"WARNING", 105.0},
        {"CRITICAL", 120.0}
    };

public:
    BatteryPressureMonitor(const vector<PressureSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No pressure sensor data available.\n";
            return;
        }

        double totalPressure = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const PressureSensor& sensor)
            {
                return total + sensor.pressureKpa;
            });

        double averagePressure =
            totalPressure / sensors.size();

        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const PressureSensor& first,
               const PressureSensor& second)
            {
                return first.pressureKpa < second.pressureKpa;
            });

        int abnormalCount = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const PressureSensor& sensor)
            {
                return sensor.pressureKpa >=
                       pressureLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY PRESSURE MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Pressure: "
                 << fixed << setprecision(1)
                 << sensor.pressureKpa << " kPa";

            if (sensor.pressureKpa >=
                pressureLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.pressureKpa >=
                     pressureLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Pressure : "
             << averagePressure << " kPa";

        cout << "\nHighest Pressure : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->pressureKpa
             << " kPa)";

        cout << "\nAbnormal Sensors : "
             << abnormalCount;

        if (highestSensor->pressureKpa >=
            pressureLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status    : CRITICAL";
            cout << "\nAction           : Stop vehicle and inspect battery pack.";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status    : WARNING";
            cout << "\nAction           : Inspect battery enclosure and pressure system.";
        }
        else
        {
            cout << "\nSystem Status    : NORMAL";
            cout << "\nAction           : Continue monitoring.";
        }

        cout << "\n=========================================\n";
    }
};

int main()
{
    vector<PressureSensor> batterySensors{
        {1, "Front Battery Pack", 98.5},
        {2, "Center Battery Pack", 102.3},
        {3, "Rear Battery Pack", 108.7},
        {4, "Left Battery Module", 101.4},
        {5, "Right Battery Module", 99.8}
    };

    BatteryPressureMonitor pressureMonitor(batterySensors);

    // Polymorphism
    EVSensorSystem* sensorSystem = &pressureMonitor;

    sensorSystem->processData();

    return 0;
}