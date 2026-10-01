/**
 * @file adaptive_suspension_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Adaptive Suspension System.
 *   It monitors road condition readings and
 *   adjusts suspension settings.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 30-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> roadConditionReadings;

public:

    /**
     * @brief Input road condition readings
     */
    void inputReadings() {

        int n, value;

        cout << "Enter number of road condition readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter road roughness (0-100): ";
            cin >> value;

            roadConditionReadings.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Adaptive Suspension System
 */
class AdaptiveSuspension : public Sensor {

public:

    /**
     * @brief Analyze road condition
     */
    void checkStatus() override {

        cout << "\n===== Adaptive Suspension Report =====\n";

        for(int value : roadConditionReadings) {

            if(value < 30) {

                cout << value
                     << " -> Smooth Road : Soft Suspension ✅\n";
            }
            else if(value <= 70) {

                cout << value
                     << " -> Normal Road : Medium Suspension 🚗\n";
            }
            else {

                cout << value
                     << " -> Rough Road :