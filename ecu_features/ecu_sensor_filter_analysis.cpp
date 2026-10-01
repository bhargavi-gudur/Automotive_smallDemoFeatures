/**
 * @file ecu_sensor_filter_analysis.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Sensor Filtering and
 *   Analysis System using C++20 ranges.
 *
 *   The system filters high sensor readings and determines
 *   the minimum and maximum values.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL vector
 *   - C++20 ranges
 *   - STL algorithms
 *
 * @date 25-08-2026
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Process sensor readings.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class SensorAnalyzer
 * @brief Filters and analyzes ECU sensor readings.
 */
class SensorAnalyzer : public ECU
{
private:

    vector<float> sensorReadings =
    {
        82.5f,
        95.0f,
        108.5f,
        91.0f,
        115.0f,
        88.5f,
        102.0f
    };

public:

    /**
     * @brief Process sensor readings using C++20 ranges.
     */
    void processData() override
    {
        cout << "===== ECU Sensor Analysis =====\n";

        cout << "\nAll Sensor Readings:\n";

        for(float value : sensorReadings)
        {
            cout << value << " ";
        }

        /*
         * Filter readings above the warning threshold.
         */
        constexpr float warningLimit = 100.0f;

        vector<float> warningReadings;

        ranges::copy_if(
            sensorReadings,
            back_inserter(warningReadings),
            [](float value)
            {
                return value > 100.0f;
            }
        );

        cout << "\n\nReadings Above "
             << warningLimit
             << ":\n";

        for(float value : warningReadings)
        {
            cout << value << " ";
        }

        /*
         * Find minimum and maximum readings.
         */
        auto minimum =
            ranges::min(sensorReadings);

        auto maximum =
            ranges::max(sensorReadings);

        cout << "\n\nMinimum Reading: "
             << minimum
             << endl;

        cout << "Maximum Reading: "
             << maximum
             << endl;

        cout << "\nWarning Status: ";

        if(!warningReadings.empty())
        {
            cout << "HIGH SENSOR VALUES DETECTED ⚠️";
        }
        else
        {
            cout << "NORMAL";
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
    ECU* ecu =
        new SensorAnalyzer();

    ecu->processData();

    delete ecu;

    return 0;
}