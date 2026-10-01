/**
 * @file ev_sensor_battery.cpp
 * @author Gandla Bhargavi
 * @brief
 *   This program simulates Electric Vehicle (EV)
 *   sensor monitoring system using inheritance and STL.
 *   It monitors:
 *   - Battery Temperature
 *   - Current
 *   - Voltage
 *   - Motor Speed
 * @date 28-05-2026
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base Sensor Class
 */
class Sensor {

protected:
    vector<float> readings;

public:

    /**
     * @brief Input sensor readings
     */
    void inputReadings() {

        int n;
        float value;

        cout << "Enter number of readings: ";
        cin >> n;

        for(int i = 0; i < n; i++) {

            cout << "Enter reading: ";
            cin >> value;

            readings.push_back(value);
        }
    }
};

/**
 * @brief Battery Temperature Sensor
 */
class BatteryTempSensor : public Sensor {

public:

    /**
     * @brief Check battery temperature
     */
    void checkTemperature() {

        cout << "\n===== Battery Temperature Status =====\n";

        for(float value : readings) {

            if(value > 45) {

                cout << value
                     << "°C -> Overheating Warning ⚠️\n";
            }
            else {

                cout << value
                     << "°C -> Temperature Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Current Sensor
 */
class CurrentSensor : public Sensor {

public:

    /**
     * @brief Check battery current
     */
    void checkCurrent() {

        cout << "\n===== Battery Current Status =====\n";

        for(float value : readings) {

            if(value > 100) {

                cout << value
                     << "A -> High Current Warning ⚠️\n";
            }
            else {

                cout << value
                     << "A -> Current Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Voltage Sensor
 */
class VoltageSensor : public Sensor {

public:

    /**
     * @brief Check voltage level
     */
    void checkVoltage() {

        cout << "\n===== Voltage Status =====\n";

        for(float value : readings) {

            if(value < 300) {

                cout << value
                     << "V -> Low Voltage Warning ⚠️\n";
            }
            else {

                cout << value
                     << "V -> Voltage Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Motor Speed Sensor
 */
class MotorSpeedSensor : public Sensor {

public:

    /**
     * @brief Check motor RPM
     */
    void checkSpeed() {

        cout << "\n===== Motor Speed Status =====\n";

        for(float value : readings) {

            if(value > 5000) {

                cout << value
                     << " RPM -> High Speed Warning ⚠️\n";
            }
            else {

                cout << value
                     << " RPM -> Speed Normal ✅\n";
            }
        }
    }
};

/**
 * @brief Main function
 */
int main() {

    BatteryTempSensor battery;
    CurrentSensor current;
    VoltageSensor voltage;
    MotorSpeedSensor motor;

    cout << "===== Battery Temperature Sensor =====\n";
    battery.inputReadings();
    battery.checkTemperature();

    cout << "\n===== Current Sensor =====\n";
    current.inputReadings();
    current.checkCurrent();

    cout << "\n===== Voltage Sensor =====\n";
    voltage.inputReadings();
    voltage.checkVoltage();

    cout << "\n===== Motor Speed Sensor =====\n";
    motor.inputReadings();
    motor.checkSpeed();

    return 0;
}