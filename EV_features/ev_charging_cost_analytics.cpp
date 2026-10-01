/**
 * @file ev_charging_cost_analytics.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an Electric Vehicle Charging Cost and
 *   Energy Analytics System.
 *
 *   Features:
 *   - Charging session records
 *   - Energy consumption calculation
 *   - Electricity tariff management
 *   - Charging cost calculation
 *   - Total energy consumed
 *   - Total charging cost
 *   - Average charging cost
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL map
 *   - STL vector
 *   - STL numeric
 *   - STL pair
 *
 * @date 30-08-2026
 */

#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * @class EVSystem
 * @brief Abstract base class for an EV telematics system.
 */
class EVSystem
{
public:

    /**
     * @brief Accept charging information.
     */
    virtual void inputData() = 0;

    /**
     * @brief Analyze charging information.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~EVSystem() = default;
};

/**
 * @class ChargingCostAnalytics
 * @brief Calculates EV charging energy and cost.
 */
class ChargingCostAnalytics : public EVSystem
{
private:

    /**
     * @brief Charging session:
     *
     * Pair:
     * first  -> Energy consumed in kWh
     * second -> Electricity price per kWh
     */
    vector<pair<double, double>> sessions;

    /**
     * @brief Stores electricity tariffs by charging type.
     *
     * Key   -> Charging type
     * Value -> Price per kWh
     */
    map<string, double> tariffs =
    {
        {"Home", 7.50},
        {"Public AC", 10.00},
        {"Fast DC", 18.00}
    };

public:

    /**
     * @brief Accept charging session data.
     */
    void inputData() override
    {
        int n;

        cout << "===== EV Charging Cost Setup =====\n";

        cout << "\nAvailable Charging Types:\n";

        for(const auto& [type, price] : tariffs)
        {
            cout << type
                 << " -> Rs."
                 << price
                 << "/kWh\n";
        }

        cout << "\nEnter number of charging sessions: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            string type;
            double energy;

            cout << "\nSession "
                 << i + 1
                 << endl;

            cout << "Enter Charging Type: ";
            cin.ignore();
            getline(cin, type);

            /*
             * Check whether the charging type exists.
             */
            auto tariff = tariffs.find(type);

            if(tariff == tariffs.end())
            {
                cout << "Invalid charging type.\n";
                --i;
                continue;
            }

            cout << "Enter Energy Consumed (kWh): ";
            cin >> energy;

            if(energy <= 0)
            {
                cout << "Energy must be positive.\n";
                --i;
                continue;
            }

            sessions.emplace_back(
                energy,
                tariff->second
            );
        }
    }

    /**
     * @brief Calculate and display charging analytics.
     */
    void processData() override
    {
        cout << fixed
             << setprecision(2);

        cout << "\n===== EV Charging Analytics =====\n";

        if(sessions.empty())
        {
            cout << "No charging sessions available.\n";
            return;
        }

        double totalEnergy =
            accumulate(
                sessions.begin(),
                sessions.end(),
                0.0,
                [](double total,
                   const pair<double, double>& session)
                {
                    return total + session.first;
                }
            );

        double totalCost =
            accumulate(
                sessions.begin(),
                sessions.end(),
                0.0,
                [](double total,
                   const pair<double, double>& session)
                {
                    return total +
                           (session.first *
                            session.second);
                }
            );

        const double averageCost =
            totalCost / sessions.size();

        cout << "Total Charging Sessions : "
             << sessions.size()
             << endl;

        cout << "Total Energy Consumed   : "
             << totalEnergy
             << " kWh"
             << endl;

        cout << "Total Charging Cost     : Rs."
             << totalCost
             << endl;

        cout << "Average Session Cost    : Rs."
             << averageCost
             << endl;

        cout << "\n===== Session Details =====\n";

        for(size_t i = 0;
            i < sessions.size();
            ++i)
        {
            const double energy =
                sessions[i].first;

            const double price =
                sessions[i].second;

            const double cost =
                energy * price;

            cout << "\nSession "
                 << i + 1
                 << endl;

            cout << "Energy : "
                 << energy
                 << " kWh"
                 << endl;

            cout << "Tariff : Rs."
                 << price
                 << "/kWh"
                 << endl;

            cout << "Cost   : Rs."
                 << cost
                 << endl;
        }

        cout << "\n===== Charging Summary =====\n";

        if(totalCost > 1000)
        {
            cout << "Warning: High charging expenditure.\n";
        }
        else
        {
            cout << "Charging expenditure is within the limit.\n";
        }
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
        new ChargingCostAnalytics();

    ev->inputData();

    ev->processData();

    delete ev;

    return 0;
}