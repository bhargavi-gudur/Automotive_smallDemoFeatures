/**
 * @file ecu_event_history_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Event History Manager.
 *
 *   The system stores ECU events using a multimap.
 *   Multiple events can have the same category,
 *   such as multiple engine or battery events.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL multimap
 *
 * @date 12-08-2026
 */

#include <iostream>
#include <map>
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
     * @brief Accept ECU event data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Display stored ECU events.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class ECUEventHistory
 * @brief Stores and displays multiple ECU events.
 */
class ECUEventHistory : public ECU
{
private:

    /**
     * @brief Stores ECU category and event description.
     *
     * multimap allows multiple values for the same key.
     */
    multimap<string, string> eventHistory;

public:

    /**
     * @brief Accept ECU event information.
     */
    void inputData() override
    {
        int n;
        string category;
        string event;

        cout << "Enter number of ECU events: ";
        cin >> n;

        cin.ignore();

        for(int i = 0; i < n; ++i)
        {
            cout << "\nEvent " << i + 1 << endl;

            cout << "Enter ECU Category: ";
            getline(cin, category);

            cout << "Enter Event Description: ";
            getline(cin, event);

            eventHistory.emplace(category, event);
        }
    }

    /**
     * @brief Display all ECU events grouped by category.
     */
    void processData() override
    {
        cout << "\n===== ECU Event History =====\n";

        if(eventHistory.empty())
        {
            cout << "No ECU events available.\n";
            return;
        }

        string currentCategory;

        for(const auto& entry : eventHistory)
        {
            if(entry.first != currentCategory)
            {
                currentCategory = entry.first;

                cout << "\n[" << currentCategory << "]\n";
            }

            cout << " - " << entry.second << endl;
        }

        cout << "\nTotal Events: "
             << eventHistory.size()
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
    ECU* ecu = new ECUEventHistory();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}