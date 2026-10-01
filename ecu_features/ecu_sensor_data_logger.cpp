/**
 * @file ecu_sensor_data_logger.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates a real-time automotive ECU Sensor Data Logger.
 *
 *   The system stores sensor ID, sensor value, and sensor
 *   status as a single record using std::tuple.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL vector
 *   - STL tuple
 *   - Structured sensor records
 *
 * @date 20-08-2026
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Accept sensor data.
     */
    virtual void inputData() = 0;

    /**
     * @brief Analyze sensor data.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class ECUSensorDataLogger
 * @brief Logs and analyzes ECU sensor data.
 */
class ECUSensorDataLogger : public ECU
{
private:

    /**
     * @brief
     * Tuple structure:
     *
     * 1. Sensor ID
     * 2. Sensor Value
     * 3. Sensor Status
     */
    using SensorRecord =
        tuple<string, float, string>;

    vector<SensorRecord> sensorRecords;

public:

    /**
     * @brief Accept sensor records from the user.
     */
    void inputData() override
    {
        int n;

        cout << "Enter number of sensor records: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            string sensorID;
            float value;
            string status;

            cout << "\nSensor " << i + 1 << endl;

            cout << "Enter Sensor ID: ";
            cin >> sensorID;

            cout << "Enter Sensor Value: ";
            cin >> value;

            cout << "Enter Sensor Status: ";
            cin >> status;

            sensorRecords.emplace_back(
                sensorID,
                value,
                status
            );
        }
    }

    /**
     * @brief Process and display sensor records.
     */
    void processData() override
    {
        cout << "\n===== ECU Sensor Data Logger =====\n";

        if(sensorRecords.empty())
        {
            cout << "No sensor data available.\n";
            return;
        }

        for(const auto& record : sensorRecords)
        {
            const string& sensorID =
                get<0>(record);

            float value =
                get<1>(record);

            const string& status =
                get<2>(record);

            cout << "\nSensor ID : "
                 << sensorID
                 << endl;

            cout << "Value     : "
                 << fixed
                 << setprecision(2)
                 << value
                 << endl;

            cout << "Status    : "
                 << status
                 << endl;

            if(status == "FAULT")
            {
                cout << "Action    : Diagnostic Check Required ⚠️"
                     << endl;
            }
            else
            {
                cout << "Action    : Sensor Operating Normally ✅"
                     << endl;
            }
        }

        cout << "\nTotal Sensor Records: "
             << sensorRecords.size()
             << endl;
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
    ECU* ecu =
        new ECUSensorDataLogger();

    ecu->inputData();

    ecu->processData();

    delete ecu;

    return 0;
}