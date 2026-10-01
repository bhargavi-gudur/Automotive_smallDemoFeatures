/**
 * @file smart_ev_charging_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates a Smart EV Charging Manager.
 *
 *   Features:
 *   - Current battery SoC
 *   - Target battery SoC
 *   - Battery capacity
 *   - Charging power
 *   - Required energy calculation
 *   - Estimated charging time
 *   - Start/stop charging
 *   - Charging status report
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL chrono
 *   - STL optional
 *   - iomanip
 *
 * @date 28-08-2026
 */

#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

using namespace std;
using namespace chrono;

/**
 * @class EVSystem
 * @brief Abstract base class for an EV system.
 */
class EVSystem
{
public:

    /**
     * @brief Accept EV charging information.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process charging information.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~EVSystem() = default;
};

/**
 * @class SmartChargingManager
 * @brief Manages smart charging of an electric vehicle.
 */
class SmartChargingManager : public EVSystem
{
private:

    double batteryCapacity{};
    double currentSoC{};
    double targetSoC{};
    double chargingPower{};

    bool charging{false};

    /**
     * @brief Stores charging start time when charging is active.
     */
    optional<system_clock::time_point> chargingStartTime;

public:

    /**
     * @brief Accept charging parameters.
     */
    void inputData() override
    {
        cout << "===== Smart EV Charging Setup =====\n";

        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;

        cout << "Enter Current SoC (%): ";
        cin >> currentSoC;

        cout << "Enter Target SoC (%): ";
        cin >> targetSoC;

        cout << "Enter Charging Power (kW): ";
        cin >> chargingPower;
    }

    /**
     * @brief Validate charging parameters.
     */
    bool validateData() const
    {
        if(batteryCapacity <= 0)
        {
            return false;
        }

        if(currentSoC < 0 || currentSoC > 100)
        {
            return false;
        }

        if(targetSoC < 0 || targetSoC > 100)
        {
            return false;
        }

        if(targetSoC <= currentSoC)
        {
            return false;
        }

        if(chargingPower <= 0)
        {
            return false;
        }

        return true;
    }

    /**
     * @brief Calculate required energy in kWh.
     */
    double calculateRequiredEnergy() const
    {
        const double socDifference =
            targetSoC - currentSoC;

        return batteryCapacity *
               socDifference / 100.0;
    }

    /**
     * @brief Calculate ideal charging time in hours.
     */
    double calculateChargingHours() const
    {
        return calculateRequiredEnergy()
               / chargingPower;
    }

    /**
     * @brief Start EV charging.
     */
    void startCharging()
    {
        charging = true;

        chargingStartTime =
            system_clock::now();

        cout << "\nCharging Started.\n";
    }

    /**
     * @brief Stop EV charging.
     */
    void stopCharging()
    {
        charging = false;

        chargingStartTime.reset();

        cout << "\nCharging Stopped.\n";
    }

    /**
     * @brief Generate charging report.
     */
    void processData() override
    {
        cout << fixed
             << setprecision(2);

        cout << "\n===== Smart EV Charging Report =====\n";

        if(!validateData())
        {
            cout << "Invalid charging parameters.\n";
            return;
        }

        const double requiredEnergy =
            calculateRequiredEnergy();

        const double chargingHours =
            calculateChargingHours();

        cout << "Battery Capacity : "
             << batteryCapacity
             << " kWh\n";

        cout << "Current SoC      : "
             << currentSoC
             << " %\n";

        cout << "Target SoC       : "
             << targetSoC
             << " %\n";

        cout << "Charging Power   : "
             << chargingPower
             << " kW\n";

        cout << "Required Energy  : "
             << requiredEnergy
             << " kWh\n";

        cout << "Estimated Time   : "
             << chargingHours
             << " hours\n";

        cout << "Charging Status  : ";

        if(charging)
        {
            cout << "ACTIVE";
        }
        else
        {
            cout << "READY";
        }

        cout << "\n";

        /*
         * Automatically start charging.
         */
        if(!charging)
        {
            startCharging();
        }

        cout << "\nFinal Status     : "
             << "SMART CHARGING ACTIVE\n";
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism.
 */
int main()
{
    EVSystem* ev =
        new SmartChargingManager();

    ev->inputData();

    ev->processData();

    delete ev;

    return 0;
}