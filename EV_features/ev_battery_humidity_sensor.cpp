/**
 * @file ev_battery_humidity_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery humidity sensor and moisture intrusion detection.
 * @date 15-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one humidity sensor
struct HumiditySensor
{
    int sensorId;
    string location;
    double humidityPercent;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryHumidityMonitor : public EVSensorSystem
{
private:
    vector<HumiditySensor> sensors;

    unordered_map<string, double> humidityLimits{
        {"WARNING", 65.0},
        {"CRITICAL", 80.0}
    };

public:
    BatteryHumidityMonitor(
        const vector<HumiditySensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No humidity sensor data available.\n";
            return;
        }

        // Calculate average humidity
        double totalHumidity = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const HumiditySensor& sensor)
            {
                return total + sensor.humidityPercent;
            });

        double averageHumidity =
            totalHumidity / sensors.size();

        // Find sensor with highest humidity
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const HumiditySensor& first,
               const HumiditySensor& second)
            {
                return first.humidityPercent <
                       second.humidityPercent;
            });

        // Count abnormal sensors
        int abnormalCount = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const HumiditySensor& sensor)
            {
                return sensor.humidityPercent >=
                       humidityLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY HUMIDITY MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Humidity: "
                 << fixed << setprecision(1)
                 << sensor.humidityPercent << "%";

            if (sensor.humidityPercent >=
                humidityLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.humidityPercent >=
                     humidityLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Humidity : "
             << averageHumidity << "%";

        cout << "\nHighest Humidity : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->humidityPercent
             << "%)";

        cout << "\nAbnormal Sensors : "
             << abnormalCount;

        if (highestSensor->humidityPercent >=
            humidityLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status    : CRITICAL";
            cout << "\nMoisture Alert   : Possible water/moisture intrusion";
            cout << "\nAction           : Isolate battery system and inspect enclosure.";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status    : WARNING";
            cout << "\nMoisture Alert   : Elevated humidity detected";
            cout << "\nAction           : Inspect battery enclosure seals.";
        }
        else
        {
            cout << "\nSystem Status    : NORMAL";
            cout << "\nMoisture Alert   : No abnormal moisture detected";
            cout << "\nAction           : Continue monitoring.";
        }

        cout << "\n=========================================\n";
    }
};

int main()
{
    vector<HumiditySensor> batterySensors{
        {1, "Front Battery Module", 48.5},
        {2, "Center Battery Module", 57.2},
        {3, "Rear Battery Module", 72.8},
        {4, "Left Battery Module", 51.6},
        {5, "Right Battery Module", 46.9}
    };

    BatteryHumidityMonitor humidityMonitor(batterySensors);

    // Polymorphism
    EVSensorSystem* sensorSystem = &humidityMonitor;

    sensorSystem->processData();

    return 0;
}