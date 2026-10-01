/**
 * @file ev_predictive_range.cpp
 * @author Gandla Bhargavi
 * @brief EV Predictive Range using Traffic, Elevation and Driving Efficiency
 *        with OOP and STL
 * @date 13-09-2026
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
 * @brief Represents historical EV energy consumption.
 */
struct DrivingRecord
{
    double distanceKm;
    double energyUsedKWh;
};

/**
 * @brief Represents current route conditions.
 */
struct RouteCondition
{
    string conditionName;
    double distanceKm;
    double trafficFactor;
    double elevationFactor;
};

/**
 * @brief Abstract base class for EV range prediction.
 */
class EVRangeSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVRangeSystem() = default;
};

/**
 * @brief Predicts EV range using real-world route factors.
 */
class PredictiveRangeCalculator : public EVRangeSystem
{
private:
    double batteryCapacityKWh;
    double currentSoC;

    vector<DrivingRecord> drivingHistory;
    vector<RouteCondition> routeConditions;

    map<string, double> efficiencyFactors =
    {
        {"Excellent", 0.90},
        {"Good", 1.00},
        {"Moderate", 1.10},
        {"Poor", 1.25}
    };

    double averageConsumption = 0.0;
    double adjustedConsumption = 0.0;
    double predictedRangeKm = 0.0;

    /**
     * @brief Calculates historical average energy consumption.
     */
    double calculateAverageConsumption() const
    {
        if (drivingHistory.empty())
        {
            return 0.0;
        }

        const double totalDistance = accumulate(
            drivingHistory.begin(),
            drivingHistory.end(),
            0.0,
            [](double total, const DrivingRecord& record)
            {
                return total + record.distanceKm;
            });

        const double totalEnergy = accumulate(
            drivingHistory.begin(),
            drivingHistory.end(),
            0.0,
            [](double total, const DrivingRecord& record)
            {
                return total + record.energyUsedKWh;
            });

        if (totalDistance <= 0.0)
        {
            return 0.0;
        }

        return (totalEnergy / totalDistance) * 100.0;
    }

    /**
     * @brief Calculates average route traffic factor.
     */
    double calculateTrafficFactor() const
    {
        if (routeConditions.empty())
        {
            return 1.0;
        }

        const double totalDistance = accumulate(
            routeConditions.begin(),
            routeConditions.end(),
            0.0,
            [](double total, const RouteCondition& route)
            {
                return total + route.distanceKm;
            });

        if (totalDistance <= 0.0)
        {
            return 1.0;
        }

        const double weightedTraffic = accumulate(
            routeConditions.begin(),
            routeConditions.end(),
            0.0,
            [](double total, const RouteCondition& route)
            {
                return total +
                       (route.distanceKm *
                        route.trafficFactor);
            });

        return weightedTraffic / totalDistance;
    }

    /**
     * @brief Calculates average elevation factor.
     */
    double calculateElevationFactor() const
    {
        if (routeConditions.empty())
        {
            return 1.0;
        }

        const double totalDistance = accumulate(
            routeConditions.begin(),
            routeConditions.end(),
            0.0,
            [](double total, const RouteCondition& route)
            {
                return total + route.distanceKm;
            });

        if (totalDistance <= 0.0)
        {
            return 1.0;
        }

        const double weightedElevation = accumulate(
            routeConditions.begin(),
            routeConditions.end(),
            0.0,
            [](double total, const RouteCondition& route)
            {
                return total +
                       (route.distanceKm *
                        route.elevationFactor);
            });

        return weightedElevation / totalDistance;
    }

    /**
     * @brief Determines driver efficiency factor.
     */
    double calculateDriverFactor() const
    {
        if (averageConsumption <= 15.0)
        {
            return efficiencyFactors.at("Excellent");
        }

        if (averageConsumption <= 18.0)
        {
            return efficiencyFactors.at("Good");
        }

        if (averageConsumption <= 22.0)
        {
            return efficiencyFactors.at("Moderate");
        }

        return efficiencyFactors.at("Poor");
    }

    /**
     * @brief Calculates route-adjusted energy consumption.
     */
    double calculateAdjustedConsumption() const
    {
        const double trafficFactor =
            calculateTrafficFactor();

        const double elevationFactor =
            calculateElevationFactor();

        const double driverFactor =
            calculateDriverFactor();

        return averageConsumption *
               trafficFactor *
               elevationFactor *
               driverFactor;
    }

    /**
     * @brief Calculates predicted range from available battery energy.
     */
    double calculatePredictedRange() const
    {
        if (adjustedConsumption <= 0.0)
        {
            return 0.0;
        }

        const double availableEnergy =
            batteryCapacityKWh *
            currentSoC / 100.0;

        return (availableEnergy /
                adjustedConsumption) * 100.0;
    }

public:
    /**
     * @brief Constructor.
     */
    PredictiveRangeCalculator(
        double batteryCapacity,
        double soc)
        : batteryCapacityKWh(batteryCapacity),
          currentSoC(soc)
    {
    }

    /**
     * @brief Adds a historical driving record.
     */
    void addDrivingRecord(const DrivingRecord& record)
    {
        if (record.distanceKm > 0.0 &&
            record.energyUsedKWh > 0.0)
        {
            drivingHistory.push_back(record);
        }
    }

    /**
     * @brief Adds route conditions.
     */
    void addRouteCondition(const RouteCondition& route)
    {
        if (route.distanceKm > 0.0 &&
            route.trafficFactor > 0.0 &&
            route.elevationFactor > 0.0)
        {
            routeConditions.push_back(route);
        }
    }

    /**
     * @brief Processes predictive range calculation.
     */
    void processData() override
    {
        if (drivingHistory.empty())
        {
            cout << "No historical driving data available.\n";
            return;
        }

        if (routeConditions.empty())
        {
            cout << "No route condition data available.\n";
            return;
        }

        averageConsumption =
            calculateAverageConsumption();

        adjustedConsumption =
            calculateAdjustedConsumption();

        predictedRangeKm =
            calculatePredictedRange();

        const double availableEnergy =
            batteryCapacityKWh *
            currentSoC / 100.0;

        cout << "\n===== EV PREDICTIVE RANGE ANALYSIS =====\n";

        cout << fixed << setprecision(2);

        cout << "\nBattery Capacity: "
             << batteryCapacityKWh
             << " kWh";

        cout << "\nCurrent SoC: "
             << currentSoC
             << "%";

        cout << "\nAvailable Battery Energy: "
             << availableEnergy
             << " kWh";

        cout << "\nHistorical Consumption: "
             << averageConsumption
             << " kWh/100 km";

        cout << "\n\nRoute Conditions:\n";

        for (const auto& route : routeConditions)
        {
            cout << route.conditionName
                 << " | Distance: "
                 << route.distanceKm
                 << " km"
                 << " | Traffic Factor: "
                 << route.trafficFactor
                 << " | Elevation Factor: "
                 << route.elevationFactor
                 << '\n';
        }

        cout << "\nAverage Traffic Factor: "
             << calculateTrafficFactor();

        cout << "\nAverage Elevation Factor: "
             << calculateElevationFactor();

        cout << "\nDriver Efficiency Factor: "
             << calculateDriverFactor();

        cout << "\nAdjusted Consumption: "
             << adjustedConsumption
             << " kWh/100 km";

        cout << "\nPredicted EV Range: "
             << predictedRangeKm
             << " km";

        displayRangeStatus();
    }

    /**
     * @brief Displays range condition.
     */
    void displayRangeStatus() const
    {
        cout << "\n\nRange Status: ";

        if (predictedRangeKm >= 200.0)
        {
            cout << "GOOD";
        }
        else if (predictedRangeKm >= 100.0)
        {
            cout << "MODERATE";
        }
        else
        {
            cout << "LOW - CHARGING RECOMMENDED";
        }

        cout << '\n';
    }
};

int main()
{
    PredictiveRangeCalculator ev(
        60.0,     // Battery capacity in kWh
        70.0      // Current SoC
    );

    vector<DrivingRecord> history =
    {
        {120.0, 19.2},
        {150.0, 24.0},
        {100.0, 15.5},
        {180.0, 29.0},
        {140.0, 22.4}
    };

    for (const auto& record : history)
    {
        ev.addDrivingRecord(record);
    }

    vector<RouteCondition> route =
    {
        {
            "City Traffic",
            25.0,
            1.20,
            1.05
        },
        {
            "Highway",
            60.0,
            1.05,
            1.00
        },
        {
            "Hilly Road",
            35.0,
            1.10,
            1.20
        }
    };

    for (const auto& condition : route)
    {
        ev.addRouteCondition(condition);
    }

    EVRangeSystem* system = &ev;

    system->processData();

    return 0;
}