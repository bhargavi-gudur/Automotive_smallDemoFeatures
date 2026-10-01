/**
 * @file ev_battery_coolant_pressure_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant pressure sensor and cooling pump fault detection.
 * @date 21-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant pressure sensor
struct CoolantPressureSensor
{
    int sensorId;
    string location;
    double pressureBar;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCoolantPressureMonitor : public EVSensorSystem
{
private:
    vector<CoolantPressureSensor> sensors;

    unordered_map<string, double> pressureLimits{
        {"LOW_WARNING", 1.5},
        {"LOW_CRITICAL", 0.8},
        {"HIGH_WARNING", 3.5},
        {"HIGH_CRITICAL", 4.5}
    };

    bool isLowPressure(double pressure) const
    {
        return pressure < pressureLimits.at("LOW_WARNING");
    }

    bool isHighPressure(double pressure) const
    {
        return pressure > pressureLimits.at("HIGH_WARNING");
    }

public:
    BatteryCoolantPressureMonitor(
        const vector<CoolantPressureSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant pressure sensor data available.\n";
            return;
        }

        // Calculate average pressure
        double totalPressure = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantPressureSensor& sensor)
            {
                return total + sensor.pressureBar;
            });

        double averagePressure =
            totalPressure / sensors.size();

        // Find lowest pressure
        auto lowestSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantPressureSensor& first,
               const CoolantPressureSensor& second)
            {
                return first.pressureBar <
                       second.pressureBar;
            });

        // Find highest pressure
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantPressureSensor& first,
               const CoolantPressureSensor& second)
            {
                return first.pressureBar <
                       second.pressureBar;
            });

        // Count abnormal pressure readings
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantPressureSensor& sensor)
            {
                return isLowPressure(sensor.pressureBar) ||
                       isHighPressure(sensor.pressureBar);
            });

        cout << "\n===== EV BATTERY COOLANT PRESSURE MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Pressure: "
                 << fixed << setprecision(2)
                 << sensor.pressureBar << " bar";

            if (sensor.pressureBar <
                pressureLimits.at("LOW_CRITICAL"))
            {
                cout << " | LOW CRITICAL";
            }
            else if (sensor.pressureBar <
                     pressureLimits.at("LOW_WARNING"))
            {
                cout << " | LOW WARNING";
            }
            else if (sensor.pressureBar >
                     pressureLimits.at("HIGH_CRITICAL"))
            {
                cout << " | HIGH CRITICAL";
            }
            else if (sensor.pressureBar >
                     pressureLimits.at("HIGH_WARNING"))
            {
                cout << " | HIGH WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Pressure : "
             << averagePressure << " bar";

        cout << "\nLowest Pressure  : Sensor "
             << lowestSensor->sensorId
             << " (" << lowestSensor->pressureBar
             << " bar)";

        cout << "\nHighest Pressure : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->pressureBar
             << " bar)";

        cout << "\nAbnormal Sensors : "
             << abnormalSensors;

        if (lowestSensor->pressureBar <
                pressureLimits.at("LOW_CRITICAL") ||
            highestSensor->pressureBar >
                pressureLimits.at("HIGH_CRITICAL"))
        {
            cout << "\nSystem Status    : CRITICAL";
            cout << "\nPump Alert       : Cooling-system pressure fault";
            cout << "\nAction           : Stop high-load operation and inspect coolant pump.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status    : WARNING";
            cout << "\nPump Alert       : Abnormal coolant pressure detected";
            cout << "\nAction           : Inspect pump, hoses and cooling circuit.";
        }
        else
        {
            cout << "\nSystem Status    : NORMAL";
            cout << "\nPump Alert       : Coolant pressure is within limits";
            cout << "\nAction           : Continue monitoring.";
        }

        cout << "\n================================================\n";
    }
};

int main()
{
    vector<CoolantPressureSensor> coolantSensors{
        {1, "Pump Outlet", 2.80},
        {2, "Front Battery Loop", 2.45},
        {3, "Center Battery Loop", 1.25},
        {4, "Rear Battery Loop", 2.60},
        {5, "Pump Return", 2.30}
    };

    BatteryCoolantPressureMonitor pressureMonitor(
        coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &pressureMonitor;

    sensorSystem->processData();

    return 0;
}