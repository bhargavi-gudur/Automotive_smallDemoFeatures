/**
 * @file smart_cabin_air_quality_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Cabin Air
 *   Quality Monitoring System. It monitors
 *   Air Quality Index (AQI) and air purifier
 *   status to maintain healthy cabin air.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 27-07-2026
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
    vector<int> airData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int aqi;
        int purifierStatus;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Cabin AQI: ";
            cin >> aqi;
            airData.push_back(aqi);

            cout << "Air Purifier ON (1=Yes, 0=No): ";
            cin >> purifierStatus;
            airData.push_back(purifierStatus);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Smart Cabin Air Quality Monitoring System
 */
class CabinAirQualitySystem : public Sensor
{
public:

    /**
     * @brief Analyze cabin air quality
     */
    void checkStatus() override
    {
        cout << "\n===== Cabin Air Quality Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < airData.size(); i += 2)
        {
            int aqi = airData[i];
            int purifier = airData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(aqi > 150 && purifier == 1)
            {
                cout << "Poor Air Quality! Air Purifier Activated ✅" << endl;
            }
            else if(aqi > 150 && purifier == 0)
            {
                cout << "Warning! Poor Cabin Air - Purifier OFF ⚠️" << endl;
            }
            else
            {
                cout << "Cabin Air Quality Normal 🚗" << endl;
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

    CabinAirQualitySystem cabinAir;

    sensor = &cabinAir;

    cabinAir.inputReadings();

    sensor->checkStatus();

    return 0;
}