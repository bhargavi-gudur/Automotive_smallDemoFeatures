/**
 * @file automatic_rain_sensing_window_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic Rain
 *   Sensing Window Control System.
 *   It monitors rain detection and window status
 *   to automatically close the windows.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 21-07-2026
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
    vector<int> rainData;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings()
    {
        int n;
        int rainDetected;
        int windowOpen;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nReading " << i + 1 << endl;

            cout << "Rain Detected (1=Yes, 0=No): ";
            cin >> rainDetected;
            rainData.push_back(rainDetected);

            cout << "Window Open (1=Yes, 0=No): ";
            cin >> windowOpen;
            rainData.push_back(windowOpen);
        }
    }

    /**
     * @brief Pure Virtual Function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Automatic Rain Sensing Window Control
 */
class RainSensingWindowControl : public Sensor
{
public:

    /**
     * @brief Analyze rain and window status
     */
    void checkStatus() override
    {
        cout << "\n===== Automatic Rain Sensing Window Control Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < rainData.size(); i += 2)
        {
            int rain = rainData[i];
            int window = rainData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(rain == 1 && window == 1)
            {
                cout << "Rain Detected! Closing Windows Automatically 🌧️" << endl;
            }
            else if(rain == 1 && window == 0)
            {
                cout << "Windows Already Closed ✅" << endl;
            }
            else
            {
                cout << "No Rain - Normal Operation" << endl;
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

    RainSensingWindowControl rainWindow;

    sensor = &rainWindow;

    rainWindow.inputReadings();

    sensor->checkStatus();

    return 0;
}