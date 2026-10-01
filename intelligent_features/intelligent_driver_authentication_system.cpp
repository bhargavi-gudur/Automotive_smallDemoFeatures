/**
 * @file intelligent_driver_authentication_system.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates an Intelligent Driver
 *   Authentication System. It verifies the
 *   driver's fingerprint and smart key before
 *   allowing the engine to start.
 *   Demonstrates Encapsulation, Inheritance,
 *   Abstraction, Polymorphism, and STL vector.
 * @date 05-08-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor
{
protected:
    vector<int> authenticationData;

public:

    void inputReadings()
    {
        int n;
        int fingerprintVerified;
        int smartKeyDetected;

        cout << "Enter number of authentication attempts: ";
        cin >> n;

        for(int i = 0; i < n; i++)
        {
            cout << "\nAttempt " << i + 1 << endl;

            cout << "Fingerprint Verified (1=Yes, 0=No): ";
            cin >> fingerprintVerified;
            authenticationData.push_back(fingerprintVerified);

            cout << "Smart Key Detected (1=Yes, 0=No): ";
            cin >> smartKeyDetected;
            authenticationData.push_back(smartKeyDetected);
        }
    }

    virtual void checkStatus() = 0;

    virtual ~Sensor(){}
};

/**
 * @brief Driver Authentication System
 */
class DriverAuthentication : public Sensor
{
public:

    void checkStatus() override
    {
        cout << "\n===== Driver Authentication Report =====\n";

        int attempt = 1;

        for(size_t i = 0; i < authenticationData.size(); i += 2)
        {
            int fingerprint = authenticationData[i];
            int smartKey = authenticationData[i + 1];

            cout << "\nAttempt " << attempt++ << endl;

            if(fingerprint == 1 && smartKey == 1)
            {
                cout << "Authentication Successful - Engine Start Enabled ✅" << endl;
            }
            else if(fingerprint == 0)
            {
                cout << "Access Denied - Invalid Fingerprint ⚠️" << endl;
            }
            else
            {
                cout << "Smart Key Not Detected ⚠️" << endl;
            }
        }
    }
};

/**
 * @brief Main Function
 */
int main()
{
    Sensor *sensor;

    DriverAuthentication auth;

    sensor = &auth;

    auth.inputReadings();

    sensor->checkStatus();

    return 0;
}