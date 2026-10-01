/**
 * @file ecu_fault_code_lookup.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Fault Code Lookup System.
 *
 *   The system maps Diagnostic Trouble Codes (DTCs)
 *   to their corresponding fault descriptions.
 *   unordered_map provides average O(1) lookup time.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL unordered_map
 *
 * @date 10-08-2026
 */

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for ECU systems.
 */
class ECU
{
public:

    /**
     * @brief Accept fault code from user.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process and display fault information.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class FaultCodeLookup
 * @brief Provides fast DTC-to-description lookup.
 */
class FaultCodeLookup : public ECU
{
private:

    /**
     * @brief Stores DTC codes and descriptions.
     */
    unordered_map<string, string> faultDatabase;

    string requestedCode;

public:

    /**
     * @brief Initialize the fault database.
     */
    FaultCodeLookup()
    {
        faultDatabase.emplace(
            "P0300",
            "Random/Multiple Cylinder Misfire Detected"
        );

        faultDatabase.emplace(
            "P0420",
            "Catalyst System Efficiency Below Threshold"
        );

        faultDatabase.emplace(
            "P0171",
            "System Too Lean"
        );

        faultDatabase.emplace(
            "P0128",
            "Coolant Temperature Below Thermostat Regulation"
        );

        faultDatabase.emplace(
            "P0113",
            "Intake Air Temperature Sensor High Input"
        );
    }

    /**
     * @brief Accept DTC code from user.
     */
    void inputData() override
    {
        cout << "Enter DTC Code: ";
        cin >> requestedCode;
    }

    /**
     * @brief Look up and display DTC information.
     */
    void processData() override
    {
        cout << "\n===== ECU Fault Code Report =====\n";

        auto result = faultDatabase.find(requestedCode);

        if(result != faultDatabase.end())
        {
            cout << "DTC Code   : "
                 << result->first << endl;

            cout << "Description: "
                 << result->second << endl;
        }
        else
        {
            cout << "DTC Code   : "
                 << requestedCode << endl;

            cout << "Description: Unknown Fault Code" << endl;
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
    ECU* ecu = new FaultCodeLookup();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}