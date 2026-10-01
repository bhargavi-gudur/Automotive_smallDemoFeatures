/**
 * @file can_message_scheduler.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive CAN Message Scheduler.
 *
 *   The program stores CAN messages in a queue and
 *   processes them in FIFO (First In, First Out) order.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL queue
 *
 * @date 08-08-2026
 */

#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for an ECU system.
 */
class ECU
{
public:

    /**
     * @brief Accepts input data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Processes ECU data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class CANMessageScheduler
 * @brief Manages automotive CAN messages using STL queue.
 */
class CANMessageScheduler : public ECU
{
private:

    /**
     * @brief Queue for storing CAN messages.
     *
     * queue follows FIFO:
     * First message inserted = First message processed.
     */
    queue<string> messages;

public:

    /**
     * @brief Accept CAN messages from the user.
     */
    void inputData() override
    {
        int n;
        string message;

        cout << "Enter number of CAN messages: ";
        cin >> n;

        cin.ignore();

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter CAN message "
                 << i + 1 << ": ";

            getline(cin, message);

            messages.push(message);
        }
    }

    /**
     * @brief Process CAN messages in FIFO order.
     */
    void processData() override
    {
        cout << "\n===== CAN Message Scheduler =====\n";

        if(messages.empty())
        {
            cout << "No CAN messages available.\n";
            return;
        }

        while(!messages.empty())
        {
            cout << "Processing CAN Message: "
                 << messages.front()
                 << endl;

            messages.pop();
        }

        cout << "\nAll CAN messages processed successfully.\n";
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
    ECU* ecu = new CANMessageScheduler();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}