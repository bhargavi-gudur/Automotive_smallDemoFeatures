/**
 * @file smart_blind_spot_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Blind Spot
 *   Monitoring System. It monitors radar distance
 *   and turn indicator status to detect vehicles
 *   in the blind spot.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 06-08-2026
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
    vector<int> blindSpotData;

public:

    void inputReadings()
    {
        int n;
        int distance;
        int indicator;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Distance (m): ";
            cin >> distance;
            blindSpotData.push_back(distance);

            cout << "Turn Indicator ON (1=Yes, 0=No): ";
            cin >> indicator;
            blindSpotData.push_back(indicator);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Smart Blind Spot Monitoring System
 */
class BlindSpotMonitoring : public Sensor
{
public:

    void checkStatus() override
    {
        cout << "\n===== Blind Spot Monitoring Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < blindSpotData.size(); i += 2)
        {
            int distance = blindSpotData[i];
            int indicator = blindSpotData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(distance <= 5 && indicator == 1)
            {
                cout << "Blind Spot Warning! Lane Change Not Safe ⚠️" << endl;
            }
            else if(distance <= 5)
            {
                cout << "Vehicle Detected in Blind Spot 🚗" << endl;
            }
            else
            {
                cout << "Blind Spot Clear ✅" << endl;
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

    BlindSpotMonitoring bsm;

    sensor = &bsm;

    bsm.inputReadings();

    sensor->checkStatus();

    return 0;
}