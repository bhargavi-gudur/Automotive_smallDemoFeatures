/**
 * @file ecu_diagnostic_fault_registry.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Fault Registry.
 *
 *   The system stores active Diagnostic Trouble Codes (DTCs)
 *   using an unordered_set. Duplicate fault codes are
 *   automatically ignored.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL unordered_set
 *   - Fast average-time lookup
 *
 * @date 15-08-2026
 */

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Accept diagnostic fault data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process and display active faults.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class FaultRegistry
 * @brief Maintains a unique collection of active DTCs.
 */
class FaultRegistry : public ECU
{
private:

    /**
     * @brief Stores unique active DTC codes.
     */
    unordered_set<string> activeFaults;

public:

    /**
     * @brief Accept DTC codes from the user.
     */
    void inputData() override
    {
        int n;
        string code;

        cout << "Enter number of detected faults: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter DTC code "
                 << i + 1 << ": ";

            cin >> code;

            activeFaults.insert(code);
        }
    }

    /**
     * @brief Display unique active faults.
     */
    void processData() override
    {
        cout << "\n===== ECU Diagnostic Fault Registry =====\n";

        if(activeFaults.empty())
        {
            cout << "No active faults detected.\n";
            return;
        }

        cout << "Active Unique DTC Codes:\n";

        for(const string& code : activeFaults)
        {
            cout << " - " << code << endl;
        }

        cout << "\nTotal Unique Faults: "
             << activeFaults.size()
             << endl;

        cout << "\nChecking P0300 status...\n";

        if(activeFaults.find("P0300") != activeFaults.end())
        {
            cout << "P0300 is ACTIVE.\n";
        }
        else
        {
            cout << "P0300 is NOT ACTIVE.\n";
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
    ECU* ecu = new FaultRegistry();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}