/**
 * @file smart_door_lock_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Door Lock System.
 *   It monitors vehicle speed and door status to
 *   automatically lock or unlock vehicle doors.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 20-07-2026
 */

#include<iostream>
#include<vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor
{
protected:
    vector<int> doorData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int speed;
        int doorLocked;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Vehicle Speed (km/h): ";
            cin >> speed;
            doorData.push_back(speed);

            cout << "Door Locked (1=Yes, 0=No): ";
            cin >> doorLocked;
            doorData.push_back(doorLocked);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Smart Door Lock System
 */
class SmartDoorLock : public Sensor
{
public:

    /**
     * @brief Analyze door lock status
     */
    void checkStatus() override
    {
        cout << "\n===== Smart Door Lock Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < doorData.size(); i += 2)
        {
            int speed = doorData[i];
            int locked = doorData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(speed > 20 && locked == 0)
            {
                cout << "Auto Lock Activated ✅" << endl;
            }
            else if(speed == 0 && locked == 1)
            {
                cout << "Vehicle Parked - Unlock Doors 🚪" << endl;
            }
            else
            {
                cout << "Door Status Normal" << endl;
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main()
{
    Sensor *sensor;

    SmartDoorLock doorLock;

    sensor = &doorLock;

    doorLock.inputReadings();

    sensor->checkStatus();

    return 0;
}