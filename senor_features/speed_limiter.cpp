/**
 * @file speed_limiter.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates a Speed Limiter System.
 *   It stores vehicle speed data using STL vector
 *   and checks whether speed exceeds the limit.
 *   Demonstrates OOP and STL concepts in C++.
 * @date 24-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Class for Speed Limiter System
 */
class SpeedLimiter {

private:

    vector<int> speedData;
    int speedLimit;

public:

    /**
     * @brief Initialize speed limit
     */
    void initLimit() {

        cout << "Enter Speed Limit: ";
        cin >> speedLimit;
    }

    /**
     * @brief Store speed data
     */
    void storeSpeed() {

        int n, speed;

        cout << "Enter number of speed readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter speed: ";
            cin >> speed;

            speedData.push_back(speed);
        }
    }

    /**
     * @brief Display stored speed data
     */
    void showSpeedData() {

        cout << "\nStored Speed Data:\n";

        for(int value : speedData) {

            cout << value << " km/h\n";
        }
    }

    /**
     * @brief Check speed limit
     */
    void checkLimit() {

        cout << "\n===== Speed Status =====\n";

        for(int value : speedData) {

            if(value > speedLimit) {

                cout << value
                     << " km/h -> Limit Exceeded ⚠️\n";
            }
            else {

                cout << value
                     << " km/h -> Safe Speed ✅\n";
            }
        }
    }
};

/**
 * @brief Main function
 */
int main() {

    SpeedLimiter s;

    cout << "===== Vehicle Speed Limiter System =====\n";

    s.initLimit();

    s.storeSpeed();

    s.showSpeedData();

    s.checkLimit();

    return 0;
}