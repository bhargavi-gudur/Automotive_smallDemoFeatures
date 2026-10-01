/**
 * @file smart_ignition_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Ignition System.
 *   It checks smart key detection and brake pedal
 *   status before allowing engine start.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 04-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> ignitionStatus;

public:

    /**
     * @brief Input ignition status
     */
    void inputReadings() {

        int n, status;

        cout << "Enter number of ignition attempts: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nAttempt " << i + 1 << endl;

            cout << "Smart Key Detected? (1=Yes, 0=No): ";
            cin >> status;

            ignitionStatus.push_back(status);

            cout << "Brake Pedal Pressed? (1=Yes, 0=No): ";
            cin >> status;

            ignitionStatus.push_back(status);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Smart Ignition System
 */
class SmartIgnition : public Sensor {

public:

    /**
     * @brief Check ignition conditions
     */
    void checkStatus() override {

        cout << "\n===== Smart Ignition Report =====\n";

        int attempt = 1;

        for(size_t i = 0; i < ignitionStatus.size(); i += 2) {

            cout << "\nAttempt " << attempt++ << endl;

            if(