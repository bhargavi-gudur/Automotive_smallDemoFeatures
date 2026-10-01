/**
 * @file ecu_diagnostic_event_history.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Event History
 *   using the STL stack container.
 *
 *   The system stores diagnostic events and retrieves
 *   the most recently stored event first.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL stack
 *   - LIFO (Last In, First Out)
 *
 * @date 13-08-2026
 */

#include <iostream>
#include <stack>
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
 * @class DiagnosticEventHistory
 * @brief Manages ECU diagnostic events using a stack.
 */
class DiagnosticEventHistory : public ECU
{
private:

    /**
     * @brief Stores diagnostic events.
     *
     * stack follows LIFO:
     * Last event inserted = First event processed.
     */
    stack<string> diagnosticEvents;

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
            cout << "Enter Diagnostic Event "
                 << i + 1 << ": ";

            getline(cin, event);

            diagnosticEvents.push(event);
        }
    }

    /**
     * @brief Display diagnostic events in LIFO order.
     */
    void processData() override
    {
        cout << "\n===== ECU Diagnostic Event History =====\n";

        if(diagnosticEvents.empty())
        {
            cout << "No diagnostic events available.\n";
            return;
        }

        int eventNumber = 1;

        while(!diagnosticEvents.empty())
        {
            cout << "Event " << eventNumber++
                 << ": "
                 << diagnosticEvents.top()
                 << endl;

            diagnosticEvents.pop();
        }

        cout << "\nAll diagnostic events processed.\n";
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
    ECU* ecu = new DiagnosticEventHistory();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}