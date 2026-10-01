/**
 * @file ev_battery_cell_voltage_imbalance.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell voltage imbalance detection.
 * @date 30-09-2026
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Battery cell sensor
struct BatteryCell
{
    int cellId;
    double voltage;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class CellVoltageMonitor : public EVSensorSystem
{
private:
    vector<BatteryCell> cells;

    double imbalanceLimit = 0.05;

public:
    CellVoltageMonitor(const vector<BatteryCell>& cellData)
        : cells(cellData)
    {
    }

    void processData() override
    {
        if (cells.empty())
        {
            cout << "No battery cell data available.\n";
            return;
        }

        // Calculate average cell voltage
        double totalVoltage = accumulate(
            cells.begin(),
            cells.end(),
            0.0,
            [](double total, const BatteryCell& cell)
            {
                return total + cell.voltage;
            });

        double averageVoltage =
            totalVoltage / cells.size();

        // Find highest and lowest voltage cells
        auto highestCell = max_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& first,
               const BatteryCell& second)
            {
                return first.voltage < second.voltage;
            });

        auto lowestCell = min_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& first,
               const BatteryCell& second)
            {
                return first.voltage < second.voltage;
            });

        // Find imbalanced cells
        int imbalancedCells = count_if(
            cells.begin(),
            cells.end(),
            [this, averageVoltage](const BatteryCell& cell)
            {
                return abs(cell.voltage - averageVoltage) >
                       imbalanceLimit;
            });

        cout << "\n===== EV BATTERY CELL VOLTAGE MONITOR =====\n";

        for (const auto& cell : cells)
        {
            double difference =
                cell.voltage - averageVoltage;

            cout << "Cell " << cell.cellId
                 << " | Voltage: "
                 << fixed << setprecision(3)
                 << cell.voltage << " V"
                 << " | Difference: "
                 << difference << " V";

            if (abs(difference) > imbalanceLimit)
            {
                cout << " | IMBALANCED";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        double voltageDifference =
            highestCell->voltage -
            lowestCell->voltage;

        cout << "\nAverage Voltage   : "
             << averageVoltage << " V";

        cout << "\nHighest Cell      : Cell "
             << highestCell->cellId
             << " (" << highestCell->voltage << " V)";

        cout << "\nLowest Cell       : Cell "
             << lowestCell->cellId
             << " (" << lowestCell->voltage << " V)";

        cout << "\nVoltage Spread    : "
             << voltageDifference << " V";

        cout << "\nImbalanced Cells  : "
             << imbalancedCells;

        if (imbalancedCells > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nBattery Alert     : Cell voltage imbalance detected";
            cout << "\nAction            : Check cell condition and balancing system.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nBattery Alert     : Cell voltages are balanced";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n============================================\n";
    }
};

int main()
{
    vector<BatteryCell> batteryCells{
        {1, 3.72},
        {2, 3.74},
        {3, 3.71},
        {4, 3.73},
        {5, 3.60},
        {6, 3.75}
    };

    CellVoltageMonitor voltageMonitor(batteryCells);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &voltageMonitor;

    sensorSystem->processData();

    return 0;
}