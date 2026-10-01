/**
 * @file ev_battery_coolant_flow_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant flow sensor and cooling system failure detection.
 * @date 20-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one coolant flow sensor
struct CoolantFlowSensor
{
    int sensorId;
    string location;
    double flowRateLpm;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCoolantFlowMonitor : public EVSensorSystem
{
private:
    vector<CoolantFlowSensor> sensors;

    unordered_map<string, double> flowLimits{
        {"WARNING", 4.0},
        {"CRITICAL", 2.0}
    };

public:
    BatteryCoolantFlowMonitor(
        const vector<CoolantFlowSensor>& sensorData)
        : sensors(sensorData)
    {
    }

    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No coolant flow sensor data available.\n";
            return;
        }

        // Calculate average coolant flow
        double totalFlow = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total,
               const CoolantFlowSensor& sensor)
            {
                return total + sensor.flowRateLpm;
            });

        double averageFlow =
            totalFlow / sensors.size();

        // Find the lowest flow sensor
        auto lowestFlowSensor = min_element(
            sensors.begin(),
            sensors.end(),
            [](const CoolantFlowSensor& first,
               const CoolantFlowSensor& second)
            {
                return first.flowRateLpm <
                       second.flowRateLpm;
            });

        // Count sensors below warning threshold
        int abnormalSensors = count_if(
            sensors.begin(),
            sensors.end(),
            [this](const CoolantFlowSensor& sensor)
            {
                return sensor.flowRateLpm <
                       flowLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY COOLANT FLOW MONITOR =====\n";

        for (const auto& sensor : sensors)
        {
            cout << "Sensor " << sensor.sensorId
                 << " | Location: " << sensor.location
                 << " | Flow: "
                 << fixed << setprecision(1)
                 << sensor.flowRateLpm << " L/min";

            if (sensor.flowRateLpm <
                flowLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (sensor.flowRateLpm <
                     flowLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Flow      : "
             << averageFlow << " L/min";

        cout << "\nLowest Flow       : Sensor "
             << lowestFlowSensor->sensorId
             << " (" << lowestFlowSensor->flowRateLpm
             << " L/min)";

        cout << "\nAbnormal Sensors  : "
             << abnormalSensors;

        if (lowestFlowSensor->flowRateLpm <
            flowLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nCooling Alert     : Insufficient coolant flow";
            cout << "\nAction            : Stop high-load operation and inspect cooling system.";
        }
        else if (abnormalSensors > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nCooling Alert     : Reduced coolant flow detected";
            cout << "\nAction            : Inspect coolant pump, hoses and restrictions.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nCooling Alert     : Coolant flow is within limits";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n============================================\n";
    }
};

int main()
{
    vector<CoolantFlowSensor> coolantSensors{
        {1, "Front Battery Cooling Loop", 6.8},
        {2, "Center Battery Cooling Loop", 5.9},
        {3, "Rear Battery Cooling Loop", 3.2},
        {4, "Left Battery Module", 6.1},
        {5, "Right Battery Module", 5.7}
    };

    BatteryCoolantFlowMonitor flowMonitor(coolantSensors);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &flowMonitor;

    sensorSystem->processData();

    return 0;
}