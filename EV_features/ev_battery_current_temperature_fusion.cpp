/**
 * @file ev_battery_current_temperature_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery current and temperature sensor fusion for overload detection.
 * @date 02-10-2026
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
    double currentAmpere;
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

class BatteryCurrentTemperatureMonitor : public EVSensorSystem
{
private:
    const double maxCurrent = 200.0;
    const double maxTemperature = 45.0;

public:
    BatteryCurrentTemperatureMonitor(
        const vector<BatterySample>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY CURRENT + TEMPERATURE MONITOR =====\n";

        unordered_map<int, string> statusMap;

        int abnormalCount = 0;

        for (const auto& sample : samples)
        {
            bool currentHigh =
                sample.currentAmpere > maxCurrent;

            bool temperatureHigh =
                sample.temperatureCelsius > maxTemperature;

            string status;

            if (currentHigh && temperatureHigh)
            {
                status = "CRITICAL";
            }
            else if (currentHigh || temperatureHigh)
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
                 << " | Current: "
                 << sample.currentAmpere << " A"
                 << " | Temperature: "
                 << sample.temperatureCelsius << " C"
                 << " | Status: " << status << '\n';
        }

        double totalCurrent = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double sum, const BatterySample& sample)
            {
                return sum + sample.currentAmpere;
            }
        );

        double averageCurrent =
            totalCurrent / samples.size();

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

        int overloadCount = count_if(
            samples.begin(),
            samples.end(),
            [&](const BatterySample& sample)
            {
                return sample.currentAmpere >
                       maxCurrent;
            }
        );

        cout << "\nAverage Current : "
             << averageCurrent << " A\n";

        cout << "Highest Current : Sensor "
             << highestCurrent->sensorId
             << " (" << highestCurrent->currentAmpere
             << " A)\n";

        cout << "Hottest Sensor  : Sensor "
             << hottestSensor->sensorId
             << " (" << hottestSensor->temperatureCelsius
             << " C)\n";

        cout << "Current Overloads : "
             << overloadCount << '\n';

        cout << "Abnormal Sensors  : "
             << abnormalCount << '\n';

        if (statusMap[highestCurrent->sensorId] == "CRITICAL")
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : Current and temperature overload detected\n";
            cout << "Action        : Reduce simulated battery load and inspect the affected area.\n";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Abnormal current or temperature detected\n";
            cout << "Action        : Continue monitoring and inspect the affected sensor.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Battery parameters are within demo limits\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "====================================================\n";
    }
};

int main()
{
    vector<BatterySample> batteryData =
    {
        {1, "Battery Pack A", 145.0, 34.5},
        {2, "Battery Pack B", 175.0, 39.2},
        {3, "Battery Pack C", 230.0, 48.5},
        {4, "Battery Pack D", 160.0, 37.8},
        {5, "Battery Pack E", 190.0, 44.0}
    };

    BatteryCurrentTemperatureMonitor monitor(batteryData);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}