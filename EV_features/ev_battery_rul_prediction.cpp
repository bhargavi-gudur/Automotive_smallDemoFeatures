/**
 * @file ev_battery_rul_prediction.cpp
 * @author Gandla Bhargavi
 * @brief EV Battery Remaining Useful Life Prediction using OOP and STL
 * @date 09-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Stores battery health information for one cycle.
 */
struct BatteryHealthData
{
    int cycleNumber;
    double sohPercent;
};

/**
 * @brief Abstract base class for battery health prediction.
 */
class BatteryPredictionSystem
{
public:
    virtual void processData() = 0;

    virtual ~BatteryPredictionSystem() = default;
};

/**
 * @brief Predicts remaining useful life of an EV battery.
 */
class EVBatteryRULPredictor : public BatteryPredictionSystem
{
private:
    vector<BatteryHealthData> healthHistory;

    map<string, double> healthLimits =
    {
        {"Healthy", 90.0},
        {"Warning", 80.0},
        {"EndOfLife", 80.0}
    };

    double averageDegradationPerCycle = 0.0;
    double predictedRUL = 0.0;

    /**
     * @brief Calculates degradation between consecutive measurements.
     */
    double calculateAverageDegradation() const
    {
        if (healthHistory.size() < 2)
        {
            return 0.0;
        }

        vector<double> degradationRates;

        for (size_t i = 1; i < healthHistory.size(); ++i)
        {
            const int cycleDifference =
                healthHistory[i].cycleNumber -
                healthHistory[i - 1].cycleNumber;

            const double sohDifference =
                healthHistory[i - 1].sohPercent -
                healthHistory[i].sohPercent;

            if (cycleDifference > 0)
            {
                const double degradationPerCycle =
                    sohDifference / cycleDifference;

                degradationRates.push_back(
                    degradationPerCycle);
            }
        }

        if (degradationRates.empty())
        {
            return 0.0;
        }

        return accumulate(
            degradationRates.begin(),
            degradationRates.end(),
            0.0) / degradationRates.size();
    }

    /**
     * @brief Finds the latest battery health measurement.
     */
    const BatteryHealthData* getLatestData() const
    {
        if (healthHistory.empty())
        {
            return nullptr;
        }

        return &(*max_element(
            healthHistory.begin(),
            healthHistory.end(),
            [](const BatteryHealthData& first,
               const BatteryHealthData& second)
            {
                return first.cycleNumber <
                       second.cycleNumber;
            }));
    }

    /**
     * @brief Predicts remaining cycles before reaching EOL.
     */
    double calculateRUL() const
    {
        const auto latest = getLatestData();

        if (latest == nullptr ||
            averageDegradationPerCycle <= 0.0)
        {
            return 0.0;
        }

        const double currentSoH = latest->sohPercent;
        const double endOfLifeSoH =
            healthLimits.at("EndOfLife");

        if (currentSoH <= endOfLifeSoH)
        {
            return 0.0;
        }

        return (currentSoH - endOfLifeSoH) /
               averageDegradationPerCycle;
    }

    /**
     * @brief Predicts the approximate cycle at battery EOL.
     */
    int predictEndOfLifeCycle() const
    {
        const auto latest = getLatestData();

        if (latest == nullptr)
        {
            return 0;
        }

        return latest->cycleNumber +
               static_cast<int>(predictedRUL);
    }

    /**
     * @brief Determines battery health condition.
     */
    string getHealthStatus(double soh) const
    {
        if (soh >= healthLimits.at("Healthy"))
        {
            return "HEALTHY";
        }

        if (soh >= healthLimits.at("Warning"))
        {
            return "DEGRADING";
        }

        return "SERVICE REQUIRED";
    }

public:
    /**
     * @brief Adds battery health data.
     */
    void addHealthData(const BatteryHealthData& data)
    {
        if (data.cycleNumber > 0 &&
            data.sohPercent >= 0.0 &&
            data.sohPercent <= 100.0)
        {
            healthHistory.push_back(data);
        }
    }

    /**
     * @brief Processes battery degradation data.
     */
    void processData() override
    {
        if (healthHistory.size() < 2)
        {
            cout << "At least two health measurements are required.\n";
            return;
        }

        // Keep the history ordered by cycle number.
        sort(
            healthHistory.begin(),
            healthHistory.end(),
            [](const BatteryHealthData& first,
               const BatteryHealthData& second)
            {
                return first.cycleNumber <
                       second.cycleNumber;
            });

        averageDegradationPerCycle =
            calculateAverageDegradation();

        predictedRUL = calculateRUL();

        const auto latest = getLatestData();

        cout << "\n===== EV BATTERY RUL PREDICTION =====\n";

        cout << fixed << setprecision(3);

        cout << "\nBattery Health History:\n";

        for (const auto& data : healthHistory)
        {
            cout << "Cycle "
                 << setw(4)
                 << data.cycleNumber
                 << " | SoH: "
                 << data.sohPercent
                 << "% | Status: "
                 << getHealthStatus(data.sohPercent)
                 << '\n';
        }

        if (latest != nullptr)
        {
            cout << "\nLatest Cycle: "
                 << latest->cycleNumber;

            cout << "\nCurrent SoH: "
                 << latest->sohPercent
                 << "%";
        }

        cout << "\nAverage Degradation: "
             << averageDegradationPerCycle
             << "% per cycle";

        cout << "\nEnd-of-Life Threshold: "
             << healthLimits.at("EndOfLife")
             << "%";

        cout << "\nPredicted Remaining Useful Life: "
             << predictedRUL
             << " cycles";

        cout << "\nPredicted EOL Cycle: "
             << predictEndOfLifeCycle();

        cout << '\n';

        displayRecommendation();
    }

    /**
     * @brief Displays maintenance recommendation.
     */
    void displayRecommendation() const
    {
        if (predictedRUL <= 0.0)
        {
            cout << "\nRecommendation: "
                 << "Battery has reached the configured EOL threshold.\n";
        }
        else if (predictedRUL < 100.0)
        {
            cout << "\nRecommendation: "
                 << "Schedule battery health inspection.\n";
        }
        else if (predictedRUL < 300.0)
        {
            cout << "\nRecommendation: "
                 << "Continue monitoring battery degradation.\n";
        }
        else
        {
            cout << "\nRecommendation: "
                 << "Battery has substantial predicted remaining life.\n";
        }
    }
};

int main()
{
    EVBatteryRULPredictor battery;

    vector<BatteryHealthData> history =
    {
        {100, 98.0},
        {200, 95.5},
        {300, 93.0},
        {400, 90.4},
        {500, 87.8},
        {600, 85.2}
    };

    for (const auto& data : history)
    {
        battery.addHealthData(data);
    }

    BatteryPredictionSystem* system = &battery;

    system->processData();

    return 0;
}