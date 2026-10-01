/**
 * @file intelligent_vehicle_diagnostics_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Vehicle
 *   Diagnostics System. It monitors Diagnostic
 *   Trouble Codes (DTC) and Malfunction Indicator
 *   Lamp (MIL) status to determine vehicle health.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 30-07-2026
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
    vector<int> diagnosticData;

public:

    /**
     * @brief Input diagnostic readings
     */
    void inputReadings()
    {
        int n;
        int dtcPresent;
        int milStatus;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Diagnostic Trouble Code Present (1=Yes, 0=No): ";
            cin >> dtcPresent;
            diagnosticData.push_back(dtcPresent);

            cout << "Malfunction Indicator Lamp ON (1=Yes, 0=No): ";
            cin >> milStatus;
            diagnosticData.push_back(milStatus);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Intelligent Vehicle Diagnostics System
 */
class VehicleDiagnostics : public Sensor
{
public:

    /**
     * @brief Analyze vehicle diagnostic status
     */
    void checkStatus() override
    {
        cout << "\n===== Vehicle Diagnostics Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < diagnosticData.size(); i += 2)
        {
            int dtc = diagnosticData[i];
            int mil = diagnosticData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(dtc == 1 && mil == 1)
            {
                cout << "Fault Detected! Check Engine Light ON ⚠️" << endl;
            }
            else if(dtc == 1 && mil == 0)
            {
                cout << "Stored Diagnostic Code - Service Recommended" << endl;
            }
            else
            {
                cout << "Vehicle Operating Normally ✅" << endl;
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

    VehicleDiagnostics diagnostics;

    sensor = &diagnostics;

    diagnostics.inputReadings();

    sensor->checkStatus();

    return 0;
}