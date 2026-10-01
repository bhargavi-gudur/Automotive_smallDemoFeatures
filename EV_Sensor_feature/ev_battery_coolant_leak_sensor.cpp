/**
 * @file ev_battery_coolant_leak_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant leak sensor and leakage detection.
 * @date 24-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant leak sensor
struct CoolantLeakSensor
{
    int sensorId;
    string location;
    double leakLevel;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCoolantLeakMonitor : public EVSensorSystem
{
private:
    vector<CoolantLeakSensor> sensors;

    unordered_map<string, double> leakLimits{
        {"WARNING", 20.0},
        {"CRITICAL", 50.0}
    };

public:
    BatteryCoolantLeakMonitor(
        const vector<CoolantLeakSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant leak sensor data available.\n";
            return;
        }

        // Calculate average leak sensor level
        double totalLeak = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantLeakSensor& sensor)
            {
                return total + sensor.leakLevel;
            });

        double averageLeak =
            totalLeak / sensors.size();

        // Find the highest leak reading
        auto highestLeakSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantLeakSensor& first,
               const CoolantLeakSensor& second)
            {
                return first.leakLevel <
                       second.leakLevel;
            });

        // Count abnormal leak sensors
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantLeakSensor& sensor)
            {
                return sensor.leakLevel >=
                       leakLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY COOLANT LEAK MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Leak Level: "
                 << fixed << setprecision(1)
                 << sensor.leakLevel << " units";

            if (sensor.leakLevel >=
                leakLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.leakLevel >=
                     leakLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Leak Level : "
             << averageLeak << " units";

        cout << "\nHighest Leak Level : Sensor "
             << highestLeakSensor->sensorId
             << " (" << highestLeakSensor->leakLevel
             << " units)";

        cout << "\nAbnormal Sensors   : "
             << abnormalSensors;

        if (highestLeakSensor->leakLevel >=
            leakLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status      : CRITICAL";
            cout << "\nLeak Alert         : Severe coolant leakage detected";
            cout << "\nAction             : Stop high-load operation and inspect cooling circuit.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status      : WARNING";
            cout << "\nLeak Alert         : Possible coolant leakage detected";
            cout << "\nAction             : Inspect hoses, reservoir and cooling connections.";
        }
        else
        {
            cout << "\nSystem Status      : NORMAL";
            cout << "\nLeak Alert         : No coolant leakage detected";
            cout << "\nAction             : Continue monitoring.";
        }

        cout << "\n=============================================\n";
    }
};

int main()
{
    vector<CoolantLeakSensor> leakSensors{
        {1, "Front Battery Module", 8.5},
        {2, "Center Battery Module", 14.2},
        {3, "Rear Battery Module", 32.7},
        {4, "Coolant Pump Area", 11.4},
        {5, "Battery Enclosure Floor", 6.8}
    };

    BatteryCoolantLeakMonitor leakMonitor(leakSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &leakMonitor;

    sensorSystem->processData();

    return 0;
}