/**
 * @file emergency_event_management.cpp
 * @author Gandla Bhargavi
 * @brief Emergency Event Management using priority_queue
 * @date 07-08-2026
 */

#include <iostream>
#include <queue>
using namespace std;

/**
 * @brief Base Class
 */
class Event
{
protected:
    priority_queue<int> eventPriority;

public:

    virtual void inputData() = 0;

    virtual void processEvents() = 0;

    virtual ~Event() {}
};

/**
 * @brief Emergency Event Manager
 */
class EmergencyEventManager : public Event
{
public:

    void inputData() override
    {
        int n, priority;

        cout << "Enter Number of Events: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "Enter Event Priority (1-100): ";
            cin >> priority;

            eventPriority.push(priority);
        }
    }

    void processEvents() override
    {
        cout << "\n===== Emergency Event Report =====\n";

        while(!eventPriority.empty())
        {
            int priority = eventPriority.top();

            cout << "Processing Priority : "
                 << priority;

            if(priority >= 90)
            {
                cout << " -> Airbag Deployment ⚠️";
            }
            else if(priority >= 70)
            {
                cout << " -> Brake System Fault";
            }
            else if(priority >= 50)
            {
                cout << " -> Engine Warning";
            }
            else
            {
                cout << " -> Information Event";
            }

            cout << endl;

            eventPriority.pop();
        }
    }
};

/**
 * @brief Main Function
 */
int main()
{
    Event *event;

    EmergencyEventManager manager;

    event = &manager;

    event->inputData();

    event->processEvents();

    return 0;
}