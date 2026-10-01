/**
 * @file automatic_tire_inflation_monitoring_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic Tire
 *   Inflation Monitoring System. It monitors
 *   tire pressure and compressor status to
 *   maintain the recommended tire pressure.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 26-07-2026
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
    vector<int> tireData;

public:

    /**
     * @brief Input tire readings
     */
    void inputReadings()
    {
        int n;
        int pressure;
        int compressorStatus;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Tire Pressure (PSI): ";
            cin >> pressure;
            tireData.push_back(pressure);

            cout << "Compressor ON (1=Yes, 0=No): ";
            cin >> compressorStatus;
            tireData.push_back(compressorStatus);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Automatic Tire Inflation Monitoring System
 */
class TireInflationSystem : public Sensor
{
public:

    /**
     * @brief Analyze tire pressure
     */
    void checkStatus() override
    {
        cout << "\n===== Automatic Tire Inflation Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < tireData.size(); i += 2)
        {
            int pressure = tireData[i];
            int compressor = tireData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(pressure < 32 && compressor == 1)
            {
                cout << "Low Tire Pressure! Compressor Inflating Tire ✅" << endl;
            }
            else if(pressure < 32 && compressor == 0)
            {
                cout << "Warning! Low Tire Pressure - Compressor OFF ⚠️" << endl;
            }
            else
            {
                cout << "Tire Pressure Normal 🚗" << endl;
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

    TireInflationSystem tireSystem;

    sensor = &tireSystem;

    tireSystem.inputReadings();

    sensor->checkStatus();

    return 0;
}