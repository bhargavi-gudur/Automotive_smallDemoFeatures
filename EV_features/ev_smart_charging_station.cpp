/**
 * @file ev_battery_soh_estimation.cpp
 * @author Gandla Bhargavi
 * @brief EV Battery State of Health and Capacity Degradation Tracking using OOP and STL
 * @date 08-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Represents one battery capacity measurement.
 */
struct BatteryCycle
{
    int cycleNumber;
    double measuredCapacityAh;
};

/**
 * @brief Abstract base class for EV battery health estimation.
 */
class BatteryHealthSystem
{
public:
    virtual void processData() = 0;

    virtual ~BatteryHealthSystem() = default;
};

/**
 * @brief Estimates battery SoH and tracks capacity degradation.
 */
class EVBatterySoHMonitor : public BatteryHealthSystem
{
private:
    double originalCapacityAh;
    vector<BatteryCycle> cycleHistory;

    double currentSoH = 100.0;
    double degradationPercent = 0.0;

    /**
     * @brief Calculates current battery SoH.
     */
    double calculateSoH() const
    {
        if (cycleHistory.empty() || originalCapacityAh <= 0.0)
        {
            return 0.0;
        }

        const auto latestCycle = max_element(
            cycleHistory.begin(),
            cycleHistory.end(),
            [](const BatteryCycle& first,
               const BatteryCycle& second)
            {
                return first.cycleNumber < second.cycleNumber;
            });

        return (latestCycle->measuredCapacityAh /
                originalCapacityAh) * 100.0;
    }

    /**
     * @brief Calculates capacity degradation percentage.
     */
    double calculateDegradation() const
    {
        return 100.0 - currentSoH;
    }

    /**
     * @brief Calculates average measured capacity.
     */
    double calculateAverageCapacity() const
    {
        if (cycleHistory.empty())
        {
            return 0.0;
        }

        const double totalCapacity = accumulate(
            cycleHistory.begin(),
            cycleHistory.end(),
            0.0,
            [](double total, const BatteryCycle& cycle)
            {
                return total + cycle.measuredCapacityAh;
            });

        return totalCapacity / cycleHistory.size();
    }

    /**
     * @brief Finds cycles with significant capacity loss.
     */
    vector<BatteryCycle> findLowCapacityCycles() const
    {
        vector<BatteryCycle> lowCapacityCycles;

        copy_if(
            cycleHistory.begin(),
            cycleHistory.end(),
            back_inserter(lowCapacityCycles),
            [this](const BatteryCycle& cycle)
            {
                const double cycleSoH =
                    (cycle.measuredCapacityAh /
                     originalCapacityAh) * 100.0;

                return cycleSoH < 90.0;
            });

        return lowCapacityCycles;
    }

    /**
     * @brief Predicts battery health condition.
     */
    string determineHealthStatus() const
    {
        if (currentSoH >= 90.0)
        {
            return "HEALTHY";
        }

        if (currentSoH >= 80.0)
        {
            return "GOOD - DEGRADATION DETECTED";
        }

        if (currentSoH >= 70.0)
        {
            return "SERVICE REQUIRED";
        }

        return "CRITICAL BATTERY HEALTH";
    }

public:
    /**
     * @brief Constructor.
     */
    explicit EVBatterySoHMonitor(double originalCapacity)
        : originalCapacityAh(originalCapacity)
    {
    }

    /**
     * @brief Adds a battery cycle measurement.
     */
    void addCycle(const BatteryCycle& cycle)
    {
        if (cycle.cycleNumber > 0 &&
            cycle.measuredCapacityAh > 0.0)
        {
            cycleHistory.push_back(cycle);
        }
    }

    /**
     * @brief Processes battery health telemetry.
     */
    void processData() override
    {
        if (cycleHistory.empty())
        {
            cout << "No battery cycle data available.\n";
            return;
        }

        currentSoH = calculateSoH();
        degradationPercent = calculateDegradation();

        cout << "\n===== EV BATTERY SOH MONITOR =====\n";

        cout << fixed << setprecision(2);

        cout << "\nOriginal Battery Capacity: "
             << originalCapacityAh
             << " Ah";

        cout << "\n\nBattery Cycle History:\n";

        for (const auto& cycle : cycleHistory)
        {
            const double cycleSoH =
                (cycle.measuredCapacityAh /
                 originalCapacityAh) * 100.0;

            cout << "Cycle "
                 << cycle.cycleNumber
                 << " | Capacity: "
                 << cycle.measuredCapacityAh
                 << " Ah | SoH: "
                 << cycleSoH
                 << "%\n";
        }

        cout << "\nAverage Measured Capacity: "
             << calculateAverageCapacity()
             << " Ah";

        cout << "\nCurrent SoH: "
             << currentSoH
             << "%";

        cout << "\nCapacity Degradation: "
             << degradationPercent
             << "%";

        cout << "\nBattery Health: "
             << determineHealthStatus();

        const auto lowCapacityCycles =
            findLowCapacityCycles();

        cout << "\nCycles Below 90% SoH: "
             << lowCapacityCycles.size()
             << '\n';

        displayRecommendation();
    }

    /**
     * @brief Displays maintenance recommendation.
     */
    void displayRecommendation() const
    {
        cout << "\n\nRecommendation: ";

        if (currentSoH >= 90.0)
        {
            cout << "Battery capacity is healthy. Continue monitoring.";
        }
        else if (currentSoH >= 80.0)
        {
            cout << "Track degradation trend and monitor battery performance.";
        }
        else if (currentSoH >= 70.0)
        {
            cout << "Schedule battery inspection and service.";
        }
        else
        {
            cout << "Battery requires immediate diagnostic inspection.";
        }

        cout << '\n';
    }
};

int main()
{
    /*
     * Example:
     * New battery capacity = 150 Ah
     */
    EVBatterySoHMonitor battery(150.0);

    vector<BatteryCycle> history =
    {
        {100, 148.5},
        {200, 146.2},
        {300, 143.8},
        {400, 140.5},
        {500, 137.0},
        {600, 133.5}
    };

    for (const auto& cycle : history)
    {
        battery.addCycle(cycle);
    }

    BatteryHealthSystem* system = &battery;

    system->processData();

    return 0;
}