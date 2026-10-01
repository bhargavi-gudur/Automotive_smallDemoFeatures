/**
 * @file smart_wiper_control.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Smart Wiper Control System.
 *   It monitors rain intensity and automatically
 *   controls the windshield wiper speed.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 06-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> rainIntensity;

public:

    /**
     * @brief Input rain sensor readings
     */
    void inputReadings() {

        int n;
        int value;

        cout << "Enter number of rain readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter rain intensity (0-100): ";
            cin >> value;

            rainIntensity.push_back(value);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Smart Wiper Control System
 */
class SmartWiperSystem : public Sensor {

public:

    /**
     * @brief Check rain intensity and control wiper
     */
    void checkStatus() override {

        cout << "\n===== Smart Wiper Report =====\n";

        for(int value : rainIntensity) {

            if(value == 0) {

                cout << value
                     << " -> No Rain | Wiper OFF ✅\n";
            }
            else if(value <= 30) {

                cout << value
                     << " -> Light Rain | Wiper LOW Speed\n";
            }
            else if(value <= 70) {

                cout << value
                     << " -> Moderate Rain | Wiper MEDIUM Speed\n";
            }
            else {

                cout << value
                     << " -> Heavy Rain | Wiper HIGH Speed ⚠️\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    SmartWiperSystem wiper;

    sensor = &wiper;

    wiper.inputReadings();

    sensor->checkStatus();

    return 0;
}