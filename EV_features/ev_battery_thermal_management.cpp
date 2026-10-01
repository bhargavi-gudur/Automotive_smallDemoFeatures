/**
 * @file ev_battery_thermal_management.cpp
 * @author Gandla Bhargavi
 * @brief EV Battery Thermal Management and Overheat Prediction using OOP and STL
 * @date 05-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief Represents temperature data from one battery sensor.
 */
struct TemperatureSensor
{
    string sensorName;
    double temperatureCelsius;
};

/**
 * @brief Abstract base class for EV thermal systems.
 */
class EVThermalSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVThermalSystem() = default;
};

/**
 * @brief Monitors EV battery temperature and predicts thermal risk.
 */
class BatteryThermalManager : public EVThermalSystem
{
private:
    vector<TemperatureSensor> sensors;

    unordered_map<string, double> temperatureLimits =
    {
        {"Warning", 45.0},
        {"Critical", 55.0}
    };

    double averageTemperature = 0.0;
    double maximumTemperature = 0.0;

    /**
     * @brief Calculates average battery temperature.
     */
    double calculateAverageTemperature() const
    {
        if (sensors.empty())
        {
            return 0.0;
        }

        const double totalTemperature = accumulate(
            sensors.begin(),
            sensors.end(),
            0.0,
            [](double total, const TemperatureSensor& sensor)
            {
                return total + sensor.temperatureCelsius;
            });

        return totalTemperature / sensors.size();
    }

    /**
     * @brief Finds the hottest battery sensor.
     */
    const TemperatureSensor* findHottestSensor() const
    {
        if (sensors.empty())
        {
            return nullptr;
        }

        const auto hottest = max_element(
            sensors.begin(),
            sensors.end(),
            [](const TemperatureSensor& first,
               const TemperatureSensor& second)
            {
                return first.temperatureCelsius <
                       second.temperatureCelsius;
            });

        return &(*hottest);
    }

    /**
     * @brief Checks whether any sensor has exceeded a limit.
     */
    bool hasTemperatureAbove(double limit) const
    {
        return any_of(
            sensors.begin(),
            sensors.end(),
            [limit](const TemperatureSensor& sensor)
            {
                return sensor.temperatureCelsius > limit;
            });
    }

    /**
     * @brief Predicts thermal condition from current temperature data.
     */
    string predictThermalCondition() const
    {
        if (hasTemperatureAbove(temperatureLimits.at("Critical")))
        {
            return "CRITICAL OVERHEAT";
        }

        if (hasTemperatureAbove(temperatureLimits.at("Warning")))
        {
            return "HIGH TEMPERATURE";
        }

        if (averageTemperature >= 40.0)
        {
            return "THERMAL RISK INCREASING";
        }

        return "NORMAL";
    }

    /**
     * @brief Displays cooling recommendation.
     */
    void displayCoolingRecommendation() const
    {
        const string condition = predictThermalCondition();

        cout << "\nCooling Recommendation: ";

        if (condition == "CRITICAL OVERHEAT")
        {
            cout << "ACTIVATE MAXIMUM COOLING";
        }
        else if (condition == "HIGH TEMPERATURE")
        {
            cout << "INCREASE COOLING PERFORMANCE";
        }
        else if (condition == "THERMAL RISK INCREASING")
        {
            cout << "MONITOR TEMPERATURE CLOSELY";
        }
        else
        {
            cout << "NORMAL COOLING";
        }
    }

public:
    /**
     * @brief Adds a battery temperature sensor.
     */
    void addSensor(const TemperatureSensor& sensor)
    {
        sensors.push_back(sensor);
    }

    /**
     * @brief Processes battery thermal telemetry.
     */
    void processData() override
    {
        if (sensors.empty())
        {
            cout << "No battery temperature data available.\n";
            return;
        }

        averageTemperature = calculateAverageTemperature();

        const auto hottestSensor = findHottestSensor();

        if (hottestSensor != nullptr)
        {
            maximumTemperature =
                hottestSensor->temperatureCelsius;
        }

        cout << "\n===== EV BATTERY THERMAL MANAGEMENT =====\n";

        cout << fixed << setprecision(2);

        cout << "\nTemperature Sensors:\n";

        for (const auto& sensor : sensors)
        {
            cout << sensor.sensorName
                 << " : "
                 << sensor.temperatureCelsius
                 << " C";

            if (sensor.temperatureCelsius >
                temperatureLimits.at("Critical"))
            {
                cout << " -> CRITICAL";
            }
            else if (sensor.temperatureCelsius >
                     temperatureLimits.at("Warning"))
            {
                cout << " -> WARNING";
            }
            else
            {
                cout << " -> NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Temperature: "
             << averageTemperature
             << " C";

        cout << "\nMaximum Temperature: "
             << maximumTemperature
             << " C";

        if (hottestSensor != nullptr)
        {
            cout << "\nHottest Sensor: "
                 << hottestSensor->sensorName;
        }

        cout << "\nThermal Prediction: "
             << predictThermalCondition();

        displayCoolingRecommendation();
        cout << '\n';
    }
};

int main()
{
    BatteryThermalManager thermalManager;

    vector<TemperatureSensor> batterySensors =
    {
        {"CellGroup_A", 41.5},
        {"CellGroup_B", 44.2},
        {"CellGroup_C", 48.7},
        {"CellGroup_D", 46.1},
        {"CellGroup_E", 43.8},
        {"CellGroup_F", 56.3}
    };

    for (const auto& sensor : batterySensors)
    {
        thermalManager.addSensor(sensor);
    }

    EVThermalSystem* system = &thermalManager;

    system->processData();

    return 0;
}