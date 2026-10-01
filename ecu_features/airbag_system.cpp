/**
 * @file airbag_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Airbag Control System.
 *   It checks vehicle speed and collision impact
 *   to decide whether airbags should deploy.
 *   Demonstrates OOP concepts in C++.
 * @date 23-05-2026
 * @update: code updated by gandla bhargavi 24-05-2026
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

/**
 * @brief Class for Airbag System
 */
class AirbagSystem {

private:
    int speed;
    int impactForce;
    bool seatBelt;

public:

    /**
     * @brief Input vehicle details
     */
    AirbagSystem()
    {

        cout << "Enter Vehicle Speed (km/h): ";
        cin >> speed;

        cout << "Enter Collision Impact Force: ";
        cin >> impactForce;

        cout << "Seat Belt Worn? (1 = Yes, 0 = No): ";
        cin >> seatBelt;
    }

    /**
     * @brief Check airbag deployment
     */
    void checkAirbag() {

        cout << "\n===== Airbag Status =====\n";

        if(speed > 40 && impactForce > 50) {

            cout << "Collision Detected!\n";

            if(seatBelt) {

                cout << "Airbag Deployed Successfully 🛑\n";
            }
            else {

                cout << "Warning! Seat Belt Not Worn\n";
                cout << "Airbag Deployed with High Risk ⚠️\n";
            }
        }
        else {

            cout << "No Airbag Deployment Needed\n";
        }
    }
};

/**
 * @brief Main function 
 */
int main() {

    AirbagSystem objAirbagSystem;

    cout << "===== Vehicle Airbag Control System =====\n";

    objAirbagSystem.checkAirbag();

    return 0;
}