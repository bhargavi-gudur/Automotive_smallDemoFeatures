/**
 * @file ev_battery_voltage_temperature_derating.cpp
 * @author Gandla Bhargavi
 * @brief EV battery voltage and temperature sensor fusion for thermal derating detection.
 * @date 05-10-2026
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
    double temperatureCelsius;
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

class BatteryThermalDeratingMonitor : public EVSensorSystem
{
private:
    const double warningTemperature = 40.0;
    const double criticalTemperature = 50.0;

    const double minimumVoltage = 340.0;

public:
    BatteryThermalDeratingMonitor(
        const vector<BatterySample>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY THERMAL DERATING MONITOR =====\n";

        unordered_map<int, string> statusMap;
        unordered_map<int, int> deratingMap;

        int abnormalCount = 0;

        for (const auto& sample : samples)
        {
            bool lowVoltage =
                sample.voltageVolt < minimumVoltage;

            bool highTemperature =
                sample.temperatureCelsius >
                warningTemperature;

            bool criticalTemperature =
                sample.temperatureCelsius >
                criticalTemperature;

            string status;
            int deratingPercent;

            if (criticalTemperature && lowVoltage)
            {
                status = "CRITICAL";
                deratingPercent = 50;
            }
            else if (criticalTemperature)
            {
                status = "CRITICAL";
                deratingPercent = 40;
            }
            else if (highTemperature && lowVoltage)
            {
                status = "WARNING";
                deratingPercent = 30;
            }
            else if (highTemperature)
            {
                status = "WARNING";
                deratingPercent = 20;
            }
            else
            {
                status = "NORMAL";
                deratingPercent = 0;
            }

            statusMap[sample.sensorId] = status;
            deratingMap[sample.sensorId] = deratingPercent;

            if (status != "NORMAL")
            {
                abnormalCount++;
            }

            cout << "Sensor " << sample.sensorId
                 << " | Location: " << sample.location
                 << " | Voltage: "
                 << sample.voltageVolt << " V"
                 << " | Temperature: "
                 << sample.temperatureCelsius << " C"
                 << " | Status: " << status
                 << " | Derating: "
                 << deratingPercent << "%"
                 << '\n';
        }

        double totalTemperature = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double sum, const BatterySample& sample)
            {
                return sum + sample.temperatureCelsius;
            }
        );

        double averageTemperature =
            totalTemperature / samples.size();

        auto hottestSensor = max_element(
            samples.begin(),
            samples.end(),
            [](const BatterySample& a,
               const BatterySample& b)
            {
                return a.temperatureCelsius <
                       b.temperatureCelsius;
            }
        );

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

        int thermalWarningCount = count_if(
            samples.begin(),
            samples.end(),
            [&](const BatterySample& sample)
            {
                return sample.temperatureCelsius >
                       warningTemperature;
            }
        );

        cout << "\nAverage Temperature : "
             << averageTemperature << " C\n";

        cout << "Hottest Sensor      : Sensor "
             << hottestSensor->sensorId
             << " ("
             << hottestSensor->temperatureCelsius
             << " C)\n";

        cout << "Lowest Voltage      : Sensor "
             << lowestVoltage->sensorId
             << " ("
             << lowestVoltage->voltageVolt
             << " V)\n";

        cout << "Thermal Warnings    : "
             << thermalWarningCount << '\n';

        cout << "Abnormal Sensors    : "
             << abnormalCount << '\n';

        int hottestDerating =
            deratingMap[hottestSensor->sensorId];

        if (hottestDerating >= 40)
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : High battery temperature detected\n";
            cout << "Thermal Action: Apply "
                 << hottestDerating
                 << "% simulated power derating\n";
            cout << "Action        : Reduce simulated battery load and inspect cooling system.\n";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Thermal condition requires attention\n";
            cout << "Thermal Action: Apply "
                 << hottestDerating
                 << "% simulated power derating\n";
            cout << "Action        : Continue monitoring battery temperature.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Battery temperature is within demo limits\n";
            cout << "Thermal Action: No derating required\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "================================================\n";
    }
};

int main()
{
    vector<BatterySample> batteryData =
    {
        {1, "Battery Pack A", 360.0, 34.5},
        {2, "Battery Pack B", 355.0, 41.5},
        {3, "Battery Pack C", 335.0, 52.0},
        {4, "Battery Pack D", 362.0, 37.0},
        {5, "Battery Pack E", 345.0, 44.0}
    };

    BatteryThermalDeratingMonitor monitor(batteryData);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}