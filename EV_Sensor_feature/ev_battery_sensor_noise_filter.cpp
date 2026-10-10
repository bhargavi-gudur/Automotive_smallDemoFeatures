/**
 * @file ev_battery_sensor_noise_filter.cpp
 * @author Gandla Bhargavi
 * @brief EV battery voltage and temperature noise filtering.
 * @date 11-10-2026
 */

#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>

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

class BatteryNoiseFilter : public EVSensorSystem
{
private:
    static constexpr size_t WINDOW_SIZE = 3;

    const double voltageDeviationLimit = 0.05;
    const double temperatureDeviationLimit = 3.0;

    double movingAverage(
        const vector<double>& readings,
        size_t endIndex)
    {
        if (readings.empty())
        {
            return 0.0;
        }

        size_t startIndex =
            (endIndex >= WINDOW_SIZE - 1)
                ? endIndex - WINDOW_SIZE + 1
                : 0;

        vector<double> window(
            readings.begin() + startIndex,
            readings.begin() + endIndex + 1
        );

        double total = accumulate(
            window.begin(),
            window.end(),
            0.0
        );

        return total / window.size();
    }

public:
    BatteryNoiseFilter(const vector<BatterySensor>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY SENSOR NOISE FILTER =====\n";

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
                     << " | Insufficient sensor data\n";
                continue;
            }

            double rawVoltage =
                sensor.voltageReadings.back();

            double rawTemperature =
                sensor.temperatureReadings.back();

            size_t voltageEnd =
                sensor.voltageReadings.size() - 1;

            size_t temperatureEnd =
                sensor.temperatureReadings.size() - 1;

            double filteredVoltage =
                movingAverage(
                    sensor.voltageReadings,
                    voltageEnd
                );

            double filteredTemperature =
                movingAverage(
                    sensor.temperatureReadings,
                    temperatureEnd
                );

            double voltageDifference =
                rawVoltage - filteredVoltage;

            double temperatureDifference =
                rawTemperature - filteredTemperature;

            bool voltageNoise =
                abs(voltageDifference) >
                voltageDeviationLimit;

            bool temperatureNoise =
                abs(temperatureDifference) >
                temperatureDeviationLimit;

            string status;

            if (voltageNoise && temperatureNoise)
            {
                status = "CHECK BOTH SENSORS";
            }
            else if (voltageNoise)
            {
                status = "CHECK VOLTAGE";
            }
            else if (temperatureNoise)
            {
                status = "CHECK TEMPERATURE";
            }
            else
            {
                status = "STABLE";
            }

            if (voltageNoise || temperatureNoise)
            {
                abnormalSensors++;
            }

            cout << fixed << setprecision(3);

            cout << "Sensor " << sensor.sensorId
                 << " | Raw Voltage: "
                 << rawVoltage << " V"
                 << " | Filtered Voltage: "
                 << filteredVoltage << " V"
                 << " | Raw Temperature: "
                 << rawTemperature << " C"
                 << " | Filtered Temperature: "
                 << filteredTemperature << " C"
                 << " | Status: " << status
                 << '\n';
        }

        cout << "\nSensors Requiring Review: "
             << abnormalSensors << '\n';

        if (abnormalSensors > 0)
        {
            cout << "System Status : SENSOR REVIEW REQUIRED\n";
            cout << "Action        : Verify unusual readings against sensor diagnostics.\n";
        }
        else
        {
            cout << "System Status : STABLE\n";
            cout << "Action        : Continue monitoring filtered readings.\n";
        }

        cout << "===========================================\n";
    }
};

int main()
{
    vector<BatterySensor> sensorData =
    {
        {
            1,
            {3.71, 3.72, 3.71, 3.72, 3.71},
            {34.0, 34.5, 34.2, 34.4, 34.3}
        },
        {
            2,
            {3.70, 3.71, 3.70, 3.71, 3.50},
            {36.0, 36.5, 37.0, 37.5, 46.0}
        },
        {
            3,
            {3.72, 3.71, 3.73, 3.72, 3.71},
            {38.0, 38.5, 39.0, 39.2, 39.5}
        }
    };

    BatteryNoiseFilter filter(sensorData);

    EVSensorSystem* system = &filter;

    system->processData();

    return 0;
}