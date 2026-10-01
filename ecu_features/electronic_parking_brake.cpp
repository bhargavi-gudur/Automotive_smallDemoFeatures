/**
 * @file electronic_parking_brake.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Electronic Parking Brake (EPB) System.
 *   It checks vehicle speed and brake switch status
 *   before applying or releasing the parking brake.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 11-07-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> brakeData;

public:

    /**
     * @brief Input brake information
     */
    void inputReadings() {

        int n;
        int speed, brakeSwitch;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "\nReading " << i + 1 << endl;

            cout << "Vehicle Speed (km/h): ";
            cin >> speed;

            brakeData.push_back(speed);

            cout << "Parking Brake Switch (1=ON, 0=OFF): ";
            cin >> brakeSwitch;

            brakeData.push_back(brakeSwitch);
        }
    }

    /**
     * @brief Pure virtual function
     */
    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Electronic Parking Brake System
 */
class ElectronicParkingBrake : public Sensor {

public:

    /**
     * @brief Analyze EPB conditions
     */
    void checkStatus() override {

        cout << "\n===== Electronic Parking Brake Report =====\n";

        int reading = 1;

        for(size_t i = 0; i < brakeData.size(); i += 2) {

            int speed = brakeData[i];
            int brakeSwitch = brakeData[i + 1];

            cout << "\nReading " << reading++ << endl;

            if(speed == 0 && brakeSwitch == 1) {

                cout << "Parking Brake Applied ✅\n";
            }
            else if(speed > 0 && brakeSwitch == 1) {

                cout << "Cannot Apply Parking Brake While Moving ⚠️\n";
            }
            else {

                cout << "Parking Brake Released\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    ElectronicParkingBrake epb;

    sensor = &epb;

    epb.inputReadings();

    sensor->checkStatus();

    return 0;
}