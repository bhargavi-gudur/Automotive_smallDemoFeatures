/**
 * @file driver_attention_monitoring.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Driver Attention
 *   Monitoring System.
 *   It monitors driver attention score and
 *   steering activity to generate safety alerts.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 17-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> attentionData;

public:

    /**
     * @brief Input driver monitoring readings
     */
    void inputReadings() {

        int n;
        int attentionScore;
        int steeringActive;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Attention Score (0-100): ";
            cin >> attentionScore;
            attentionData.push_back(attentionScore);

            cout << "Steering Activity (1=Active, 0=Inactive): ";
            cin >> steeringActive;
            attentionData.push_back(steeringActive);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Driver Attention Monitoring System
 */
class DriverAttentionMonitoring : public Sensor {

public:

    /**
     * @brief Analyze driver attention
     */
    void checkStatus() override {

        cout << "\n===== Driver Attention Monitoring Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < attentionData.size(); i += 2) {

            int attention = attentionData[i];
            int steering = attentionData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(attention < 40 && steering == 0) {

                cout << "Driver Drowsy! Take a Break ⚠️\n";
            }
            else if(attention < 70) {

                cout << "Driver Attention Reduced 🚗\n";
            }
            else {

                cout << "Driver Alert ✅\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    DriverAttentionMonitoring monitor;

    sensor = &monitor;

    monitor.inputReadings();

    sensor->checkStatus();

    return 0;
}