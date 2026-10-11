/**
 * @file ev_battery_median_filter.cpp
 * @author Gandla Bhargavi
 * @brief EV battery voltage and temperature spike detection using a median filter.
 * @date 12-10-2026
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>

using namespace std;

struct BatterySensor
{
    int sensorId;
    vector<double> voltageReadings;
    vector<double> temperatureReadings;
};

class EVSensorSystem
{
protected:
    vector<BatterySensor> sensors;

public:
    EVSensorSystem(const vector<BatterySensor>& data)
        : sensors(data)
    {
    }

    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

class BatteryMedianFilter : public EVSensorSystem
{
private:
    const double voltageSpikeLimit = 0.05;
    const double temperatureSpikeLimit = 3.0;

    double calculateMedian(vector<double> readings)
    {
        if (readings.empty())
        {
            return 0.0;
        }

        sort(readings.begin(), readings.end());

        size_t middle = readings.size() / 2;

        if (readings.size() % 2 == 0)
        {
            return (
                readings[middle - 1] +
                readings[middle]
            ) / 2.0;
        }

        return readings[middle];
    }

public:
    BatteryMedianFilter(const vector<BatterySensor>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY MEDIAN FILTER =====\n";

        if (sensors.empty())
        {
            cout << "No sensor data available.\n";
            return;
        }

        int abnormalSensors = 0;

        for (const auto& sensor : sensors)
        {
            if (sensor.voltageReadings.empty() ||
                sensor.temperatureReadings.empty())
            {
                cout << "Sensor " << sensor.sensorId
                     << " | Insufficient data\n";
                continue;
            }

            double rawVoltage =
                sensor.voltageReadings.back();

            double rawTemperature =
                sensor.temperatureReadings.back();

            double medianVoltage =
                calculateMedian(sensor.voltageReadings);

            double medianTemperature =
                calculateMedian(sensor.temperatureReadings);

            double voltageDeviation =
                abs(rawVoltage - medianVoltage);

            double temperatureDeviation =
                abs(rawTemperature - medianTemperature);

            bool voltageSpike =
                voltageDeviation > voltageSpikeLimit;

            bool temperatureSpike =
                temperatureDeviation > temperatureSpikeLimit;

            string status;

            if (voltageSpike && temperatureSpike)
            {
                status = "CHECK BOTH SENSORS";
            }
            else if (voltageSpike)
            {
                status = "CHECK VOLTAGE";
            }
            else if (temperatureSpike)
            {
                status = "CHECK TEMPERATURE";
            }
            else
            {
                status = "NORMAL";
            }

            if (voltageSpike || temperatureSpike)
            {
                abnormalSensors++;
            }

            cout << fixed << setprecision(3);

            cout << "Sensor " << sensor.sensorId
                 << " | Raw Voltage: "
                 << rawVoltage << " V"
                 << " | Median Voltage: "
                 << medianVoltage << " V"
                 << " | Raw Temperature: "
                 << rawTemperature << " C"
                 << " | Median Temperature: "
                 << medianTemperature << " C"
                 << " | Status: " << status
                 << '\n';
        }

        cout << "\nSensors Requiring Review: "
             << abnormalSensors << '\n';

        if (abnormalSensors > 0)
        {
            cout << "System Status : SENSOR REVIEW REQUIRED\n";
            cout << "Action        : Verify abnormal readings against sensor diagnostics.\n";
        }
        else
        {
            cout << "System Status : NORMAL\n";
            cout << "Action        : Continue monitoring sensor readings.\n";
        }

        cout << "====================================\n";
    }
};

int main()
{
    vector<BatterySensor> sensorData =
    {
        {
            1,
            {3.71, 3.72, 3.71, 3.72, 3.71},
            {34.0, 34.2, 34.1, 34.3, 34.2}
        },
        {
            2,
            {3.70, 3.71, 3.70, 3.71, 3.95},
            {36.0, 36.2, 36.5, 36.4, 36.3}
        },
        {
            3,
            {3.72, 3.71, 3.73, 3.72, 3.71},
            {38.0, 38.2, 38.4, 38.3, 48.0}
        }
    };

    BatteryMedianFilter filter(sensorData);

    EVSensorSystem* system = &filter;

    system->processData();

    return 0;
}