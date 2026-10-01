/**
 * @file electronic_stability_program.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Electronic Stability
 *   Program (ESP). It monitors steering angle and
 *   wheel slip percentage to determine whether
 *   stability control should be activated.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 20-07-2026
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
    vector<int> espData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int steeringAngle;
        int wheelSlip;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Enter Steering Angle (degrees): ";
            cin >> steeringAngle;
            espData.push_back(steeringAngle);

            cout << "Enter Wheel Slip (%): ";
            cin >> wheelSlip;
            espData.push_back(wheelSlip);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Electronic Stability Program
 */
class ElectronicStabilityProgram : public Sensor
{
public:

    /**
     * @brief Analyze vehicle stability
     */
    void checkStatus() override
    {
        cout << "\n===== Electronic Stability Program Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < espData.size(); i += 2)
        {
            int steeringAngle = espData[i];
            int wheelSlip = espData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(steeringAngle > 30 && wheelSlip > 20)
            {
                cout << "ESP Activated! Applying Brake to Individual Wheels ✅" << endl;
            }
            else if(wheelSlip > 20)
            {
                cout << "Wheel Slip Detected! Stability Correction Required ⚠️" << endl;
            }
            else
            {
                cout << "Vehicle Stable 🚗" << endl;
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

    ElectronicStabilityProgram esp;

    sensor = &esp;

    esp.inputReadings();

    sensor->checkStatus();

    return 0;
}