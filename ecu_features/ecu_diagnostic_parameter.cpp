/**
 * @file ecu_diagnostic_parameter_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Parameter Manager.
 *
 *   The system stores diagnostic parameters of different
 *   data types using std::any. Parameters can contain
 *   integers, floating-point values, strings, or Boolean values.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL any
 *   - STL vector
 *   - std::any_cast
 *
 * @date 23-08-2026
 */

#include <any>
#include <iostream>
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
     * @brief Accept diagnostic parameters.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process diagnostic parameters.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class DiagnosticParameterManager
 * @brief Manages different types of ECU parameters.
 */
class DiagnosticParameterManager : public ECU
{
private:

    /**
     * @brief Stores diagnostic parameters of different types.
     */
    vector<any> parameters;

public:

    /**
     * @brief Add predefined diagnostic parameters.
     */
    void inputData() override
    {
        parameters.push_back(
            string("TEMP_SENSOR_01")
        );

        parameters.push_back(
            95.5
        );

        parameters.push_back(
            12
        );

        parameters.push_back(
            true
        );

        parameters.push_back(
            string("ECU_OPERATIONAL")
        );
    }

    /**
     * @brief Display stored diagnostic parameters.
     */
    void processData() override
    {
        cout << "\n===== ECU Diagnostic Parameter Report =====\n";

        if(parameters.empty())
        {
            cout << "No diagnostic parameters available.\n";
            return;
        }

        for(size_t i = 0;
             i < parameters.size();
             ++i)
        {
            cout << "\nParameter "
                 << i + 1
                 << ": ";

            if(parameters[i].type() == typeid(string))
            {
                cout << any_cast<string>(
                    parameters[i]
                );

                cout << " -> String";
            }
            else if(parameters[i].type() == typeid(double))
            {
                cout << any_cast<double>(
                    parameters[i]
                );

                cout << " -> Double";
            }
            else if(parameters[i].type() == typeid(int))
            {
                cout << any_cast<int>(
                    parameters[i]
                );

                cout << " -> Integer";
            }
            else if(parameters[i].type() == typeid(bool))
            {
                bool status =
                    any_cast<bool>(parameters[i]);

                cout << boolalpha
                     << status;

                cout << " -> Boolean";
            }
        }

        cout << "\n";
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
        new DiagnosticParameterManager();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}