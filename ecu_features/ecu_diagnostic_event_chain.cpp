/**
 * @file ecu_diagnostic_event_chain.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Event Chain.
 *
 *   The system stores diagnostic events using an STL
 *   forward_list. Events can be added and processed
 *   sequentially with low memory overhead.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL forward_list
 *   - STL find algorithm
 *
 * @date 16-08-2026
 */

#include <algorithm>
#include <forward_list>
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
     * @brief Accept diagnostic events.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process diagnostic events.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class DiagnosticEventChain
 * @brief Maintains ECU diagnostic events using forward_list.
 */
class DiagnosticEventChain : public ECU
{
private:

    /**
     * @brief Stores diagnostic events.
     */
    forward_list<string> events;

public:

    /**
     * @brief Accept diagnostic events from the user.
     */
    void inputData() override
    {
        int n;
        string event;

        cout << "Enter number of diagnostic events: ";
        cin >> n;

        cin.ignore();

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter diagnostic event "
                 << i + 1 << ": ";

            getline(cin, event);

            /*
             * Add each new event to the front
             * of the forward_list.
             */
            events.push_front(event);
        }
    }

    /**
     * @brief Process and display diagnostic events.
     */
    void processData() override
    {
        cout << "\n===== ECU Diagnostic Event Chain =====\n";

        if(events.empty())
        {
            cout << "No diagnostic events available.\n";
            return;
        }

        int eventNumber = 1;

        for(const string& event : events)
        {
            cout << "Event "
                 << eventNumber++
                 << ": "
                 << event
                 << endl;
        }

        /*
         * Search for a specific diagnostic event.
         */
        const string searchEvent = "Engine Overheating";

        auto result =
            find(events.begin(),
                 events.end(),
                 searchEvent);

        cout << "\nSearching for: "
             << searchEvent
             << endl;

        if(result != events.end())
        {
            cout << "Event Found: ECU requires inspection.\n";
        }
        else
        {
            cout << "Event Not Found.\n";
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
        new DiagnosticEventChain();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}