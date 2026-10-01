/**
 * @file ev_battery_temperature_imbalance.cpp
 * @author Gandla Bhargavi
 * @brief EV Battery Cell Temperature Imbalance Detection using OOP and STL
 * @date 06-09-2026
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Represents temperature data from one battery cell group.
 */
struct CellTemperature
{
    string cellGroup;
    double temperatureCelsius;
};

/**
 * @brief Abstract base class for battery monitoring systems.
 */
class BatteryMonitoringSystem
{
public:
    virtual void processData() = 0;

    virtual ~BatteryMonitoringSystem() = default;
};

/**
 * @brief Detects temperature imbalance between EV battery cell groups.
 */
class TemperatureImbalanceMonitor : public BatteryMonitoringSystem
{
private:
    vector<CellTemperature> cellTemperatures;

    double imbalanceLimit = 8.0;
    double averageTemperature = 0.0;
    double temperatureDifference = 0.0;

    /**
     * @brief Calculates average battery temperature.
     */
    double calculateAverageTemperature() const
    {
        if (cellTemperatures.empty())
        {
            return 0.0;
        }

        const double totalTemperature = accumulate(
            cellTemperatures.begin(),
            cellTemperatures.end(),
            0.0,
            [](double total, const CellTemperature& cell)
            {
                return total + cell.temperatureCelsius;
            });

        return totalTemperature / cellTemperatures.size();
    }

    /**
     * @brief Finds the hottest cell group.
     */
    const CellTemperature* findHottestCell() const
    {
        if (cellTemperatures.empty())
        {
            return nullptr;
        }

        const auto result = max_element(
            cellTemperatures.begin(),
            cellTemperatures.end(),
            [](const CellTemperature& first,
               const CellTemperature& second)
            {
                return first.temperatureCelsius <
                       second.temperatureCelsius;
            });

        return &(*result);
    }

    /**
     * @brief Finds the coolest cell group.
     */
    const CellTemperature* findCoolestCell() const
    {
        if (cellTemperatures.empty())
        {
            return nullptr;
        }

        const auto result = min_element(
            cellTemperatures.begin(),
            cellTemperatures.end(),
            [](const CellTemperature& first,
               const CellTemperature& second)
            {
                return first.temperatureCelsius <
                       second.temperatureCelsius;
            });

        return &(*result);
    }

    /**
     * @brief Calculates the temperature difference between hottest
     *        and coolest cell groups.
     */
    double calculateTemperatureDifference() const
    {
        const auto hottest = findHottestCell();
        const auto coolest = findCoolestCell();

        if (hottest == nullptr || coolest == nullptr)
        {
            return 0.0;
        }

        return hottest->temperatureCelsius -
               coolest->temperatureCelsius;
    }

    /**
     * @brief Finds all cell groups with abnormal temperature.
     */
    vector<CellTemperature> findAbnormalCells() const
    {
        vector<CellTemperature> abnormalCells;

        copy_if(
            cellTemperatures.begin(),
            cellTemperatures.end(),
            back_inserter(abnormalCells),
            [this](const CellTemperature& cell)
            {
                return abs(
                    cell.temperatureCelsius -
                    averageTemperature) > imbalanceLimit;
            });

        return abnormalCells;
    }

public:
    /**
     * @brief Adds a cell temperature reading.
     */
    void addCellTemperature(const CellTemperature& cell)
    {
        cellTemperatures.push_back(cell);
    }

    /**
     * @brief Processes battery temperature data.
     */
    void processData() override
    {
        if (cellTemperatures.empty())
        {
            cout << "No battery temperature data available.\n";
            return;
        }

        averageTemperature = calculateAverageTemperature();
        temperatureDifference = calculateTemperatureDifference();

        const auto hottest = findHottestCell();
        const auto coolest = findCoolestCell();

        cout << "\n===== EV BATTERY TEMPERATURE IMBALANCE =====\n";

        cout << fixed << setprecision(2);

        cout << "\nCell Group Temperatures:\n";

        for (const auto& cell : cellTemperatures)
        {
            cout << cell.cellGroup
                 << " : "
                 << cell.temperatureCelsius
                 << " C\n";
        }

        cout << "\nAverage Temperature: "
             << averageTemperature
             << " C";

        if (hottest != nullptr)
        {
            cout << "\nHottest Cell Group: "
                 << hottest->cellGroup
                 << " (" << hottest->temperatureCelsius
                 << " C)";
        }

        if (coolest != nullptr)
        {
            cout << "\nCoolest Cell Group: "
                 << coolest->cellGroup
                 << " (" << coolest->temperatureCelsius
                 << " C)";
        }

        cout << "\nTemperature Difference: "
             << temperatureDifference
             << " C";

        cout << "\nAllowed Imbalance: "
             << imbalanceLimit
             << " C";

        if (temperatureDifference > imbalanceLimit)
        {
            cout << "\nThermal Status: IMBALANCE DETECTED";
        }
        else
        {
            cout << "\nThermal Status: BALANCED";
        }

        const auto abnormalCells = findAbnormalCells();

        cout << "\n\nAbnormal Cell Groups: "
             << abnormalCells.size();

        for (const auto& cell : abnormalCells)
        {
            cout << "\n- " << cell.cellGroup
                 << " : "
                 << cell.temperatureCelsius
                 << " C";
        }

        cout << '\n';

        displayRecommendation();
    }

    /**
     * @brief Displays thermal management recommendation.
     */
    void displayRecommendation() const
    {
        cout << "\nThermal Management Recommendation: ";

        if (temperatureDifference > imbalanceLimit)
        {
            cout << "CHECK COOLING SYSTEM AND BATTERY CELL HEALTH.\n";
        }
        else
        {
            cout << "TEMPERATURE DISTRIBUTION IS NORMAL.\n";
        }
    }
};

int main()
{
    TemperatureImbalanceMonitor monitor;

    vector<CellTemperature> batteryData =
    {
        {"CellGroup_A", 32.5},
        {"CellGroup_B", 34.1},
        {"CellGroup_C", 35.8},
        {"CellGroup_D", 36.2},
        {"CellGroup_E", 43.9},
        {"CellGroup_F", 45.7},
        {"CellGroup_G", 34.8},
        {"CellGroup_H", 33.6}
    };

    for (const auto& cell : batteryData)
    {
        monitor.addCellTemperature(cell);
    }

    BatteryMonitoringSystem* system = &monitor;

    system->processData();

    return 0;
}