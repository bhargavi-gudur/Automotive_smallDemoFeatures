/**
 * @file ev_battery_gas_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery gas sensor monitoring and thermal event detection.
 * @date 16-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one gas sensor
struct GasSensor
{
    int sensorId;
    string location;
    double gasLevelPpm;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryGasMonitor : public EVSensorSystem
{
private:
    vector<GasSensor> sensors;

    unordered_map<string, double> gasLimits{
        {"WARNING", 50.0},
        {"CRITICAL", 100.0}
    };

public:
    BatteryGasMonitor(const vector<GasSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No gas sensor data available.\n";
            return;
        }

        // Calculate average gas concentration
        double totalGas = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const GasSensor& sensor)
            {
                return total + sensor.gasLevelPpm;
            });

        double averageGas = totalGas / sensors.size();

        // Find sensor with highest gas concentration
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const GasSensor& first,
               const GasSensor& second)
            {
                return first.gasLevelPpm <
                       second.gasLevelPpm;
            });

        // Count abnormal sensors
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const GasSensor& sensor)
            {
                return sensor.gasLevelPpm >=
                       gasLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY GAS SENSOR MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Gas Level: "
                 << fixed << setprecision(1)
                 << sensor.gasLevelPpm << " ppm";

            if (sensor.gasLevelPpm >=
                gasLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.gasLevelPpm >=
                     gasLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Gas Level : "
             << averageGas << " ppm";

        cout << "\nHighest Gas Level : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->gasLevelPpm
             << " ppm)";

        cout << "\nAbnormal Sensors  : "
             << abnormalSensors;

        if (highestSensor->gasLevelPpm >=
            gasLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nThermal Alert     : Possible battery safety event";
            cout << "\nAction            : Stop charging and isolate battery system.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nThermal Alert     : Abnormal gas concentration detected";
            cout << "\nAction            : Inspect battery pack immediately.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nThermal Alert     : No abnormal gas detected";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n==========================================\n";
    }
};

int main()
{
    vector<GasSensor> batterySensors{
        {1, "Front Battery Module", 18.5},
        {2, "Center Battery Module", 27.4},
        {3, "Rear Battery Module", 64.8},
        {4, "Left Battery Module", 31.2},
        {5, "Right Battery Module", 22.6}
    };

    BatteryGasMonitor gasMonitor(batterySensors);

    // Polymorphism
    EVSensorSystem* sensorSystem = &gasMonitor;

    sensorSystem->processData();

    return 0;
}