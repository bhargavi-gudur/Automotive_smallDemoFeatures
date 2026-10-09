/**
 * @file ev_battery_cell_moving_average.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell anomaly detection using moving averages.
 * @date 10-10-2026
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

struct BatteryCell
{
    int cellId;
    vector<double> voltageHistory;
    vector<double> temperatureHistory;
};

class EVSensorSystem
{
protected:
    vector<BatteryCell> cells;

public:
    EVSensorSystem(const vector<BatteryCell>& data)
        : cells(data)
    {
    }

    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

class BatteryMovingAverageMonitor : public EVSensorSystem
{
private:
    const double voltageDeviationLimit = 0.05;
    const double temperatureDeviationLimit = 5.0;

    double calculateAverage(const vector<double>& values)
    {
        if (values.empty())
        {
            return 0.0;
        }

        double total = accumulate(
            values.begin(),
            values.end(),
            0.0
        );

        return total / values.size();
    }

public:
    BatteryMovingAverageMonitor(
        const vector<BatteryCell>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY MOVING AVERAGE MONITOR =====\n";

        if (cells.empty())
        {
            cout << "No battery cell data available.\n";
            return;
        }

        int abnormalCells = 0;

        for (const auto& cell : cells)
        {
            if (cell.voltageHistory.size() < 2 ||
                cell.temperatureHistory.size() < 2)
            {
                cout << "Cell " << cell.cellId
                     << " | Insufficient historical data\n";

                continue;
            }

            // Use all readings except the latest as the baseline.
            vector<double> previousVoltages(
                cell.voltageHistory.begin(),
                cell.voltageHistory.end() - 1
            );

            vector<double> previousTemperatures(
                cell.temperatureHistory.begin(),
                cell.temperatureHistory.end() - 1
            );

            double averageVoltage =
                calculateAverage(previousVoltages);

            double averageTemperature =
                calculateAverage(previousTemperatures);

            double currentVoltage =
                cell.voltageHistory.back();

            double currentTemperature =
                cell.temperatureHistory.back();

            double voltageDeviation =
                currentVoltage - averageVoltage;

            double temperatureDeviation =
                currentTemperature - averageTemperature;

            bool voltageAnomaly =
                abs(voltageDeviation) >
                voltageDeviationLimit;

            bool temperatureAnomaly =
                abs(temperatureDeviation) >
                temperatureDeviationLimit;

            string status;

            if (voltageAnomaly && temperatureAnomaly)
            {
                status = "CRITICAL";
            }
            else if (voltageAnomaly || temperatureAnomaly)
            {
                status = "WARNING";
            }
            else
            {
                status = "NORMAL";
            }

            if (status != "NORMAL")
            {
                abnormalCells++;
            }

            cout << fixed << setprecision(3);

            cout << "Cell " << cell.cellId
                 << " | Average Voltage: "
                 << averageVoltage << " V"
                 << " | Current Voltage: "
                 << currentVoltage << " V"
                 << " | Voltage Deviation: "
                 << voltageDeviation << " V"
                 << " | Average Temperature: "
                 << averageTemperature << " C"
                 << " | Current Temperature: "
                 << currentTemperature << " C"
                 << " | Temperature Deviation: "
                 << temperatureDeviation << " C"
                 << " | Status: " << status
                 << '\n';
        }

        cout << "\nAbnormal Cells: "
             << abnormalCells << '\n';

        if (abnormalCells > 0)
        {
            cout << "System Status : WARNING\n";
            cout << "Battery Alert : Moving-average anomaly detected\n";
            cout << "Action        : Verify sensor readings and inspect affected cells.\n";
        }
        else
        {
            cout << "System Status : NORMAL\n";
            cout << "Battery Alert : No anomalies detected by demo thresholds\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "==============================================\n";
    }
};

int main()
{
    vector<BatteryCell> batteryCells =
    {
        {
            1,
            {3.71, 3.72, 3.71, 3.72, 3.71},
            {34.0, 34.5, 35.0, 34.8, 35.0}
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
        },
        {
            4,
            {3.69, 3.70, 3.69, 3.70, 3.68},
            {35.0, 35.5, 35.8, 36.0, 36.2}
        }
    };

    BatteryMovingAverageMonitor monitor(batteryCells);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}