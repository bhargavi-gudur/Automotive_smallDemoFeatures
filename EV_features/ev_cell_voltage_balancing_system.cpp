/**
 * @file ev_cell_voltage_balancing_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an EV Cell Voltage
 *   Balancing System. It monitors individual
 *   cell voltage and balancing status to
 *   maintain battery pack health.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 02-08-2026
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
    vector<float> cellData;

public:

    void inputReadings()
    {
        int n;
        float voltage;
        int balancingStatus;

        cout << "Enter number of cell readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nCell " << i + 1 << endl;

            cout << "Cell Voltage (V): ";
            cin >> voltage;
            cellData.push_back(voltage);

            cout << "Balancing Active (1=Yes, 0=No): ";
            cin >> balancingStatus;
            cellData.push_back(balancingStatus);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief EV Cell Voltage Balancing System
 */
class CellVoltageBalancing : public Sensor
{
public:

    void checkStatus() override
    {
        cout << "\n===== EV Cell Voltage Balancing Report =====\n";

        int cellNumber = 1;

        for(size_t i = 0; i < cellData.size(); i += 2)
        {
            float voltage = cellData[i];
            int balancing = static_cast<int>(cellData[i + 1]);

            cout << "\nCell " << cellNumber++ << endl;

            if(voltage > 4.15 && balancing == 1)
            {
                cout << "Balancing Active - Cell Voltage Reduced ✅" << endl;
            }
            else if(voltage > 4.15 && balancing == 0)
            {
                cout << "High Cell Voltage! Start Balancing ⚠️" << endl;
            }
            else if(voltage < 3.20)
            {
                cout << "Low Cell Voltage - Check Battery 🔋" << endl;
            }
            else
            {
                cout << "Cell Voltage Normal" << endl;
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

    CellVoltageBalancing battery;

    sensor = &battery;

    battery.inputReadings();

    sensor->checkStatus();

    return 0;
}