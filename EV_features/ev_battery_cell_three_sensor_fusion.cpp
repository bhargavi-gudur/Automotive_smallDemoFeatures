/**
 * @file ev_battery_cell_three_sensor_fusion.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell voltage, current and temperature sensor fusion.
 * @date 06-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

struct BatteryCell
{
    int cellId;
    double voltageVolt;
    double currentAmpere;
    double temperatureCelsius;
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

class BatteryCellFaultMonitor : public EVSensorSystem
{
private:
    const double minimumVoltage = 3.40;
    const double maximumCurrent = 200.0;
    const double warningTemperature = 40.0;
    const double criticalTemperature = 50.0;

public:
    BatteryCellFaultMonitor(
        const vector<BatteryCell>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY CELL 3-SENSOR MONITOR =====\n";

        unordered_map<int, string> faultMap;

        int abnormalCells = 0;

        for (const auto& cell : cells)
        {
            bool lowVoltage =
                cell.voltageVolt < minimumVoltage;

            bool overcurrent =
                cell.currentAmpere > maximumCurrent;

            bool highTemperature =
                cell.temperatureCelsius >
                warningTemperature;

            bool criticalTemperature =
                cell.temperatureCelsius >
                criticalTemperature;

            string faultType;
            string status;

            if (criticalTemperature &&
                overcurrent &&
                lowVoltage)
            {
                faultType = "MULTIPLE FAULT";
                status = "CRITICAL";
            }
            else if (criticalTemperature &&
                     overcurrent)
            {
                faultType = "THERMAL + CURRENT";
                status = "CRITICAL";
            }
            else if (criticalTemperature &&
                     lowVoltage)
            {
                faultType = "THERMAL + VOLTAGE";
                status = "CRITICAL";
            }
            else if (overcurrent &&
                     lowVoltage)
            {
                faultType = "CURRENT + VOLTAGE";
                status = "WARNING";
            }
            else if (criticalTemperature)
            {
                faultType = "HIGH TEMPERATURE";
                status = "CRITICAL";
            }
            else if (overcurrent)
            {
                faultType = "OVERCURRENT";
                status = "WARNING";
            }
            else if (lowVoltage)
            {
                faultType = "LOW VOLTAGE";
                status = "WARNING";
            }
            else if (highTemperature)
            {
                faultType = "ELEVATED TEMPERATURE";
                status = "WARNING";
            }
            else
            {
                faultType = "NO FAULT";
                status = "NORMAL";
            }

            faultMap[cell.cellId] = faultType;

            if (status != "NORMAL")
            {
                abnormalCells++;
            }

            cout << "Cell " << cell.cellId
                 << " | Voltage: "
                 << cell.voltageVolt << " V"
                 << " | Current: "
                 << cell.currentAmpere << " A"
                 << " | Temperature: "
                 << cell.temperatureCelsius << " C"
                 << " | Fault: " << faultType
                 << " | Status: " << status
                 << '\n';
        }

        double totalVoltage = accumulate(
            cells.begin(),
            cells.end(),
            0.0,
            [](double sum, const BatteryCell& cell)
            {
                return sum + cell.voltageVolt;
            }
        );

        double averageVoltage =
            totalVoltage / cells.size();

        auto lowestVoltageCell = min_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& a,
               const BatteryCell& b)
            {
                return a.voltageVolt <
                       b.voltageVolt;
            }
        );

        auto highestCurrentCell = max_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& a,
               const BatteryCell& b)
            {
                return a.currentAmpere <
                       b.currentAmpere;
            }
        );

        auto hottestCell = max_element(
            cells.begin(),
            cells.end(),
            [](const BatteryCell& a,
               const BatteryCell& b)
            {
                return a.temperatureCelsius <
                       b.temperatureCelsius;
            }
        );

        int criticalCells = count_if(
            cells.begin(),
            cells.end(),
            [&](const BatteryCell& cell)
            {
                return cell.temperatureCelsius >
                       criticalTemperature;
            }
        );

        cout << "\nAverage Cell Voltage : "
             << averageVoltage << " V\n";

        cout << "Lowest Voltage Cell  : Cell "
             << lowestVoltageCell->cellId
             << " ("
             << lowestVoltageCell->voltageVolt
             << " V)\n";

        cout << "Highest Current Cell : Cell "
             << highestCurrentCell->cellId
             << " ("
             << highestCurrentCell->currentAmpere
             << " A)\n";

        cout << "Hottest Cell         : Cell "
             << hottestCell->cellId
             << " ("
             << hottestCell->temperatureCelsius
             << " C)\n";

        cout << "Critical Cells       : "
             << criticalCells << '\n';

        cout << "Abnormal Cells       : "
             << abnormalCells << '\n';

        if (criticalCells > 0)
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : Critical cell condition detected\n";
            cout << "Action        : Reduce simulated battery load and inspect affected cell.\n";
        }
        else if (abnormalCells > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Cell-level electrical or thermal anomaly detected\n";
            cout << "Action        : Continue monitoring affected cells.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : All cell parameters are within demo limits\n";
            cout << "Action        : Continue monitoring.\n";
        }

        cout << "===============================================\n";
    }
};

int main()
{
    vector<BatteryCell> batteryCells =
    {
        {1, 3.72, 120.0, 34.5},
        {2, 3.70, 145.0, 38.5},
        {3, 3.35, 230.0, 52.0},
        {4, 3.74, 130.0, 36.0},
        {5, 3.65, 210.0, 43.5},
        {6, 3.71, 150.0, 41.0}
    };

    BatteryCellFaultMonitor monitor(batteryCells);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}