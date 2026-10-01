/**
 * @file ev_battery_coolant_level_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant level sensor and low-coolant detection.
 * @date 23-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant level sensor
struct CoolantLevelSensor
{
    int sensorId;
    string location;
    double levelPercent;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCoolantLevelMonitor : public EVSensorSystem
{
private:
    vector<CoolantLevelSensor> sensors;

    unordered_map<string, double> levelLimits{
        {"LOW_WARNING", 30.0},
        {"CRITICAL", 15.0}
    };

public:
    BatteryCoolantLevelMonitor(
        const vector<CoolantLevelSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant level sensor data available.\n";
            return;
        }

        // Calculate average coolant level
        double totalLevel = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantLevelSensor& sensor)
            {
                return total + sensor.levelPercent;
            });

        double averageLevel =
            totalLevel / sensors.size();

        // Find lowest coolant level
        auto lowestSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantLevelSensor& first,
               const CoolantLevelSensor& second)
            {
                return first.levelPercent <
                       second.levelPercent;
            });

        // Find highest coolant level
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantLevelSensor& first,
               const CoolantLevelSensor& second)
            {
                return first.levelPercent <
                       second.levelPercent;
            });

        // Count low-level sensors
        int lowLevelSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantLevelSensor& sensor)
            {
                return sensor.levelPercent <
                       levelLimits.at("LOW_WARNING");
            });

        cout << "\n===== EV BATTERY COOLANT LEVEL MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Coolant Level: "
                 << fixed << setprecision(1)
                 << sensor.levelPercent << "%";

            if (sensor.levelPercent <
                levelLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.levelPercent <
                     levelLimits.at("LOW_WARNING"))
            {
                cout << " | LOW WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Level      : "
             << averageLevel << "%";

        cout << "\nLowest Level       : Sensor "
             << lowestSensor->sensorId
             << " (" << lowestSensor->levelPercent
             << "%)";

        cout << "\nHighest Level      : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->levelPercent
             << "%)";

        cout << "\nLow-Level Sensors  : "
             << lowLevelSensors;

        if (lowestSensor->levelPercent <
            levelLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status      : CRITICAL";
            cout << "\nCoolant Alert      : Critically low coolant level";
            cout << "\nAction             : Stop high-load operation and inspect cooling system.";
        }
        else if (lowLevelSensors > 0)
        {
            cout << "\nSystem Status      : WARNING";
            cout << "\nCoolant Alert      : Low coolant level detected";
            cout << "\nAction             : Check reservoir and inspect for possible leakage.";
        }
        else
        {
            cout << "\nSystem Status      : NORMAL";
            cout << "\nCoolant Alert      : Coolant level is sufficient";
            cout << "\nAction             : Continue monitoring.";
        }

        cout << "\n=============================================\n";
    }
};

int main()
{
    vector<CoolantLevelSensor> coolantSensors{
        {1, "Main Reservoir", 72.5},
        {2, "Front Cooling Loop", 64.8},
        {3, "Center Battery Loop", 27.4},
        {4, "Rear Cooling Loop", 68.2},
        {5, "Auxiliary Reservoir", 59.6}
    };

    BatteryCoolantLevelMonitor levelMonitor(
        coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &levelMonitor;

    sensorSystem->processData();

    return 0;
}