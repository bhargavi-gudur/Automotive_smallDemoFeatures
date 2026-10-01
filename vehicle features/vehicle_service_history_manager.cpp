/**
 * @file vehicle_service_history_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates a Vehicle Service and Maintenance
 *   History Manager using the STL list container.
 *
 *   The system stores service records, displays
 *   maintenance history, searches for a service
 *   record, and removes an obsolete record.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL list
 *   - STL find algorithm
 *
 * @date 17-08-2026
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

/**
 * @class VehicleSystem
 * @brief Abstract base class for vehicle systems.
 */
class VehicleSystem
{
public:

    /**
     * @brief Accept maintenance data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Process maintenance records.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~VehicleSystem() = default;
};

/**
 * @class ServiceHistoryManager
 * @brief Manages vehicle maintenance records.
 */
class ServiceHistoryManager : public VehicleSystem
{
private:

    /**
     * @brief Stores vehicle service records.
     */
    list<string> serviceHistory;

public:

    /**
     * @brief Accept service records from the user.
     */
    void inputData() override
    {
        int n;
        string service;

        cout << "Enter number of service records: ";
        cin >> n;

        cin.ignore();

        for(int i = 0; i < n; ++i)
        {
            cout << "Enter service record "
                 << i + 1 << ": ";

            getline(cin, service);

            serviceHistory.push_back(service);
        }
    }

    /**
     * @brief Display and manage service history.
     */
    void processData() override
    {
        cout << "\n===== Vehicle Service History =====\n";

        if(serviceHistory.empty())
        {
            cout << "No service records available.\n";
            return;
        }

        int recordNumber = 1;

        for(const string& service : serviceHistory)
        {
            cout << "Record "
                 << recordNumber++
                 << ": "
                 << service
                 << endl;
        }

        /*
         * Search for a specific service record.
         */
        const string searchRecord =
            "Engine Oil Service";

        auto result =
            find(serviceHistory.begin(),
                 serviceHistory.end(),
                 searchRecord);

        cout << "\nSearching for: "
             << searchRecord
             << endl;

        if(result != serviceHistory.end())
        {
            cout << "Service Record Found.\n";
        }
        else
        {
            cout << "Service Record Not Found.\n";
        }

        /*
         * Remove an obsolete service record.
         */
        const string obsoleteRecord =
            "Old Battery Replacement";

        serviceHistory.remove(obsoleteRecord);

        cout << "\nUpdated Service History:\n";

        recordNumber = 1;

        for(const string& service : serviceHistory)
        {
            cout << "Record "
                 << recordNumber++
                 << ": "
                 << service
                 << endl;
        }
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    VehicleSystem* system =
        new ServiceHistoryManager();

    system->inputData();

    system->processData();

    delete system;

    return 0;
}