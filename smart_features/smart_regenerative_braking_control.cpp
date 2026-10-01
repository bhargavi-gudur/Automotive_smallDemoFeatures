/**
 * @file smart_regenerative_braking_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Regenerative
 *   Braking Control System. It monitors brake
 *   pedal position and battery SOC to control
 *   regenerative braking.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 03-08-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor
{
protected:
    vector<int> brakeData;

public:

    void inputReadings()
    {
        int n;
        int brakePosition;
        int batterySOC;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Brake Pedal Position (%): ";
            cin >> brakePosition;
            brakeData.push_back(brakePosition);

            cout << "Battery SOC (%): ";
            cin >> batterySOC;
            brakeData.push_back(batterySOC);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Smart Regenerative Braking System
 */
class RegenerativeBrakingControl : public Sensor
{
public:

    void checkStatus() override
    {
        cout << "\n===== Smart Regenerative Braking Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < brakeData.size(); i += 2)
        {
            int brake = brakeData[i];
            int soc = brakeData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(brake > 20 && soc < 90)
            {
                cout << "Regenerative Braking Enabled ✅" << endl;
            }
            else if(brake > 20 && soc >= 90)
            {
                cout << "Battery Nearly Full - Use Friction Braking ⚠️" << endl;
            }
            else
            {
                cout << "Normal Driving - No Regeneration" << endl;
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

    RegenerativeBrakingControl regen;

    sensor = &regen;

    regen.inputReadings();

    sensor->checkStatus();

    return 0;
}