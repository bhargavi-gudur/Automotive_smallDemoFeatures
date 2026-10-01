/**
 * @file ev_battery_voltage_current_sensor_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery voltage and current sensor fusion for power anomaly detection.
 * @date 29-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one battery electrical sensor sample
struct BatteryElectricalSample
{
    int sensorId;
    string location;
    double voltageVolt;
    double currentAmpere;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryPowerMonitor : public EVSensorSystem
{
private:
    vector<BatteryElectricalSample> samples;

    unordered_map<string, double> powerLimits{
        {"MIN_POWER_KW", 10.0},
        {"MAX_POWER_KW", 80.0}
    };

    double calculatePowerKW(
        const BatteryElectricalSample& sample) const
    {
        return (sample.voltageVolt *
                sample.currentAmpere) / 1000.0;
    }

public:
    BatteryPowerMonitor(
        const vector<BatteryElectricalSample>& sensorData)
        : samples(sensorData)
    {
    }

    void processData() override
    {
        if (samples.empty())
        {
            cout << "No voltage/current sensor data available.\n";
            return;
        }

        // Calculate total power
        double totalPower = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [this](double total,
                   const BatteryElectricalSample& sample)
            {
                return total + calculatePowerKW(sample);
            });

        double averagePower =
            totalPower / samples.size();

        // Find highest power reading
        auto highestPowerSample = max_element(
            samples.begin(),
            samples.end(),
            [this](const BatteryElectricalSample& first,
                   const BatteryElectricalSample& second)
            {
                return calculatePowerKW(first) <
                       calculatePowerKW(second);
            });

        // Count power anomalies
        int abnormalSamples = count_if(
            samples.begin(),
            samples.end(),
            [this](const BatteryElectricalSample& sample)
            {
                double power = calculatePowerKW(sample);

                return power < powerLimits.at("MIN_POWER_KW") ||
                       power > powerLimits.at("MAX_POWER_KW");
            });

        cout << "\n===== EV BATTERY POWER SENSOR MONITOR =====\n";

        for (const auto& sample : samples)
        {
            double powerKW = calculatePowerKW(sample);

            cout << "Sensor " << sample.sensorId
                 << " | Location: " << sample.location
                 << " | Voltage: "
                 << fixed << setprecision(1)
                 << sample.voltageVolt << " V"
                 << " | Current: "
                 << sample.currentAmpere << " A"
                 << " | Power: "
                 << powerKW << " kW";

            if (powerKW > powerLimits.at("MAX_POWER_KW"))
            {
                cout << " | HIGH POWER";
            }
            else if (powerKW <
                     powerLimits.at("MIN_POWER_KW"))
            {
                cout << " | LOW POWER";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        double highestPower =
            calculatePowerKW(*highestPowerSample);

        cout << "\nAverage Power     : "
             << averagePower << " kW";

        cout << "\nHighest Power     : Sensor "
             << highestPowerSample->sensorId
             << " (" << highestPower << " kW)";

        cout << "\nPower Anomalies   : "
             << abnormalSamples;

        if (highestPower >
            powerLimits.at("MAX_POWER_KW"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nPower Alert       : Excessive battery power detected";
            cout << "\nAction            : Reduce electrical load and inspect battery system.";
        }
        else if (abnormalSamples > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nPower Alert       : Abnormal battery power detected";
            cout << "\nAction            : Check voltage/current sensors and battery load.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nPower Alert       : Battery electrical output is within limits";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n============================================\n";
    }
};

int main()
{
    vector<BatteryElectricalSample> batterySamples{
        {1, "Front Battery Module", 360.0, 120.0},
        {2, "Center Battery Module", 365.0, 145.0},
        {3, "Rear Battery Module", 370.0, 230.0},
        {4, "Left Battery Module", 362.0, 130.0},
        {5, "Right Battery Module", 368.0, 125.0}
    };

    BatteryPowerMonitor powerMonitor(batterySamples);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &powerMonitor;

    sensorSystem->processData();

    return 0;
}