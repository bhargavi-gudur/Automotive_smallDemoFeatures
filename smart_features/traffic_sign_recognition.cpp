/**
 * @file traffic_sign_recognition.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Traffic Sign Recognition System.
 *   It processes detected traffic sign codes and
 *   displays the corresponding action.
 *   Demonstrates Inheritance, Polymorphism,
 *   and STL vector in C++.
 * @date 22-06-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<int> signCodes;

public:

    void inputReadings() {

        int n, code;

        cout << "Enter number of detected signs: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter sign code (1=STOP, 2=Speed40, 3=Speed60, 4=School Zone): ";
            cin >> code;

            signCodes.push_back(code);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor() {}
};

/**
 * @brief Traffic Sign Recognition Class
 */
class TrafficSignRecognition : public Sensor {

public:

    void checkStatus() override {

        cout << "\n===== Traffic Sign Report =====\n";

        for(int code : signCodes) {

            switch(code) {

                case 1:
                    cout << "STOP Sign Detected 🛑\n";
                    break;

                case 2:
                    cout << "Speed Limit 40 km/h 🚗\n";
                    break;

                case 3:
                    cout << "Speed Limit 60 km/h 🚗\n";
                    break;

                case 4:
                    cout << "School Zone Detected ⚠️\n";
                    break;

                default:
                    cout << "Unknown Traffic Sign\n";
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main() {

    Sensor* sensor;

    TrafficSignRecognition tsr;

    sensor = &tsr;

    tsr.inputReadings();

    sensor->checkStatus();

    return 0;
}