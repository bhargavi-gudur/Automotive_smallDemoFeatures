/**
 * @file intelligent_rear_cross_traffic_alert.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Rear
 *   Cross Traffic Alert (RCTA) System.
 *   It monitors the distance of approaching
 *   vehicles and reverse gear status to
 *   generate collision warnings.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 25-07-2026
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
    vector<int> trafficData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int distance;
        int reverseGear;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Approaching Vehicle Distance (m): ";
            cin >> distance;
            trafficData.push_back(distance);

            cout << "Reverse Gear Engaged (1=Yes, 0=No): ";
            cin >> reverseGear;
            trafficData.push_back(reverseGear);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Rear Cross Traffic Alert System
 */
class RearCrossTrafficAlert : public Sensor
{
public:

    /**
     * @brief Analyze traffic conditions
     */
    void checkStatus() override
    {
        cout << "\n===== Rear Cross Traffic Alert Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < trafficData.size(); i += 2)
        {
            int distance = trafficData[i];
            int reverseGear = trafficData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(reverseGear == 1 && distance < 10)
            {
                cout << "Collision Warning! Vehicle Approaching Behind ⚠️" << endl;
            }
            else if(reverseGear == 1 && distance >= 10)
            {
                cout << "Reverse Path Clear ✅" << endl;
            }
            else
            {
                cout << "System Monitoring - Vehicle Not Reversing" << endl;
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

    RearCrossTrafficAlert rcta;

    sensor = &rcta;

    rcta.inputReadings();

    sensor->checkStatus();

    return 0;
}