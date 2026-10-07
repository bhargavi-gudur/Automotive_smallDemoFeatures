/**
 * @file ev_battery_cell_trend_analysis.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell voltage and temperature trend analysis.
 * @date 07-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

struct BatteryCell
{
    int cellId;
    double previousVoltage;
    double currentVoltage;
    double previousTemperature;
    double currentTemperature;
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

class BatteryCellTrendMonitor : public EVSensorSystem
{
private:
    const double voltageDropLimit = 0.05;
    const double temperatureRiseLimit = 5.0;
    const double criticalTemperature = 50.0;

public:
    BatteryCellTrendMonitor(
        const vector<BatteryCell>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY CELL TREND MONITOR =====\n";

        unordered_map<int, string> statusMap;

        int abnormalCells = 0;

        for (const auto& cell : cells)
        {
            double voltageChange =
                cell.currentVoltage -
                cell.previousVoltage;

            double temperatureChange =
                cell.currentTemperature -
                cell.previousTemperature;

            bool voltageDropping =
                voltageChange < -voltageDropLimit;

            bool temperatureRising =
                temperatureChange > temperatureRiseLimit;

            bool criticalTemperature =
                cell.currentTemperature >
                criticalTemperature;

            string status;

            if (
                criticalTemperature &&
                voltageDropping &&
                temperatureRising
            )
            {
                status = "CRITICAL";
            }
            else if (
                voltageDropping &&
                temperatureRising
            )
            {
                status = "WARNING";
            }
            else if (
                voltageDropping ||
                temperatureRising ||
                criticalTemperature
            )
            {
                status = "WARNING";
            }
            else
            {
                status = "NORMAL";
            }

            statusMap[cell.cellId] = status;

            if (status != "NORMAL")
            {
                abnormalCells++;
            }

            cout << "Cell " << cell.cellId
                 << " | Voltage Change: "
                 << voltageChange << " V"
                 << " | Temperature Change: "
                 << temperatureChange << " C"
                 << " | Current Voltage: "
                 << cell.currentVoltage << " V"
                 << " | Current Temperature: "
                 << cell.currentTemperature << " C"
                 << " | Status: " << status
                 << '\n';
        }

        double totalVoltageChange = accumulate(
            cells.begin(),
            cells.end(),
            0.0,
            [](double sum, const BatteryCell& cell)
            {
                return sum +
                       (cell.currentVoltage -
                        cell.previousVoltage);
            }
        );

        double averageVoltageChange =
            totalVoltageChange / cells.size();

        auto largestVoltageDrop = min_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& a,
               const BatteryCell& b)
            {
                double changeA =
                    a.currentVoltage -
                    a.previousVoltage;

                double changeB =
                    b.currentVoltage -
                    b.previousVoltage;

                return changeA < changeB;
            }
        );

        auto highestTemperatureRise = max_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& a,
               const BatteryCell& b)
            {
                double changeA =
                    a.currentTemperature -
                    a.previousTemperature;

                double changeB =
                    b.currentTemperature -
                    b.previousTemperature;

                return changeA < changeB;
            }
        );

        int voltageDropCount = count_if(
            cells.begin(),
            cells.end(),
            [&](const BatteryCell& cell)
            {
                return
                    (cell.currentVoltage -
                     cell.previousVoltage)
                    < -voltageDropLimit;
            }
        );

        int temperatureRiseCount = count_if(
            cells.begin(),
            cells.end(),
            [&](const BatteryCell& cell)
            {
                return
                    (cell.currentTemperature -
                     cell.previousTemperature)
                    > temperatureRiseLimit;
            }
        );

        cout << "\nAverage Voltage Change : "
             << averageVoltageChange << " V\n";

        cout << "Largest Voltage Drop  : Cell "
             << largestVoltageDrop->cellId
             << " ("
             << largestVoltageDrop->currentVoltage -
                largestVoltageDrop->previousVoltage
             << " V)\n";

        cout << "Largest Temperature Rise : Cell "
             << highestTemperatureRise->cellId
             << " ("
             << highestTemperatureRise->currentTemperature -
                highestTemperatureRise->previousTemperature
             << " C)\n";

        cout << "Voltage Drop Cells       : "
             << voltageDropCount << '\n';

        cout << "Temperature Rise Cells   : "
             << temperatureRiseCount << '\n';

        cout << "Abnormal Cells           : "
             << abnormalCells << '\n';

        if (
            statusMap[largestVoltageDrop->cellId] ==
                "CRITICAL" ||
            statusMap[highestTemperatureRise->cellId] ==
                "CRITICAL"
        )
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : Rapid cell parameter deterioration detected\n";
            cout << "Action        : Reduce simulated battery load and inspect affected cell.\n";
        }
        else if (abnormalCells > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Cell voltage or temperature trend anomaly detected\n";
            cout << "Action        : Continue monitoring cell trends.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Cell trends are within demo limits\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "===========================================\n";
    }
};

int main()
{
    vector<BatteryCell> batteryCells =
    {
        {1, 3.72, 3.71, 34.0, 35.0},
        {2, 3.71, 3.68, 37.0, 40.0},
        {3, 3.68, 3.57, 43.0, 50.5},
        {4, 3.73, 3.72, 35.0, 36.0},
        {5, 3.70, 3.64, 39.0, 45.5},
        {6, 3.72, 3.71, 38.0, 39.0}
    };

    BatteryCellTrendMonitor monitor(batteryCells);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}