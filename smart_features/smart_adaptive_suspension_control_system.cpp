/**
 * @file smart_adaptive_suspension_control_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Adaptive
 *   Suspension Control System. It monitors
 *   vehicle speed and road condition to
 *   automatically adjust suspension stiffness.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 31-07-2026
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
    vector<int> suspensionData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int vehicleSpeed;
        int roadCondition;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Speed (km/h): ";
            cin >> vehicleSpeed;
            suspensionData.push_back(vehicleSpeed);

            cout << "Road Condition (0=Smooth, 1=Rough): ";
            cin >> roadCondition;
            suspensionData.push_back(roadCondition);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Smart Adaptive Suspension Control System
 */
class AdaptiveSuspension : public Sensor
{
public:

    /**
     * @brief Analyze suspension requirements
     */
    void checkStatus() override
    {
        cout << "\n===== Adaptive Suspension Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < suspensionData.size(); i += 2)
        {
            int speed = suspensionData[i];
            int road = suspensionData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(road == 1 && speed > 60)
            {
                cout << "Adjust Suspension to Soft Mode ✅" << endl;
            }
            else if(road == 0 && speed > 80)
            {
                cout << "Adjust Suspension to Sport Mode 🚗" << endl;
            }
            else
            {
                cout << "Normal Suspension Mode" << endl;
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

    AdaptiveSuspension suspension;

    sensor = &suspension;

    suspension.inputReadings();

    sensor->checkStatus();

    return 0;
}