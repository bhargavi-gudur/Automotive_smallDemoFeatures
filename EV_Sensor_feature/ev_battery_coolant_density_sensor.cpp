/**
 * @file ev_battery_coolant_density_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant density sensor and concentration monitoring.
 * @date 27-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant density sensor
struct CoolantDensitySensor
{
    int sensorId;
    string location;
    double densityKgPerM3;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class CoolantDensityMonitor : public EVSensorSystem
{
private:
    vector<CoolantDensitySensor> sensors;

    unordered_map<string, double> densityLimits{
        {"LOW_WARNING", 1020.0},
        {"LOW_CRITICAL", 990.0},
        {"HIGH_WARNING", 1100.0},
        {"HIGH_CRITICAL", 1150.0}
    };

    bool isLowDensity(double density) const
    {
        return density < densityLimits.at("LOW_WARNING");
    }

    bool isHighDensity(double density) const
    {
        return density > densityLimits.at("HIGH_WARNING");
    }

public:
    CoolantDensityMonitor(
        const vector<CoolantDensitySensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant density sensor data available.\n";
            return;
        }

        // Calculate average density
        double totalDensity = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantDensitySensor& sensor)
            {
                return total + sensor.densityKgPerM3;
            });

        double averageDensity =
            totalDensity / sensors.size();

        // Find lowest density
        auto lowestSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantDensitySensor& first,
               const CoolantDensitySensor& second)
            {
                return first.densityKgPerM3 <
                       second.densityKgPerM3;
            });

        // Find highest density
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantDensitySensor& first,
               const CoolantDensitySensor& second)
            {
                return first.densityKgPerM3 <
                       second.densityKgPerM3;
            });

        // Count abnormal density readings
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantDensitySensor& sensor)
            {
                return isLowDensity(sensor.densityKgPerM3) ||
                       isHighDensity(sensor.densityKgPerM3);
            });

        cout << "\n===== EV BATTERY COOLANT DENSITY MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Density: "
                 << fixed << setprecision(1)
                 << sensor.densityKgPerM3 << " kg/m3";

            if (sensor.densityKgPerM3 <
                densityLimits.at("LOW_CRITICAL"))
            {
                cout << " | LOW CRITICAL";
            }
            else if (sensor.densityKgPerM3 <
                     densityLimits.at("LOW_WARNING"))
            {
                cout << " | LOW WARNING";
            }
            else if (sensor.densityKgPerM3 >
                     densityLimits.at("HIGH_CRITICAL"))
            {
                cout << " | HIGH CRITICAL";
            }
            else if (sensor.densityKgPerM3 >
                     densityLimits.at("HIGH_WARNING"))
            {
                cout << " | HIGH WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Density    : "
             << averageDensity << " kg/m3";

        cout << "\nLowest Density     : Sensor "
             << lowestSensor->sensorId
             << " (" << lowestSensor->densityKgPerM3
             << " kg/m3)";

        cout << "\nHighest Density    : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->densityKgPerM3
             << " kg/m3)";

        cout << "\nAbnormal Sensors   : "
             << abnormalSensors;

        if (lowestSensor->densityKgPerM3 <
                densityLimits.at("LOW_CRITICAL") ||
            highestSensor->densityKgPerM3 >
                densityLimits.at("HIGH_CRITICAL"))
        {
            cout << "\nSystem Status      : CRITICAL";
            cout << "\nConcentration Alert: Significant coolant concentration deviation";
            cout << "\nAction             : Inspect coolant mixture and cooling circuit.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status      : WARNING";
            cout << "\nConcentration Alert: Coolant density outside normal range";
            cout << "\nAction             : Check coolant concentration and service condition.";
        }
        else
        {
            cout << "\nSystem Status      : NORMAL";
            cout << "\nConcentration Alert: Coolant density within monitored range";
            cout << "\nAction             : Continue monitoring.";
        }

        cout << "\n================================================\n";
    }
};

int main()
{
    vector<CoolantDensitySensor> coolantSensors{
        {1, "Pump Outlet", 1065.0},
        {2, "Front Battery Loop", 1072.0},
        {3, "Center Battery Loop", 1012.0},
        {4, "Rear Battery Loop", 1068.0},
        {5, "Pump Return", 1060.0}
    };

    CoolantDensityMonitor densityMonitor(coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &densityMonitor;

    sensorSystem->processData();

    return 0;
}