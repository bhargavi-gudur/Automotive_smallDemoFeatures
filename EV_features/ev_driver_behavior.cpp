/**
 * @file ev_driver_behavior.cpp
 * @author Gandla Bhargavi
 * @brief EV Driver Driving Behavior and Energy Efficiency Score using OOP and STL
 * @date 04-09-2026
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
 * @brief Represents one driving sample.
 */
struct DrivingSample
{
    double speedKmph;
    double acceleration;
    double braking;
    double energyConsumption;
};

/**
 * @brief Abstract base class for EV telematics analysis.
 */
class TelematicsSystem
{
public:
    virtual void processData() = 0;

    virtual ~TelematicsSystem() = default;
};

/**
 * @brief Analyzes EV driver behavior and energy efficiency.
 */
class EVDriverBehavior : public TelematicsSystem
{
private:
    vector<DrivingSample> drivingHistory;

    map<string, double> behaviorScores;

    double efficiencyScore = 0.0;

    /**
     * @brief Calculates average speed.
     */
    double calculateAverageSpeed() const
    {
        if (drivingHistory.empty())
        {
            return 0.0;
        }

        const double totalSpeed = accumulate(
            drivingHistory.begin(),
            drivingHistory.end(),
            0.0,
            [](double total, const DrivingSample& sample)
            {
                return total + sample.speedKmph;
            });

        return totalSpeed / drivingHistory.size();
    }

    /**
     * @brief Counts harsh acceleration events.
     */
    int countHarshAcceleration() const
    {
        return count_if(
            drivingHistory.begin(),
            drivingHistory.end(),
            [](const DrivingSample& sample)
            {
                return sample.acceleration > 3.0;
            });
    }

    /**
     * @brief Counts harsh braking events.
     */
    int countHarshBraking() const
    {
        return count_if(
            drivingHistory.begin(),
            drivingHistory.end(),
            [](const DrivingSample& sample)
            {
                return sample.braking > 3.0;
            });
    }

    /**
     * @brief Calculates average energy consumption.
     */
    double calculateAverageConsumption() const
    {
        if (drivingHistory.empty())
        {
            return 0.0;
        }

        const double totalEnergy = accumulate(
            drivingHistory.begin(),
            drivingHistory.end(),
            0.0,
            [](double total, const DrivingSample& sample)
            {
                return total + sample.energyConsumption;
            });

        return totalEnergy / drivingHistory.size();
    }

    /**
     * @brief Calculates behavior score.
     */
    void calculateBehaviorScore()
    {
        const int harshAcceleration = countHarshAcceleration();
        const int harshBraking = countHarshBraking();

        double accelerationScore = 100.0;
        double brakingScore = 100.0;
        double speedScore = 100.0;

        accelerationScore -= harshAcceleration * 10.0;
        brakingScore -= harshBraking * 10.0;

        const double averageSpeed = calculateAverageSpeed();

        // Higher average speed generally increases energy consumption.
        if (averageSpeed > 100.0)
        {
            speedScore -= 20.0;
        }
        else if (averageSpeed > 80.0)
        {
            speedScore -= 10.0;
        }

        accelerationScore = max(0.0, accelerationScore);
        brakingScore = max(0.0, brakingScore);

        behaviorScores["Acceleration"] = accelerationScore;
        behaviorScores["Braking"] = brakingScore;
        behaviorScores["Speed Control"] = speedScore;

        efficiencyScore =
            (accelerationScore +
             brakingScore +
             speedScore) / 3.0;
    }

public:
    /**
     * @brief Adds a driving sample to the history.
     */
    void addDrivingSample(const DrivingSample& sample)
    {
        drivingHistory.push_back(sample);
    }

    /**
     * @brief Processes driving telemetry data.
     */
    void processData() override
    {
        if (drivingHistory.empty())
        {
            cout << "No driving data available.\n";
            return;
        }

        calculateBehaviorScore();

        cout << "\n===== EV DRIVER BEHAVIOR ANALYSIS =====\n";

        cout << fixed << setprecision(2);

        cout << "\nAverage Speed: "
             << calculateAverageSpeed()
             << " km/h";

        cout << "\nAverage Energy Consumption: "
             << calculateAverageConsumption()
             << " kWh/100 km";

        cout << "\nHarsh Acceleration Events: "
             << countHarshAcceleration();

        cout << "\nHarsh Braking Events: "
             << countHarshBraking();

        cout << "\n\nBehavior Scores:\n";

        for (const auto& [category, score] : behaviorScores)
        {
            cout << category << ": "
                 << score << "/100\n";
        }

        cout << "\nOverall Energy Efficiency Score: "
             << efficiencyScore
             << "/100\n";

        if (efficiencyScore >= 85.0)
        {
            cout << "Driving Rating: EXCELLENT\n";
        }
        else if (efficiencyScore >= 70.0)
        {
            cout << "Driving Rating: GOOD\n";
        }
        else if (efficiencyScore >= 50.0)
        {
            cout << "Driving Rating: MODERATE\n";
        }
        else
        {
            cout << "Driving Rating: POOR\n";
        }
    }

    /**
     * @brief Displays driver recommendations.
     */
    void displayRecommendations() const
    {
        cout << "\n===== DRIVER RECOMMENDATIONS =====\n";

        if (countHarshAcceleration() > 0)
        {
            cout << "- Reduce sudden acceleration.\n";
        }

        if (countHarshBraking() > 0)
        {
            cout << "- Maintain safer following distance.\n";
        }

        if (calculateAverageSpeed() > 100.0)
        {
            cout << "- Reduce high-speed driving to improve EV range.\n";
        }

        if (efficiencyScore >= 85.0)
        {
            cout << "- Excellent driving pattern. Maintain current behavior.\n";
        }
    }
};

int main()
{
    EVDriverBehavior driver;

    vector<DrivingSample> tripData =
    {
        {65.0, 1.2, 1.0, 14.8},
        {72.0, 1.5, 1.3, 15.2},
        {88.0, 2.0, 1.8, 16.1},
        {95.0, 3.4, 2.1, 18.2},
        {82.0, 1.7, 3.6, 17.5},
        {76.0, 1.4, 1.2, 15.8},
        {91.0, 3.2, 1.6, 17.9}
    };

    for (const auto& sample : tripData)
    {
        driver.addDrivingSample(sample);
    }

    TelematicsSystem* system = &driver;

    system->processData();

    driver.displayRecommendations();

    return 0;
}