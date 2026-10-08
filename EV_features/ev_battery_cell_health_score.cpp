/**
 * @file ev_battery_cell_health_score.cpp
 * @author Gandla Bhargavi
 * @brief EV battery cell health scoring using voltage and temperature trends.
 * @date 08-10-2026
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

class BatteryCellHealthMonitor : public EVSensorSystem
{
private:
    const double voltageDropLimit = 0.05;
    const double temperatureRiseLimit = 5.0;
    const double highTemperatureLimit = 45.0;

public:
    BatteryCellHealthMonitor(
        const vector<BatteryCell>& data)
        : EVSensorSystem(data)
    {
    }

    void processData() override
    {
        cout << "\n===== EV BATTERY CELL HEALTH MONITOR =====\n";

        unordered_map<int, double> healthScores;

        int healthyCells = 0;
        int warningCells = 0;
        int criticalCells = 0;

        for (const auto& cell : cells)
        {
            double voltageDrop =
                cell.previousVoltage -
                cell.currentVoltage;

            double temperatureRise =
                cell.currentTemperature -
                cell.previousTemperature;

            double score = 100.0;

            // Voltage trend penalty
            if (voltageDrop > voltageDropLimit)
            {
                score -= 30.0;
            }

            // Temperature trend penalty
            if (temperatureRise > temperatureRiseLimit)
            {
                score -= 30.0;
            }

            // High absolute temperature penalty
            if (cell.currentTemperature >
                highTemperatureLimit)
            {
                score -= 20.0;
            }

            if (score < 0.0)
            {
                score = 0.0;
            }

            string status;

            if (score >= 80.0)
            {
                status = "HEALTHY";
                healthyCells++;
            }
            else if (score >= 50.0)
            {
                status = "WARNING";
                warningCells++;
            }
            else
            {
                status = "CRITICAL";
                criticalCells++;
            }

            healthScores[cell.cellId] = score;

            cout << "Cell " << cell.cellId
                 << " | Voltage Drop: "
                 << voltageDrop << " V"
                 << " | Temperature Rise: "
                 << temperatureRise << " C"
                 << " | Health Score: "
                 << score
                 << " | Status: "
                 << status
                 << '\n';
        }

        double totalScore = accumulate(
            healthScores.begin(),
            healthScores.end(),
            0.0,
            [](double sum,
               const pair<const int, double>& item)
            {
                return sum + item.second;
            }
        );

        double averageHealth =
            totalScore / healthScores.size();

        auto weakestCell = min_element(
            healthScores.begin(),
            healthScores.end(),
            [](const auto& a, const auto& b)
            {
                return a.second < b.second;
            }
        );

        auto strongestCell = max_element(
            healthScores.begin(),
            healthScores.end(),
            [](const auto& a, const auto& b)
            {
                return a.second < b.second;
            }
        );

        cout << "\nAverage Health Score : "
             << averageHealth << "%\n";

        cout << "Weakest Cell         : Cell "
             << weakestCell->first
             << " ("
             << weakestCell->second
             << "%)\n";

        cout << "Strongest Cell       : Cell "
             << strongestCell->first
             << " ("
             << strongestCell->second
             << "%)\n";

        cout << "Healthy Cells        : "
             << healthyCells << '\n';

        cout << "Warning Cells        : "
             << warningCells << '\n';

        cout << "Critical Cells       : "
             << criticalCells << '\n';

        if (criticalCells > 0)
        {
            cout << "\nSystem Status : CRITICAL\n";
            cout << "Battery Alert : Weak cell health detected\n";
            cout << "Action        : Inspect affected cell and reduce simulated battery stress.\n";
        }
        else if (warningCells > 0)
        {
            cout << "\nSystem Status : WARNING\n";
            cout << "Battery Alert : Cell health degradation detected\n";
            cout << "Action        : Continue monitoring cell trends.\n";
        }
        else
        {
            cout << "\nSystem Status : NORMAL\n";
            cout << "Battery Alert : Cell health is within demo limits\n";
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
        {2, 3.71, 3.63, 37.0, 43.0},
        {3, 3.68, 3.54, 43.0, 51.0},
        {4, 3.73, 3.72, 35.0, 36.0},
        {5, 3.70, 3.64, 39.0, 46.0},
        {6, 3.72, 3.70, 38.0, 40.0}
    };

    BatteryCellHealthMonitor monitor(batteryCells);

    EVSensorSystem* system = &monitor;

    system->processData();

    return 0;
}