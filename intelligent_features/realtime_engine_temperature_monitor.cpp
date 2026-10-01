/**
 * @file realtime_engine_temperature_monitor.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates a real-time engine temperature monitoring system.
 *
 *   The system stores the latest temperature readings in a
 *   fixed-size deque. When the buffer becomes full, the
 *   oldest reading is automatically removed.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL deque
 *   - Sliding Window Technique
 *
 * @date 11-08-2026
 */

#include <iostream>
#include <deque>
#include <iomanip>

using namespace std;

/**
 * @class Sensor
 * @brief Abstract base class for an automotive sensor.
 */
class Sensor
{
public:

    /**
     * @brief Accept sensor readings.
     */
    virtual void inputData() = 0;

    /**
     * @brief Analyze sensor readings.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Sensor() = default;
};

/**
 * @class EngineTemperatureMonitor
 * @brief Monitors the latest engine temperature readings.
 */
class EngineTemperatureMonitor : public Sensor
{
private:

    /**
     * @brief Stores recent temperature readings.
     */
    deque<float> temperatureBuffer;

    /**
     * @brief Maximum number of readings retained.
     */
    static constexpr size_t BUFFER_SIZE = 5;

public:

    /**
     * @brief Accept engine temperature readings.
     */
    void inputData() override
    {
        int n;
        float temperature;

        cout << "Enter number of temperature readings: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter Engine Temperature "
                 << i + 1 << " (C): ";

            cin >> temperature;

            temperatureBuffer.push_back(temperature);

            /*
             * Remove the oldest reading when
             * the buffer exceeds its maximum size.
             */
            if(temperatureBuffer.size() > BUFFER_SIZE)
            {
                temperatureBuffer.pop_front();
            }
        }
    }

    /**
     * @brief Analyze the latest sensor readings.
     */
    void processData() override
    {
        cout << "\n===== Engine Temperature Report =====\n";

        if(temperatureBuffer.empty())
        {
            cout << "No temperature data available.\n