/**
 * @file intelligent_speed_adaptation.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Speed
 *   Adaptation (ISA) System.
 *   It compares vehicle speed with the road
 *   speed limit and generates warnings.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 28-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> vehicleSpeeds;

public:

    /**
     * @brief Input vehicle speed readings
     */
    void inputReadings() {

        int n, speed;

        cout << "Enter number of speed readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter vehicle speed (km/h): ";
            cin >> speed;

            vehicleSpeeds.push_back(speed);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Intelligent Speed Adaptation System
 */
class IntelligentSpeedAdaptation : public Sensor {

private:

    int speedLimit;

public:

    /**
     * @brief Input road speed limit
     */
    void setSpeedLimit() {

        cout << "Enter road speed limit (km/h): ";
        cin >> speedLimit;
    }

    /**
     * @brief Compare speed with speed limit
     */
    void checkStatus() override {

        cout << "\n===== Intelligent Speed Adaptation Report =====\n";

        for(int speed : vehicleSpeeds) {

            if(speed > speedLimit) {

                cout << speed
                     << " km/h -> Reduce Speed! Limit Exceeded ⚠️\n";
            }
            else if(speed == speedLimit) {

                cout << speed
                     << " km/h -> Driving at Speed Limit ✅\n";
            }
            else {

                cout << speed
                     << " km/h -> Safe Speed\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    IntelligentSpeedAdaptation isa;

    sensor = &isa;

    isa.setSpeedLimit();

    isa.inputReadings();

    sensor->checkStatus();

    return 0;
}