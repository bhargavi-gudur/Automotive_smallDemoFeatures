/**
 * @file ev_battery_coolant_conductivity_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant conductivity sensor and contamination detection.
 * @date 25-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant conductivity sensor
struct ConductivitySensor
{
    int sensorId;
    string location;
    double conductivityUsCm;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class CoolantConductivityMonitor : public EVSensorSystem
{
private:
    vector<ConductivitySensor> sensors;

    unordered_map<string, double> conductivityLimits{
        {"WARNING", 80.0},
        {"CRITICAL", 150.0}
    };

public:
    CoolantConductivityMonitor(
        const vector<ConductivitySensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant conductivity data available.\n";
            return;
        }

        // Calculate average conductivity
        double totalConductivity = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const ConductivitySensor& sensor)
            {
                return total + sensor.conductivityUsCm;
            });

        double averageConductivity =
            totalConductivity / sensors.size();

        // Find highest conductivity
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const ConductivitySensor& first,
               const ConductivitySensor& second)
            {
                return first.conductivityUsCm <
                       second.conductivityUsCm;
            });

        // Count abnormal sensors
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const ConductivitySensor& sensor)
            {
                return sensor.conductivityUsCm >=
                       conductivityLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY COOLANT CONDUCTIVITY MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Conductivity: "
                 << fixed << setprecision(1)
                 << sensor.conductivityUsCm << " uS/cm";

            if (sensor.conductivityUsCm >=
                conductivityLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.conductivityUsCm >=
                     conductivityLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Conductivity : "
             << averageConductivity << " uS/cm";

        cout << "\nHighest Conductivity : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->conductivityUsCm
             << " uS/cm)";

        cout << "\nAbnormal Sensors     : "
             << abnormalSensors;

        if (highestSensor->conductivityUsCm >=
            conductivityLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status        : CRITICAL";
            cout << "\nContamination Alert  : Significant coolant property change detected";
            cout << "\nAction               : Inspect coolant condition and cooling circuit.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status        : WARNING";
            cout << "\nContamination Alert  : Elevated coolant conductivity detected";
            cout << "\nAction               : Check coolant quality and service condition.";
        }
        else
        {
            cout << "\nSystem Status        : NORMAL";
            cout << "\nContamination Alert  : Conductivity within monitored limits";
            cout << "\nAction               : Continue monitoring.";
        }

        cout << "\n====================================================\n";
    }
};

int main()
{
    vector<ConductivitySensor> coolantSensors{
        {1, "Pump Outlet", 42.5},
        {2, "Front Battery Loop", 58.4},
        {3, "Center Battery Loop", 96.7},
        {4, "Rear Battery Loop", 51.3},
        {5, "Pump Return", 47.8}
    };

    CoolantConductivityMonitor conductivityMonitor(
        coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &conductivityMonitor;

    sensorSystem->processData();

    return 0;
}