/**
 * @file ecu_sensor_timestamp_monitor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Sensor Timestamp and
 *   Execution-Time Monitoring System.
 *
 *   The system records timestamps for ECU sensor events
 *   and measures the execution time of a diagnostic
 *   processing operation.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL chrono
 *   - STL vector
 *   - Time duration measurement
 *
 * @date 27-08-2026
 */

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Process ECU diagnostic information.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class SensorMonitor
 * @brief Monitors ECU sensor events and execution time.
 */
class SensorMonitor : public ECU
{
private:

    /**
     * @brief Stores sensor event descriptions.
     */
    vector<string> sensorEvents =
    {
        "Engine Temperature Reading",
        "Brake Pressure Reading",
        "Battery Voltage Reading",
        "CAN Communication Check"
    };

    /**
     * @brief Returns the current local timestamp.
     */
    string getCurrentTime() const
    {
        const auto now = system_clock::now();

        const time_t currentTime =
            system_clock::to_time_t(now);

        tm localTime{};

#ifdef _WIN32
        localtime_s(&localTime, &currentTime);
#else
        localtime_r(&currentTime, &localTime);
#endif

        ostringstream output;

        output << put_time(
            &localTime,
            "%Y-%m-%d %H:%M:%S"
        );

        return output.str();
    }

public:

    /**
     * @brief Process ECU sensor events and measure
     *        execution time.
     */
    void processData() override
    {
        cout << "===== ECU Sensor Time Monitor =====\n";

        cout << "\nSensor Events:\n";

        for(const string& event : sensorEvents)
        {
            cout << "[" << getCurrentTime() << "] "
                 << event
                 << endl;

            /*
             * Simulate ECU processing delay.
             */
            this_thread::sleep_for(
                milliseconds(100)
            );
        }

        /*
         * Measure execution time of a diagnostic operation.
         */
        const auto start =
            steady_clock::now();

        /*
         * Simulated diagnostic calculation.
         */
        volatile long long calculation = 0;

        for(long long i = 0; i < 1000000; ++i)
        {
            calculation += i;
        }

        const auto end =
            steady_clock::now();

        const auto executionTime =
            duration_cast<microseconds>(
                end - start
            );

        cout << "\n===== Execution-Time Report =====\n";

        cout << "Diagnostic Operation Time: "
             << executionTime.count()
             << " microseconds"
             << endl;

        cout << "Monitoring Completed At: "
             << getCurrentTime()
             << endl;
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
        new SensorMonitor();

    ecu->processData();

    delete ecu;

    return 0;
}