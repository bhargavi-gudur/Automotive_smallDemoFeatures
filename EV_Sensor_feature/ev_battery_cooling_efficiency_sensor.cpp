/**
 * @file ev_battery_cooling_efficiency_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery coolant temperature and flow sensor fusion for cooling efficiency detection.
 * @date 28-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents combined sensor data from one cooling zone
struct CoolingZone
{
    int zoneId;
    string location;
    double inletTemperatureC;
    double outletTemperatureC;
    double flowRateLpm;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryCoolingEfficiencyMonitor : public EVSensorSystem
{
private:
    vector<CoolingZone> zones;

    unordered_map<string, double> limits{
        {"MIN_FLOW", 4.0},
        {"MAX_OUTLET_TEMP", 50.0},
        {"MIN_TEMP_DROP", 2.0}
    };

    double calculateTemperatureDrop(
        const CoolingZone& zone) const
    {
        return zone.inletTemperatureC -
               zone.outletTemperatureC;
    }

    double calculateEfficiency(
        const CoolingZone& zone) const
    {
        double temperatureDrop =
            calculateTemperatureDrop(zone);

        if (zone.flowRateLpm <= 0.0)
        {
            return 0.0;
        }

        return (temperatureDrop /
                zone.flowRateLpm) * 100.0;
    }

public:
    BatteryCoolingEfficiencyMonitor(
        const vector<CoolingZone>& coolingData)
        : zones(coolingData)
    {
    }

    void processData() override
    {
        if (zones.empty())
        {
            cout << "No cooling sensor data available.\n";
            return;
        }

        // Average inlet temperature
        double totalInletTemperature = accumulate(
            zones.begin(),
            zones.end(),
            0.0,
            [](double total, const CoolingZone& zone)
            {
                return total + zone.inletTemperatureC;
            });

        double averageInletTemperature =
            totalInletTemperature / zones.size();

        // Average outlet temperature
        double totalOutletTemperature = accumulate(
            zones.begin(),
            zones.end(),
            0.0,
            [](double total, const CoolingZone& zone)
            {
                return total + zone.outletTemperatureC;
            });

        double averageOutletTemperature =
            totalOutletTemperature / zones.size();

        // Find zone with lowest flow
        auto lowestFlowZone = min_element(
            zones.begin(),
            zones.end(),
            [](const CoolingZone& first,
               const CoolingZone& second)
            {
                return first.flowRateLpm <
                       second.flowRateLpm;
            });

        // Find hottest outlet
        auto hottestOutletZone = max_element(
            zones.begin(),
            zones.end(),
            [](const CoolingZone& first,
               const CoolingZone& second)
            {
                return first.outletTemperatureC <
                       second.outletTemperatureC;
            });

        // Count inefficient cooling zones
        int inefficientZones = count_if(
            zones.begin(),
            zones.end(),
            [this](const CoolingZone& zone)
            {
                return zone.flowRateLpm <
                           limits.at("MIN_FLOW") ||
                       zone.outletTemperatureC >
                           limits.at("MAX_OUTLET_TEMP") ||
                       calculateTemperatureDrop(zone) <
                           limits.at("MIN_TEMP_DROP");
            });

        cout << "\n===== EV BATTERY COOLING EFFICIENCY MONITOR =====\n";

        for (const auto& zone : zones)
        {
            double temperatureDrop =
                calculateTemperatureDrop(zone);

            double efficiency =
                calculateEfficiency(zone);

            cout << "Zone " << zone.zoneId
                 << " | Location: " << zone.location
                 << " | Inlet: "
                 << fixed << setprecision(1)
                 << zone.inletTemperatureC << " °C"
                 << " | Outlet: "
                 << zone.outletTemperatureC << " °C"
                 << " | Flow: "
                 << zone.flowRateLpm << " L/min"
                 << " | ΔT: "
                 << temperatureDrop << " °C"
                 << " | Efficiency: "
                 << efficiency << "%";

            if (zone.flowRateLpm <
                    limits.at("MIN_FLOW") ||
                zone.outletTemperatureC >
                    limits.at("MAX_OUTLET_TEMP") ||
                temperatureDrop <
                    limits.at("MIN_TEMP_DROP"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        cout << "\nAverage Inlet Temp  : "
             << averageInletTemperature << " °C";

        cout << "\nAverage Outlet Temp : "
             << averageOutletTemperature << " °C";

        cout << "\nLowest Flow Zone    : Zone "
             << lowestFlowZone->zoneId
             << " (" << lowestFlowZone->flowRateLpm
             << " L/min)";

        cout << "\nHottest Outlet      : Zone "
             << hottestOutletZone->zoneId
             << " (" << hottestOutletZone->outletTemperatureC
             << " °C)";

        cout << "\nInefficient Zones   : "
             << inefficientZones;

        if (hottestOutletZone->outletTemperatureC >=
                limits.at("MAX_OUTLET_TEMP") ||
            lowestFlowZone->flowRateLpm <
                limits.at("MIN_FLOW"))
        {
            cout << "\nSystem Status       : WARNING";
            cout << "\nCooling Alert       : Cooling performance degraded";
            cout << "\nAction              : Inspect coolant flow and thermal management system.";
        }
        else if (inefficientZones > 0)
        {
            cout << "\nSystem Status       : ATTENTION";
            cout << "\nCooling Alert       : Reduced cooling efficiency detected";
            cout << "\nAction              : Monitor cooling zones.";
        }
        else
        {
            cout << "\nSystem Status       : NORMAL";
            cout << "\nCooling Alert       : Cooling performance is within limits";
            cout << "\nAction              : Continue monitoring.";
        }

        cout << "\n====================================================\n";
    }
};

int main()
{
    vector<CoolingZone> coolingZones{
        {1, "Front Battery Module", 42.0, 36.5, 6.8},
        {2, "Center Battery Module", 45.0, 39.2, 6.1},
        {3, "Rear Battery Module", 48.0, 45.8, 3.5},
        {4, "Left Battery Module", 43.0, 37.8, 6.4},
        {5, "Right Battery Module", 44.0, 38.5, 6.0}
    };

    BatteryCoolingEfficiencyMonitor coolingMonitor(
        coolingZones);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &coolingMonitor;

    sensorSystem->processData();

    return 0;
}