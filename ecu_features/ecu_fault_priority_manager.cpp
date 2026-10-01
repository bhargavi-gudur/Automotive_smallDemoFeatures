/**
 * @file ecu_fault_priority_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Fault Priority Manager.
 *
 *   The system stores diagnostic faults with priority levels.
 *   The highest-priority fault is processed first using
 *   the STL priority_queue container.
 *
 *   Priority:
 *   5 -> Critical
 *   4 -> High
 *   3 -> Medium
 *   2 -> Low
 *   1 -> Informational
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL priority_queue
 *   - STL vector
 *   - Pair
 *
 * @date 19-08-2026
 */

#include <iostream>
#include <queue>
#include <string>
#include <utility>
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
     * @brief Accept diagnostic fault information.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process faults according to priority.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class FaultPriorityManager
 * @brief Manages ECU faults according to priority.
 */
class FaultPriorityManager : public ECU
{
private:

    /**
     * @brief Stores priority and fault description.
     *
     * priority_queue keeps the highest priority
     * value at the top.
     */
    priority_queue<pair<int, string>> faultQueue;

public:

    /**
     * @brief Accept fault information from the user.
     */
    void inputData() override
    {
        int n;
        int priority;
        string fault;

        cout << "Enter number of ECU faults: ";
        cin >> n;

        cin.ignore();

        for(int i = 0; i < n; ++i)
        {
            cout << "\nFault " << i + 1 << endl;

            cout << "Enter priority (1-5): ";
            cin >> priority;

            cin.ignore();

            cout << "Enter fault description: ";
            getline(cin, fault);

            faultQueue.emplace(priority, fault);
        }
    }

    /**
     * @brief Convert priority number to text.
     */
    string getPriorityName(int priority) const
    {
        switch(priority)
        {
            case 5:
                return "CRITICAL";

            case 4:
                return "HIGH";

            case 3:
                return "MEDIUM";

            case 2:
                return "LOW";

            case 1:
                return "INFORMATIONAL";

            default:
                return "UNKNOWN";
        }
    }

    /**
     * @brief Process faults from highest to lowest priority.
     */
    void processData() override
    {
        cout << "\n===== ECU Fault Priority Report =====\n";

        if(faultQueue.empty())
        {
            cout << "No ECU faults available.\n";
            return;
        }

        int faultNumber = 1;

        while(!faultQueue.empty())
        {
            const auto& currentFault = faultQueue.top();

            int priority = currentFault.first;
            const string& description = currentFault.second;

            cout << "\nFault " << faultNumber++ << endl;

            cout << "Priority   : "
                 << priority
                 << " ("
                 << getPriorityName(priority)
                 << ")"
                 << endl;

            cout << "Description: "
                 << description
                 << endl;

            faultQueue.pop();
        }

        cout << "\nAll ECU faults processed by priority.\n";
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
    ECU* ecu = new FaultPriorityManager();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}