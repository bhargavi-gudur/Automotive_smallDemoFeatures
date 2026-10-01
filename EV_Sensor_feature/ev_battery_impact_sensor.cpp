/**
 * @file ev_battery_impact_sensor.cpp
 * @author Gandla Bhargavi
 * @brief EV battery shock/acceleration sensor and crash impact detection.
 * @date 19-09-2026
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents one accelerometer reading
struct AccelerationSample
{
    int sensorId;
    string location;
    double xAxisG;
    double yAxisG;
    double zAxisG;
};

// Abstract base class
class EVSensorSystem
{
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class BatteryImpactMonitor : public EVSensorSystem
{
private:
    vector<AccelerationSample> samples;

    unordered_map<string, double> impactLimits{
        {"WARNING", 3.0},
        {"CRITICAL", 6.0}
    };

    double calculateMagnitude(
        const AccelerationSample& sample) const
    {
        return sqrt(
            sample.xAxisG * sample.xAxisG +
            sample.yAxisG * sample.yAxisG +
            sample.zAxisG * sample.zAxisG);
    }

public:
    BatteryImpactMonitor(
        const vector<AccelerationSample>& sensorData)
        : samples(sensorData)
    {
    }

    void processData() override
    {
        if (samples.empty())
        {
            cout << "No acceleration sensor data available.\n";
            return;
        }

        // Find maximum impact magnitude
        auto highestImpact = max_element(
            samples.begin(),
            samples.end(),
            [this](const AccelerationSample& first,
                   const AccelerationSample& second)
            {
                return calculateMagnitude(first) <
                       calculateMagnitude(second);
            });

        // Calculate average magnitude
        double totalMagnitude = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [this](double total,
                   const AccelerationSample& sample)
            {
                return total + calculateMagnitude(sample);
            });

        double averageMagnitude =
            totalMagnitude / samples.size();

        // Count abnormal impact samples
        int abnormalSamples = count_if(
            samples.begin(),
            samples.end(),
            [this](const AccelerationSample& sample)
            {
                return calculateMagnitude(sample) >=
                       impactLimits.at("WARNING");
            });

        cout << "\n===== EV BATTERY IMPACT MONITOR =====\n";

        for (const auto& sample : samples)
        {
            double magnitude = calculateMagnitude(sample);

            cout << "Sensor " << sample.sensorId
                 << " | Location: " << sample.location
                 << " | X: " << fixed << setprecision(2)
                 << sample.xAxisG << " g"
                 << " | Y: " << sample.yAxisG << " g"
                 << " | Z: " << sample.zAxisG << " g"
                 << " | Magnitude: " << magnitude << " g";

            if (magnitude >= impactLimits.at("CRITICAL"))
            {
                cout << " | CRITICAL";
            }
            else if (magnitude >= impactLimits.at("WARNING"))
            {
                cout << " | WARNING";
            }
            else
            {
                cout << " | NORMAL";
            }

            cout << '\n';
        }

        double highestMagnitude =
            calculateMagnitude(*highestImpact);

        cout << "\nAverage Impact    : "
             << averageMagnitude << " g";

        cout << "\nHighest Impact    : Sensor "
             << highestImpact->sensorId
             << " (" << highestMagnitude << " g)";

        cout << "\nAbnormal Samples  : "
             << abnormalSamples;

        if (highestMagnitude >=
            impactLimits.at("CRITICAL"))
        {
            cout << "\nSystem Status     : CRITICAL";
            cout << "\nCrash Alert       : Severe impact detected";
            cout << "\nAction            : Isolate battery system and inspect pack.";
        }
        else if (abnormalSamples > 0)
        {
            cout << "\nSystem Status     : WARNING";
            cout << "\nImpact Alert      : Abnormal acceleration detected";
            cout << "\nAction            : Inspect battery mounting and enclosure.";
        }
        else
        {
            cout << "\nSystem Status     : NORMAL";
            cout << "\nImpact Alert      : No abnormal impact detected";
            cout << "\nAction            : Continue monitoring.";
        }

        cout << "\n=======================================\n";
    }
};

int main()
{
    vector<AccelerationSample> batterySamples{
        {1, "Front Battery Pack", 0.80, 0.60, 1.10},
        {2, "Center Battery Pack", 1.20, 0.90, 1.40},
        {3, "Rear Battery Pack", 2.40, 2.10, 2.80},
        {4, "Left Battery Module", 0.70, 0.80, 1.00},
        {5, "Right Battery Module", 1.00, 0.90, 1.20}
    };

    BatteryImpactMonitor impactMonitor(batterySamples);

    // Runtime polymorphism
    EVSensorSystem* sensorSystem = &impactMonitor;

    sensorSystem->processData();

    return 0;
}