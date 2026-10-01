/**
 * @file ecu_sensor_data_validation.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Sensor Data Validation System.
 *
 *   The system receives sensor readings and uses
 *   std::optional to safely represent missing sensor data.
 *   Valid readings are analyzed, while missing readings
 *   generate a diagnostic warning.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL optional
 *   - STL vector
 *
 * @date 21-08-2026
 */

#include <iostream>
#include <optional>
#include <string>
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
     * @brief Accept sensor data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Validate sensor data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class SensorDataValidator
 * @brief Validates optional ECU sensor readings.
 */
class SensorDataValidator : public ECU
{
private:

    /**
     * @brief Stores optional sensor values.
     *
     * nullopt represents missing sensor data.
     */
    vector<optional<float>> sensorValues;

public:

    /**
     * @brief Accept sensor readings from the user.
     */
    void inputData() override
    {
        int n;
        int available;
        float value;

        cout << "Enter number of sensor readings: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            cout << "\nSensor " << i + 1 << endl;

            cout << "Is sensor data available? "
                 << "(1 = Yes, 0 = No): ";
            cin >> available;

            if(available == 1)
            {
                cout << "Enter sensor value: ";
                cin >> value;

                sensorValues.push_back(value);
            }
            else
            {
                sensorValues.push_back(nullopt);
            }
        }
    }

    /**
     * @brief Validate and display sensor readings.
     */
    void processData() override
    {
        cout << "\n===== ECU Sensor Validation Report =====\n";

        for(size_t i = 0;
            i < sensorValues.size();
            ++i)
        {
            cout << "\nSensor " << i + 1 << ": ";

            if(sensorValues[i].has_value())
            {
                cout << "Value = "
                     << sensorValues[i].value()
                     << endl;

                cout << "Status = Valid Sensor Data"
                     << endl;
            }
            else
            {
                cout << "Value = NOT AVAILABLE"
                     << endl;

                cout << "Status = Sensor Data Missing ⚠️"
                     << endl;
            }
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
    ECU* ecu =
        new SensorDataValidator();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}