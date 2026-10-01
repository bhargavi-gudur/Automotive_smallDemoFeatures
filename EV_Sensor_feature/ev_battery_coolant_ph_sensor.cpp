/**
 * @file ev_battery_coolant_ph_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant pH sensor and chemical condition monitoring.
 * @date 26-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant pH sensor
struct CoolantPHSensor
{
    int sensorId;
    string location;
    double phValue;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class CoolantPHMonitor : public EVSensorSystem
{
private:
    vector<CoolantPHSensor> sensors;

    unordered_map<string, double> phLimits{
        {"LOW_CRITICAL", 5.0},
        {"LOW_WARNING", 6.0},
        {"HIGH_WARNING", 9.0},
        {"HIGH_CRITICAL", 10.0}
    };

    bool isLow(double ph) const
    {
        return ph < phLimits.at("LOW_WARNING");
    }

    bool isHigh(double ph) const
    {
        return ph > phLimits.at("HIGH_WARNING");
    }

public:
    CoolantPHMonitor(
        const vector<CoolantPHSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant pH sensor data available.\n";
            return;
        }

        // Calculate average pH
        double totalPH = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantPHSensor& sensor)
            {
                return total + sensor.phValue;
            });

        double averagePH =
            totalPH / sensors.size();

        // Find lowest pH
        auto lowestSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantPHSensor& first,
               const CoolantPHSensor& second)
            {
                return first.phValue <
                       second.phValue;
            });

        // Find highest pH
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantPHSensor& first,
               const CoolantPHSensor& second)
            {
                return first.phValue <
                       second.phValue;
            });

        // Count sensors outside warning range
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantPHSensor& sensor)
            {
                return isLow(sensor.phValue) ||
                       isHigh(sensor.phValue);
            });

        cout << "\n===== EV BATTERY COOLANT pH MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | pH: "
                 << fixed << setprecision(2)
                 << sensor.phValue;

            if (sensor.phValue <
                phLimits.at("LOW_CRITICAL"))
            {
                cout << " | LOW CRITICAL";
            }
            else if (sensor.phValue <
                     phLimits.at("LOW_WARNING"))
            {
                cout << " | LOW WARNING";
            }
            else if (sensor.phValue >
                     phLimits.at("HIGH_CRITICAL"))
            {
                cout << " | HIGH CRITICAL";
            }
            else if (sensor.phValue >
                     phLimits.at("HIGH_WARNING"))
            {
                cout << " | HIGH WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage pH        : "
             << averagePH;

        cout << "\nLowest pH         : Sensor "
             << lowestSensor->sensorId
             << " (" << lowestSensor->phValue << ")";

        cout << "\nHighest pH        : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->phValue << ")";

        cout << "\nAbnormal Sensors  : "
             << abnormalSensors;

        if (lowestSensor->phValue <
                phLimits.at("LOW_CRITICAL") ||
            highestSensor->phValue >
                phLimits.at("HIGH_CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nChemical Alert    : Coolant pH is outside the critical range";
            cout << "\nAction            : Inspect coolant condition and cooling circuit.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nChemical Alert    : Coolant pH deviation detected";
            cout << "\nAction            : Check coolant quality and service condition.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nChemical Alert    : Coolant pH is within monitored range";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n===========================================\n";
    }
};

int main()
{
    vector<CoolantPHSensor> coolantSensors{
        {1, "Pump Outlet", 7.20},
        {2, "Front Battery Loop", 7.45},
        {3, "Center Battery Loop", 8.85},
        {4, "Rear Battery Loop", 7.35},
        {5, "Pump Return", 7.60}
    };

    CoolantPHMonitor phMonitor(coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &phMonitor;

    sensorSystem->processData();

    return 0;
}