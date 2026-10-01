/**
 * @file ev_battery_vibration_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery vibration sensor and mechanical impact detection.
 * @date 18-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one vibration sensor
struct VibrationSensor
{
    int sensorId;
    string location;
    double vibrationG;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryVibrationMonitor : public EVSensorSystem
{
private:
    vector<VibrationSensor> sensors;

    unordered_map<string, double> vibrationLimits{
        {"WARNING", 2.5},
        {"CRITICAL", 5.0}
    };

public:
    BatteryVibrationMonitor(
        const vector<VibrationSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No vibration sensor data available.\n";
            return;
        }

        // Calculate average vibration
        double totalVibration = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const VibrationSensor& sensor)
            {
                return total + sensor.vibrationG;
            });

        double averageVibration =
            totalVibration / sensors.size();

        // Find highest vibration sensor
        auto highestSensor = max_element(
            sensors.begin(),
            sensors.end(),
            [](const VibrationSensor& first,
               const VibrationSensor& second)
            {
                return first.vibrationG <
                       second.vibrationG;
            });

        // Count abnormal sensors
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const VibrationSensor& sensor)
            {
                return sensor.vibrationG >=
                       vibrationLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY VIBRATION MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Vibration: "
                 << fixed << setprecision(2)
                 << sensor.vibrationG << " g";

            if (sensor.vibrationG >=
                vibrationLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.vibrationG >=
                     vibrationLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Vibration : "
             << averageVibration << " g";

        cout << "\nHighest Vibration : Sensor "
             << highestSensor->sensorId
             << " (" << highestSensor->vibrationG
             << " g)";

        cout << "\nAbnormal Sensors  : "
             << abnormalSensors;

        if (highestSensor->vibrationG >=
            vibrationLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nImpact Alert      : Severe mechanical impact detected";
            cout << "\nAction            : Stop vehicle and inspect battery pack.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nImpact Alert      : Excessive vibration detected";
            cout << "\nAction            : Inspect battery mounting and enclosure.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nImpact Alert      : No abnormal vibration detected";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n=========================================\n";
    }
};

int main()
{
    vector<VibrationSensor> batterySensors{
        {1, "Front Battery Module", 0.85},
        {2, "Center Battery Module", 1.20},
        {3, "Rear Battery Module", 3.40},
        {4, "Left Battery Module", 1.05},
        {5, "Right Battery Module", 0.95}
    };

    BatteryVibrationMonitor vibrationMonitor(batterySensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &vibrationMonitor;

    sensorSystem->processData();

    return 0;
}