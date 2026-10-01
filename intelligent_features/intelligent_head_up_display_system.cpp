/**
 * @file intelligent_head_up_display_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Head-Up
 *   Display (HUD) System. It monitors vehicle speed
 *   and navigation alert status to display driving
 *   information on the windshield.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 01-08-2026
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
    vector<int> hudData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int speed;
        int navigationAlert;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Speed (km/h): ";
            cin >> speed;
            hudData.push_back(speed);

            cout << "Navigation Alert (1=Yes, 0=No): ";
            cin >> navigationAlert;
            hudData.push_back(navigationAlert);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Intelligent Head-Up Display System
 */
class HeadUpDisplay : public Sensor
{
public:

    /**
     * @brief Display HUD information
     */
    void checkStatus() override
    {
        cout << "\n===== Head-Up Display Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < hudData.size(); i += 2)
        {
            int speed = hudData[i];
            int alert = hudData[i + 1];

            cout << "\nReading " << reading++ << endl;

            cout << "Display Speed: " << speed << " km/h" << endl;

            if(alert == 1)
            {
                cout << "Navigation Alert Displayed 🧭" << endl;
            }
            else
            {
                cout << "No Navigation Alert" << endl;
            }

            if(speed > 100)
            {
                cout << "Overspeed Warning Displayed ⚠️" << endl;
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

    HeadUpDisplay hud;

    sensor = &hud;

    hud.inputReadings();

    sensor->checkStatus();

    return 0;
}