/**
 * @file ev_battery_smoke_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery smoke/particulate sensor monitoring and early fire detection.
 * @date 17-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one smoke/particulate sensor
struct SmokeSensor
{
    int sensorId;
    string location;
    double particulateLevel;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatterySmokeMonitor : public EVSensorSystem
{
private:
    vector<SmokeSensor> sensors;

    unordered_map<string, double> limits{
        {"WARNING", 35.0},
        {"CRITICAL", 70.0}
    };

public:
    BatterySmokeMonitor(const vector<SmokeSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No smoke sensor data available.\n";
            return;
        }

        // Calculate average particulate level
        double totalLevel = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const SmokeSensor& sensor)
            {
                return total + sensor.particulateLevel;
            });

        double averageLevel =
            totalLevel / sensors.size();

        // Find sensor with highest particulate level
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const SmokeSensor& first,
               const SmokeSensor& second)
            {
                return first.particulateLevel <
                       second.particulateLevel;
            });

        // Count abnormal sensors
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const SmokeSensor& sensor)
            {
                return sensor.particulateLevel >=
                       limits.at("WARNING");
            });

        cout << "\n===== EV BATTERY SMOKE MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Particulate Level: "
                 << fixed << setprecision(1)
                 << sensor.particulateLevel << " units";

            if (sensor.particulateLevel >=
                limits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.particulateLevel >=
                     limits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Level     : "
             << averageLevel << " units";

        cout << "\nHighest Level     : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->particulateLevel
             << " units)";

        cout << "\nAbnormal Sensors  : "
             << abnormalSensors;

        if (highestSensor->particulateLevel >=
            limits.at("CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nFire Alert        : Possible smoke event detected";
            cout << "\nAction            : Stop charging and isolate battery system.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nFire Alert        : Elevated particulate level detected";
            cout << "\nAction            : Inspect battery enclosure.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nFire Alert        : No abnormal particulate detected";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n======================================\n";
    }
};

int main()
{
    vector<SmokeSensor> batterySensors{
        {1, "Front Battery Module", 12.5},
        {2, "Center Battery Module", 21.8},
        {3, "Rear Battery Module", 48.6},
        {4, "Left Battery Module", 18.2},
        {5, "Right Battery Module", 15.7}
    };

    BatterySmokeMonitor smokeMonitor(batterySensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &smokeMonitor;

    sensorSystem->processData();

    return 0;
}