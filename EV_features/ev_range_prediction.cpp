/**
 * @file ev_range_prediction.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an Electric Vehicle Range Prediction System.
 *
 *   Features:
 *   - Battery SoC monitoring
 *   - Battery capacity
 *   - Recent energy-consumption history
 *   - Average energy consumption
 *   - Estimated remaining energy
 *   - Predicted driving range
 *   - Low-range warning
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL vector
 *   - STL numeric
 *   - STL optional
 *
 * @date 29-08-2026
 */

#include <iomanip>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

using namespace std;

/**
 * @class EVSystem
 * @brief Abstract base class for an electric vehicle system.
 */
class EVSystem
{
public:

    /**
     * @brief Accept EV data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Calculate and display EV range.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~EVSystem() = default;
};

/**
 * @class EVRangePredictor
 * @brief Predicts the remaining driving range of an EV.
 */
class EVRangePredictor : public EVSystem
{
private:

    double batteryCapacity{};
    double currentSoC{};

    /**
     * @brief Stores recent energy consumption values.
     *
     * Unit: kWh / 100 km
     */
    vector<double> consumptionHistory;

    /**
     * @brief Calculates average energy consumption.
     */
    optional<double> calculateAverageConsumption() const
    {
        if(consumptionHistory.empty())
        {
            return nullopt;
        }

        const double total =
            accumulate(
                consumptionHistory.begin(),
                consumptionHistory.end(),
                0.0
            );

        return total / consumptionHistory.size();
    }

public:

    /**
     * @brief Accept EV parameters from the user.
     */
    void inputData() override
    {
        int n;

        cout << "===== EV Range Prediction Setup =====\n";

        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;

        cout << "Enter Current SoC (%): ";
        cin >> currentSoC;

        cout << "Enter number of consumption records: ";
        cin >> n;

        if(n <= 0)
        {
            return;
        }

        cout << "\nEnter energy consumption values "
             << "(kWh/100 km):\n";

        for(int i = 0; i < n; ++i)
        {
            double consumption;

            cout << "Record "
                 << i + 1
                 << ": ";

            cin >> consumption;

            if(consumption > 0)
            {
                consumptionHistory.push_back(
                    consumption
                );
            }
        }
    }

    /**
     * @brief Process the range prediction.
     */
    void processData() override
    {
        cout << fixed
             << setprecision(2);

        cout << "\n===== EV Range Prediction Report =====\n";

        if(batteryCapacity <= 0 ||
           currentSoC < 0 ||
           currentSoC > 100)
        {
            cout << "Invalid battery information.\n";
            return;
        }

        const auto averageConsumption =
            calculateAverageConsumption();

        if(!averageConsumption.has_value())
        {
            cout << "No valid consumption data available.\n";
            return;
        }

        /*
         * Calculate remaining battery energy.
         */
        const double remainingEnergy =
            batteryCapacity *
            currentSoC / 100.0;

        /*
         * Convert kWh/100 km into predicted range.
         */
        const double predictedRange =
            (remainingEnergy /
             averageConsumption.value()) *
            100.0;

        cout << "Battery Capacity      : "
             << batteryCapacity
             << " kWh\n";

        cout << "Current SoC           : "
             << currentSoC
             << " %\n";

        cout << "Average Consumption   : "
             << averageConsumption.value()
             << " kWh/100 km\n";

        cout << "Remaining Energy      : "
             << remainingEnergy
             << " kWh\n";

        cout << "Predicted Range       : "
             << predictedRange
             << " km\n";

        cout << "Range Status          : ";

        if(predictedRange < 50)
        {
            cout << "LOW RANGE WARNING";
        }
        else if(predictedRange < 100)
        {
            cout << "MODERATE RANGE";
        }
        else
        {
            cout << "GOOD RANGE";
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
        new EVRangePredictor();

    ev->inputData();

    ev->processData();

    delete ev;

    return 0;
}