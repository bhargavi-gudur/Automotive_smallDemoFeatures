/**
 * @file ev_battery_cell_sensor_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell temperature and voltage sensor fusion.
 * @date 01-10-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// Represents one battery cell
struct BatteryCell
{
    int cellId;
    double voltage;
    double temperature;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCellSensorFusion : public EVSensorSystem
{
private:
    vector<BatteryCell> cells;

    double voltageLimit = 0.05;
    double temperatureLimit = 45.0;

public:
    BatteryCellSensorFusion(
        const vector<BatteryCell>& cellData)
        : cells(cellData)
    {
    }

    void processData() override
    {
        if (cells.empty())
        {
            cout << "No battery cell sensor data available.\n";
            return;
        }

        // Calculate average voltage
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

        // Find hottest cell
        auto hottestCell = max_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& first,
               const BatteryCell& second)
            {
                return first.temperature <
                       second.temperature;
            });

        // Find lowest voltage cell
        auto lowestVoltageCell = min_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& first,
               const BatteryCell& second)
            {
                return first.voltage <
                       second.voltage;
            });

        // Count abnormal cells
        int abnormalCells = count_if(
            cells.begin(),
            cells.end(),
            [this, averageVoltage](const BatteryCell& cell)
            {
                bool voltageAbnormal =
                    abs(cell.voltage - averageVoltage) >
                    voltageLimit;

                bool temperatureAbnormal =
                    cell.temperature >
                    temperatureLimit;

                return voltageAbnormal ||
                       temperatureAbnormal;
            });

        cout << "\n===== EV BATTERY CELL SENSOR FUSION =====\n";

        for (const auto& cell : cells)
        {
            double voltageDifference =
                cell.voltage - averageVoltage;

            bool voltageAbnormal =
                abs(voltageDifference) > voltageLimit;

            bool temperatureAbnormal =
                cell.temperature > temperatureLimit;

            cout << "Cell " << cell.cellId
                 << " | Voltage: "
                 << fixed << setprecision(3)
                 << cell.voltage << " V"
                 << " | Temperature: "
                 << setprecision(1)
                 << cell.temperature << " °C";

            if (voltageAbnormal &&
                temperatureAbnormal)
            {
                cout << " | CRITICAL";
            }
            else if (voltageAbnormal ||
                     temperatureAbnormal)
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Voltage    : "
             << averageVoltage << " V";

        cout << "\nLowest Voltage     : Cell "
             << lowestVoltageCell->cellId
             << " (" << lowestVoltageCell->voltage
             << " V)";

        cout << "\nHottest Cell       : Cell "
             << hottestCell->cellId
             << " (" << hottestCell->temperature
             << " °C)";

        cout << "\nAbnormal Cells     : "
             << abnormalCells;

        if (hottestCell->temperature >
                temperatureLimit &&
            abs(hottestCell->voltage -
                averageVoltage) > voltageLimit)
        {
            cout << "\nSystem Status      : CRITICAL";
            cout << "\nBattery Alert      : Cell voltage and temperature anomaly";
            cout << "\nAction             : Reduce battery load and inspect cell.";
        }
        else if (abnormalCells > 0)
        {
            cout << "\nSystem Status      : WARNING";
            cout << "\nBattery Alert      : Abnormal cell sensor data detected";
            cout << "\nAction             : Check cell condition and BMS balancing.";
        }
        else
        {
            cout << "\nSystem Status      : NORMAL";
            cout << "\nBattery Alert      : Cell parameters are within limits";
            cout << "\nAction             : Continue monitoring.";
        }

        cout << "\n============================================\n";
    }
};

int main()
{
    vector<BatteryCell> batteryCells{
        {1, 3.72, 34.5},
        {2, 3.74, 36.2},
        {3, 3.71, 35.8},
        {4, 3.73, 37.1},
        {5, 3.58, 49.5},
        {6, 3.75, 36.8}
    };

    BatteryCellSensorFusion sensorFusion(batteryCells);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &sensorFusion;

    sensorSystem->processData();

    return 0;
}