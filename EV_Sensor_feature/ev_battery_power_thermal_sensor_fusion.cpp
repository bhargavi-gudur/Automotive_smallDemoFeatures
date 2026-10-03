/**
 * @file ev_battery_power_thermal_sensor_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery voltage, current and temperature sensor fusion.
 * @date 03-10-2026
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

class BatteryPowerThermalMonitor : public EVSensorSystem
{
private:
    const double maxPowerKW = 80.0;
    const double maxTemperature = 45.0;

public:
    BatteryPowerThermalMonitor(
        const vector<BatterySample>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY POWER + THERMAL MONITOR =====\n";

        unordered_map<int, string> statusMap;

        int abnormalCount = 0;

        for (const auto& sample : samples)
        {
            double powerKW =
                (sample.voltageVolt *
                 sample.currentAmpere) / 1000.0;

            bool powerHigh =
                powerKW > maxPowerKW;

            bool temperatureHigh =
                sample.temperatureCelsius > maxTemperature;

            string status;

            if (powerHigh && temperatureHigh)
            {
                status = "CRITICAL";
            }
            else if (powerHigh || temperatureHigh)
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
                 << " | Voltage: " << sample.voltageVolt << " V"
                 << " | Current: " << sample.currentAmpere << " A"
                 << " | Power: " << powerKW << " kW"
                 << " | Temperature: "
                 << sample.temperatureCelsius << " C"
                 << " | Status: " << status << '\n';
        }

        double totalPower = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double sum, const BatterySample& sample)
            {
                return sum +
                       (sample.voltageVolt *
                        sample.currentAmpere) / 1000.0;
            }
        );

        double averagePower =
            totalPower / samples.size();

        auto highestPower = max_element(
            samples.begin(),
            samples.end(),
            [](const BatterySample& a,
               const BatterySample& b)
            {
                double powerA =
                    a.voltageVolt * a.currentAmpere;

                double powerB =
                    b.voltageVolt * b.currentAmpere;

                return powerA < powerB;
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

        int powerAnomalyCount = count_if(
            samples.begin(),
            samples.end(),
            [&](const BatterySample& sample)
            {
                double powerKW =
                    (sample.voltageVolt *
                     sample.currentAmpere) / 1000.0;

                return powerKW > maxPowerKW;
            }
        );

        cout << "\nAverage Power : "
             << averagePower << " kW\n";

        cout << "Highest Power : Sensor "
             << highestPower->sensorId
             << " ("
             << (highestPower->voltageVolt *
                 highestPower->currentAmpere) / 1000.0
             << " kW)\n";

        cout << "Hottest Sensor: Sensor "
             << hottestSensor->sensorId
             << " ("
             << hottestSensor->temperatureCelsius
             << " C)\n";

        cout << "Power Anomalies: "
             << powerAnomalyCount << '\n';

        cout << "Abnormal Sensors: "
             << abnormalCount << '\n';

        if (
            statusMap[highestPower->sensorId] == "CRITICAL"
        )
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : High power and thermal anomaly detected\n";
            cout << "Action        : Reduce simulated battery load and inspect the affected sensor.\n";
        }
        else if (abnormalCount > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Electrical or thermal anomaly detected\n";
            cout << "Action        : Continue monitoring battery parameters.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Battery parameters are within demo limits\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "=================================================\n";
    }
};

int main()
{
    vector<BatterySample> batteryData =
    {
        {1, "Battery Pack A", 360.0, 120.0, 34.5},
        {2, "Battery Pack B", 365.0, 145.0, 38.0},
        {3, "Battery Pack C", 370.0, 230.0, 49.0},
        {4, "Battery Pack D", 362.0, 130.0, 36.5},
        {5, "Battery Pack E", 368.0, 150.0, 42.0}
    };

    BatteryPowerThermalMonitor monitor(batteryData);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}