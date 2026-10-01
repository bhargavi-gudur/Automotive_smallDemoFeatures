/**
 * @file ev_battery_coolant_temperature_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant temperature sensor fusion and thermal gradient detection.
 * @date 22-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant temperature sensor
struct CoolantTemperatureSensor
{
    int sensorId;
    string location;
    double temperatureCelsius;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class CoolantTemperatureFusion : public EVSensorSystem
{
private:
    vector<CoolantTemperatureSensor> sensors;

    unordered_map<string, double> temperatureLimits{
        {"WARNING", 45.0},
        {"CRITICAL", 60.0},
        {"MAX_GRADIENT", 12.0}
    };

public:
    CoolantTemperatureFusion(
        const vector<CoolantTemperatureSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant temperature data available.\n";
            return;
        }

        // Calculate average coolant temperature
        double totalTemperature = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantTemperatureSensor& sensor)
            {
                return total + sensor.temperatureCelsius;
            });

        double averageTemperature =
            totalTemperature / sensors.size();

        // Find hottest sensor
        auto hottestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantTemperatureSensor& first,
               const CoolantTemperatureSensor& second)
            {
                return first.temperatureCelsius <
                       second.temperatureCelsius;
            });

        // Find coolest sensor
        auto coolestSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantTemperatureSensor& first,
               const CoolantTemperatureSensor& second)
            {
                return first.temperatureCelsius <
                       second.temperatureCelsius;
            });

        double thermalGradient =
            hottestSensor->temperatureCelsius -
            coolestSensor->temperatureCelsius;

        // Count high-temperature sensors
        int highTemperatureSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantTemperatureSensor& sensor)
            {
                return sensor.temperatureCelsius >=
                       temperatureLimits.at("WARNING");
            });

        cout << "\n===== EV COOLANT TEMPERATURE SENSOR FUSION =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Temperature: "
                 << fixed << setprecision(1)
                 << sensor.temperatureCelsius << " °C";

            if (sensor.temperatureCelsius >=
                temperatureLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.temperatureCelsius >=
                     temperatureLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Temperature : "
             << averageTemperature << " °C";

        cout << "\nHottest Sensor      : Sensor "
             << hottestSensor->sensorId
             << " (" << hottestSensor->temperatureCelsius
             << " °C)";

        cout << "\nCoolest Sensor      : Sensor "
             << coolestSensor->sensorId
             << " (" << coolestSensor->temperatureCelsius
             << " °C)";

        cout << "\nThermal Gradient    : "
             << thermalGradient << " °C";

        cout << "\nHigh Temp Sensors   : "
             << highTemperatureSensors;

        if (hottestSensor->temperatureCelsius >=
            temperatureLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status       : CRITICAL";
            cout << "\nThermal Alert       : Coolant temperature too high";
            cout << "\nAction              : Reduce battery load and inspect cooling system.";
        }
        else if (thermalGradient >=
                 temperatureLimits.at("MAX_GRADIENT"))
        {
            cout << "\nSystem Status       : WARNING";
            cout << "\nThermal Alert       : Large temperature gradient detected";
            cout << "\nAction              : Check coolant distribution and flow.";
        }
        else if (highTemperatureSensors > 0)
        {
            cout << "\nSystem Status       : WARNING";
            cout << "\nThermal Alert       : Elevated coolant temperature";
            cout << "\nAction              : Monitor cooling performance.";
        }
        else
        {
            cout << "\nSystem Status       : NORMAL";
            cout << "\nThermal Alert       : Coolant temperature balanced";
            cout << "\nAction              : Continue monitoring.";
        }

        cout << "\n================================================\n";
    }
};

int main()
{
    vector<CoolantTemperatureSensor> coolantSensors{
        {1, "Pump Outlet", 38.5},
        {2, "Front Battery Loop", 41.2},
        {3, "Center Battery Loop", 47.8},
        {4, "Rear Battery Loop", 39.6},
        {5, "Pump Return", 36.4}
    };

    CoolantTemperatureFusion temperatureMonitor(
        coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &temperatureMonitor;

    sensorSystem->processData();

    return 0;
}