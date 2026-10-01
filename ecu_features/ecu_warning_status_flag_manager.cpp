/**
 * @file ecu_warning_status_flag_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Warning and Status Flag Manager.
 *
 *   The system uses std::bitset to store multiple ECU warning
 *   and status flags in a compact form. Each bit represents
 *   one vehicle condition.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL bitset
 *   - Bit manipulation
 *
 * @date 18-08-2026
 */

#include <bitset>
#include <iostream>
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
     * @brief Accept ECU status information.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process and display ECU status.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class ECUStatusManager
 * @brief Manages ECU warning flags using std::bitset.
 */
class ECUStatusManager : public ECU
{
private:

    /**
     * @brief Eight ECU status flags.
     *
     * Bit 0 -> Engine Temperature
     * Bit 1 -> Low Battery Voltage
     * Bit 2 -> Brake Fault
     * Bit 3 -> ABS Fault
     * Bit 4 -> Airbag Fault
     * Bit 5 -> Oil Pressure
     * Bit 6 -> CAN Communication
     * Bit 7 -> Check Engine
     */
    bitset<8> statusFlags;

    const string flagNames[8] =
    {
        "Engine Temperature",
        "Low Battery Voltage",
        "Brake Fault",
        "ABS Fault",
        "Airbag Fault",
        "Oil Pressure",
        "CAN Communication",
        "Check Engine"
    };

public:

    /**
     * @brief Accept warning flag status from the user.
     */
    void inputData() override
    {
        int status;

        cout << "===== ECU Status Input =====\n";

        for(int i = 0; i < 8; ++i)
        {
            cout << "Is " << flagNames[i]
                 << " active? (1 = Yes, 0 = No): ";

            cin >> status;

            if(status == 1)
            {
                statusFlags.set(i);
            }
            else
            {
                statusFlags.reset(i);
            }
        }
    }

    /**
     * @brief Display active ECU warning flags.
     */
    void processData() override
    {
        cout << "\n===== ECU Warning Status Report =====\n";

        cout << "Status Bitset: "
             << statusFlags
             << endl;

        bool faultDetected = false;

        for(int i = 0; i < 8; ++i)
        {
            cout << "Bit " << i
                 << " - "
                 << flagNames[i]
                 << " : ";

            if(statusFlags.test(i))
            {
                cout << "ACTIVE";
                faultDetected = true;
            }
            else
            {
                cout << "NORMAL";
            }

            cout << endl;
        }

        cout << "\nOverall ECU Status: ";

        if(faultDetected)
        {
            cout << "WARNING - FAULTS DETECTED";
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
    ECU* ecu = new ECUStatusManager();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}