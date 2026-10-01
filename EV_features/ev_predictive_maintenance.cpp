/**
 * @file ev_predictive_maintenance.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an Electric Vehicle Predictive Maintenance
 *   Telematics System.
 *
 *   The system monitors EV component health and generates
 *   maintenance recommendations based on health scores.
 *
 *   Components:
 *   - Battery
 *   - Drive Motor
 *   - Inverter
 *   - Brake System
 *   - Cooling System
 *   - 12V Battery
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL unordered_map
 *   - STL vector
 *   - STL algorithms
 *   - Lambda expressions
 *
 * @date 31-08-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @class EVSystem
 * @brief Abstract base class for EV telematics systems.
 */
class EVSystem
{
public:

    /**
     * @brief Process vehicle health data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~EVSystem() = default;
};

/**
 * @class PredictiveMaintenance
 * @brief Monitors health of EV components.
 */
class PredictiveMaintenance : public EVSystem
{
private:

    /**
     * @brief Stores component health scores.
     *
     * Key   -> Component name
     * Value -> Health percentage
     */
    unordered_map<string, double> componentHealth
    {
        {"Battery", 91.0},
        {"Drive Motor", 96.0},
        {"Inverter", 88.0},
        {"Brake System", 72.0},
        {"Cooling System", 84.0},
        {"12V Battery", 65.0}
    };

    /**
     * @brief Returns maintenance status for a component.
     */
    string getStatus(double health) const
    {
        if(health >= 90.0)
        {
            return "EXCELLENT";
        }

        if(health >= 80.0)
        {
            return "GOOD";
        }

        if(health >= 70.0)
        {
            return "SERVICE SOON";
        }

        return "MAINTENANCE REQUIRED";
    }

public:

    /**
     * @brief Display component health and maintenance status.
     */
    void processData() override
    {
        cout << fixed
             << setprecision(1);

        cout << "===== EV Predictive Maintenance =====\n";

        if(componentHealth.empty())
        {
            cout << "No component data available.\n";
            return;
        }

        /*
         * Display all component health values.
         */
        for(const auto& [component, health]
            : componentHealth)
        {
            cout << "\nComponent : "
                 << component
                 << endl;

            cout << "Health    : "
                 << health
                 << "%"
                 << endl;

            cout << "Status    : "
                 << getStatus(health)
                 << endl;
        }

        /*
         * Calculate average vehicle health.
         */
        const double totalHealth =
            accumulate(
                componentHealth.begin(),
                componentHealth.end(),
                0.0,
                [](double total,
                   const auto& component)
                {
                    return total + component.second;
                }
            );

        const double averageHealth =
            totalHealth /
            componentHealth.size();

        cout << "\n===== Vehicle Health Summary =====\n";

        cout << "Average Component Health : "
             << averageHealth
             << "%"
             << endl;

        /*
         * Find the weakest component.
         */
        auto weakestComponent =
            min_element(
                componentHealth.begin(),
                componentHealth.end(),
                [](const auto& first,
                   const auto& second)
                {
                    return first.second <
                           second.second;
                }
            );

        if(weakestComponent !=
           componentHealth.end())
        {
            cout << "Weakest Component        : "
                 << weakestComponent->first
                 << endl;

            cout << "Weakest Health            : "
                 << weakestComponent->second
                 << "%"
                 << endl;
        }

        /*
         * Find components requiring service.
         */
        vector<pair<string, double>>
            serviceRequired;

        for(const auto& [component, health]
            : componentHealth)
        {
            if(health < 80.0)
            {
                serviceRequired.emplace_back(
                    component,
                    health
                );
            }
        }

        cout << "\n===== Maintenance Prediction =====\n";

        if(serviceRequired.empty())
        {
            cout << "No immediate maintenance required.\n";
        }
        else
        {
            cout << "Components requiring attention:\n";

            for(const auto& [component, health]
                : serviceRequired)
            {
                cout << "- "
                     << component
                     << " ("
                     << health
                     << "%)"
                     << endl;
            }
        }

        /*
         * Overall vehicle recommendation.
         */
        cout << "\n===== Telematics Recommendation =====\n";

        if(averageHealth >= 90.0)
        {
            cout << "Vehicle health is excellent.";
        }
        else if(averageHealth >= 80.0)
        {
            cout << "Vehicle health is good. "
                    "Continue regular monitoring.";
        }
        else
        {
            cout << "Vehicle service is recommended.";
        }

        cout << endl;
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    EVSystem* ev =
        new PredictiveMaintenance();

    ev->processData();

    delete ev;

    return 0;
}