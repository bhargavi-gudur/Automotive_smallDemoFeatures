/**
 * @file dtc_fault_code_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive Diagnostic Trouble Code (DTC)
 *   Fault Code Manager.
 *
 *   The system stores detected DTC fault codes in a set.
 *   Duplicate fault codes are automatically ignored.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL set
 *
 * @date 09-08-2026
 */

#include <iostream>
#include <set>
#include <string>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Accept fault-code input.
     */
    virtual void inputData() = 0;

    /**
     * @brief Analyze and display fault codes.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class DTCFaultManager
 * @brief Manages unique Diagnostic Trouble Codes.
 */
class DTCFaultManager : public ECU
{
private:

    /**
     * @brief Stores unique DTC codes.
     *
     * std::set automatically:
     * - Removes duplicates
     * - Keeps elements sorted
     */
    set<string> faultCodes;

public:

    /**
     * @brief Accept DTC codes from the user.
     */
    void inputData() override
    {
        int n;
        string code;

        cout << "Enter number of DTC codes: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter DTC code "
                 << i + 1 << ": ";

            cin >> code;

            faultCodes.insert(code);
        }
    }

    /**
     * @brief Display unique DTC codes.
     */
    void processData() override
    {
        cout << "\n===== DTC Fault Code Report =====\n";

        if(faultCodes.empty())
        {
            cout << "No faults detected.\n";
            return;
        }

        cout << "Unique DTC Codes:\n";

        for(const string& code : faultCodes)
        {
            cout << code << endl;
        }

        cout << "\nTotal Unique Faults: "
             << faultCodes.size()
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
    ECU* ecu = new DTCFaultManager();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}