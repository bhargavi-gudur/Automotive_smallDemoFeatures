/**
 * @file ev_battery_current_voltage_fault_detection.cpp
 * @author Gandla Bhargavi
 * @brief EV battery current and voltage sensor fusion for electrical fault detection.
 * @date 04-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

struct BatterySample
{
    int sensorId;
    string location;
    double voltageVolt;
    double currentAmpere;
};

class EVSensorSystem
{
protected:
    vector<BatterySample> samples;

public:
    EVSensorSystem(const vector<BatterySample>& data)
        : samples(data)
    {
    }

    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

class BatteryElectricalFaultMonitor : public EVSensorSystem
{
private:
    const double minimumVoltage = 340.0;
    const double maximumCurrent = 200.0;

public:
    BatteryElectricalFaultMonitor(
        const vector<BatterySample>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY ELECTRICAL FAULT MONITOR =====\n";

        unordered_map<int, string> statusMap;

        int abnormalCount = 0;

        for (const auto& sample : samples)
        {
            bool undervoltage =
                sample.voltageVolt < minimumVoltage;

            bool overcurrent =
                sample.currentAmpere > maximumCurrent;

            string status;

            if (undervoltage && overcurrent)
            {
                status = "CRITICAL";
            }
            else if (undervoltage || overcurrent)
            {
                status = "WARNING";
            }
            else
            {
                status = "NORMAL";
            }

            statusMap[sample.sensorId] = status;

            if (status != "NORMAL")
            {
                abnormalCount++;
            }

            cout << "Sensor " << sample.sensorId
                 << " | Location: " << sample.location
                 << " | Voltage: "
                 << sample.voltageVolt << " V"
                 << " | Current: "
                 << sample.currentAmpere << " A"
                 << " | Status: " << status
                 << '\n';
        }

        double totalVoltage = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double sum, const BatterySample& sample)
            {
                return sum + sample.voltageVolt;
            }
        );

        double averageVoltage =
            totalVoltage / samples.size();

        auto lowestVoltage = min_element(
            samples.begin(),
            samples.end(),
            [](const BatterySample& a,
               const BatterySample& b)
            {
                return a.voltageVolt <
                       b.voltageVolt;
            }
        );

        auto highestCurrent = max_element(
            samples.begin(),
            samples.end(),
            [](const BatterySample& a,
               const BatterySample& b)
            {
                return a.currentAmpere <
                       b.currentAmpere;
            }
        );

        int undervoltageCount = count_if(
            samples.begin(),
            samples.end(),
            [&](const BatterySample& sample)
            {
                return sample.voltageVolt <
                       minimumVoltage;
            }
        );

        int overcurrentCount = count_if(
            samples.begin(),
            samples.end(),
            [&](const BatterySample& sample)
            {
                return sample.currentAmpere >
                       maximumCurrent;
            }
        );

        cout << "\nAverage Voltage  : "
             << averageVoltage << " V\n";

        cout << "Lowest Voltage   : Sensor "
             << lowestVoltage->sensorId
             << " ("
             << lowestVoltage->voltageVolt
             << " V)\n";

        cout << "Highest Current  : Sensor "
             << highestCurrent->sensorId
             << " ("
             << highestCurrent->currentAmpere
             << " A)\n";

        cout << "Undervoltage Faults : "
             << undervoltageCount << '\n';

        cout << "Overcurrent Faults   : "
             << overcurrentCount << '\n';

        cout << "Abnormal Sensors     : "
             << abnormalCount << '\n';

        string highestCurrentStatus =
            statusMap[highestCurrent->sensorId];

        string lowestVoltageStatus =
            statusMap[lowestVoltage->sensorId];

        if (
            highestCurrentStatus == "CRITICAL" ||
            lowestVoltageStatus == "CRITICAL"
        )
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : Combined electrical fault detected\n";
            cout << "Action        : Reduce simulated load and inspect battery electrical parameters.\n";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Voltage or current anomaly detected\n";
            cout << "Action        : Continue monitoring and inspect affected sensor.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Electrical parameters are within demo limits\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "================================================\n";
    }
};

int main()
{
    vector<BatterySample> batteryData =
    {
        {1, "Battery Pack A", 360.0, 120.0},
        {2, "Battery Pack B", 350.0, 145.0},
        {3, "Battery Pack C", 330.0, 230.0},
        {4, "Battery Pack D", 362.0, 130.0},
        {5, "Battery Pack E", 345.0, 210.0}
    };

    BatteryElectricalFaultMonitor monitor(batteryData);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}