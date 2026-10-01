/**
 * @file automatic_high_beam_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Automatic High Beam
 *   Control System.
 *   It monitors ambient light and oncoming vehicle
 *   detection to control headlight beams.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 07-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> lightReadings;

public:

    /**
     * @brief Input ambient light readings
     */
    void inputReadings() {

        int n, value;

        cout << "Enter number of light readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Ambient Light (0-100): ";
            cin >> value;

            lightReadings.push_back(value);

            cout << "Oncoming Vehicle (1=Yes, 0=No): ";
            cin >> value;

            lightReadings.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Automatic High Beam Control System
 */
class HighBeamControl : public Sensor {

public:

    /**
     * @brief Analyze lighting conditions
     */
    void checkStatus() override {

        cout << "\n===== Automatic High Beam Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < lightReadings.size(); i += 2) {

            cout << "\nReading " << reading++ << endl;

            int ambientLight = lightReadings[i];
            int oncomingVehicle = lightReadings[i