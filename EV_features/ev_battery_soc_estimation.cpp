/**
 * @file ev_battery_soc_estimation.cpp
 * @author Gandla Bhargavi
 * @brief EV Battery State of Charge Estimation using Coulomb Counting, OOP and STL
 * @date 07-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Represents one battery current sample.
 *
 * Positive current  -> battery discharging
 * Negative current  -> battery charging
 */
struct BatterySample
{
    double currentAmpere;
    double durationSeconds;
};

/**
 * @brief Abstract base class for EV battery estimation.
 */
class BatteryEstimator
{
public:
    virtual void processData() = 0;

    virtual ~BatteryEstimator() = default;
};

/**
 * @brief Estimates battery SoC using Coulomb Counting.
 */
class EVBatterySoCEstimator : public BatteryEstimator
{
private:
    double batteryCapacityAh;
    double initialSoC;

    double currentSoC;

    vector<BatterySample> samples;

    /**
     * @brief Calculates charge variation in Ampere-hours.
     */
    double calculateChargeVariationAh() const
    {
        const double totalChargeCoulombs = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double total, const BatterySample& sample)
            {
                return total +
                       (sample.currentAmpere *
                        sample.durationSeconds);
            });

        // Convert Coulombs to Ampere-hours.
        return totalChargeCoulombs / 3600.0;
    }

    /**
     * @brief Calculates total charging current contribution.
     */
    double calculateChargingAh() const
    {
        const double chargingCoulombs = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double total, const BatterySample& sample)
            {
                if (sample.currentAmpere < 0.0)
                {
                    return total +
                           (-sample.currentAmpere *
                            sample.durationSeconds);
                }

                return total;
            });

        return chargingCoulombs / 3600.0;
    }

    /**
     * @brief Calculates total discharging current contribution.
     */
    double calculateDischargingAh() const
    {
        const double dischargingCoulombs = accumulate(
            samples.begin(),
            samples.end(),
            0.0,
            [](double total, const BatterySample& sample)
            {
                if (sample.currentAmpere > 0.0)
                {
                    return total +
                           (sample.currentAmpere *
                            sample.durationSeconds);
                }

                return total;
            });

        return dischargingCoulombs / 3600.0;
    }

    /**
     * @brief Keeps SoC within the valid 0-100% range.
     */
    void clampSoC()
    {
        currentSoC = clamp(currentSoC, 0.0, 100.0);
    }

public:
    /**
     * @brief Constructor for battery SoC estimator.
     */
    EVBatterySoCEstimator(double capacityAh, double soc)
        : batteryCapacityAh(capacityAh),
          initialSoC(soc),
          currentSoC(soc)
    {
    }

    /**
     * @brief Adds a battery current sample.
     */
    void addSample(const BatterySample& sample)
    {
        if (sample.durationSeconds > 0.0)
        {
            samples.push_back(sample);
        }
    }

    /**
     * @brief Estimates SoC from current measurements.
     */
    void processData() override
    {
        if (samples.empty())
        {
            cout << "No battery current data available.\n";
            return;
        }

        const double chargeVariationAh =
            calculateChargeVariationAh();

        currentSoC =
            initialSoC -
            (chargeVariationAh / batteryCapacityAh) * 100.0;

        clampSoC();

        const double chargingAh = calculateChargingAh();
        const double dischargingAh = calculateDischargingAh();

        cout << "\n===== EV BATTERY SOC ESTIMATION =====\n";

        cout << fixed << setprecision(2);

        cout << "\nBattery Capacity: "
             << batteryCapacityAh
             << " Ah";

        cout << "\nInitial SoC: "
             << initialSoC
             << " %";

        cout << "\nCharging Energy Flow: "
             << chargingAh
             << " Ah";

        cout << "\nDischarging Energy Flow: "
             << dischargingAh
             << " Ah";

        cout << "\nNet Charge Variation: "
             << chargeVariationAh
             << " Ah";

        cout << "\nEstimated SoC: "
             << currentSoC
             << " %";

        if (currentSoC <= 20.0)
        {
            cout << "\nBattery Status: LOW SOC";
        }
        else if (currentSoC <= 50.0)
        {
            cout << "\nBattery Status: MODERATE SOC";
        }
        else
        {
            cout << "\nBattery Status: HEALTHY SOC";
        }

        cout << '\n';
    }

    /**
     * @brief Returns the estimated SoC.
     */
    double getSoC() const
    {
        return currentSoC;
    }
};

int main()
{
    // Example: 150 Ah EV battery.
    EVBatterySoCEstimator battery(150.0, 80.0);

    vector<BatterySample> batterySamples =
    {
        {40.0, 600.0},    // Discharge
        {35.0, 480.0},    // Discharge
        {-20.0, 300.0},   // Charging
        {30.0, 420.0},    // Discharge
        {25.0, 360.0}     // Discharge
    };

    for (const auto& sample : batterySamples)
    {
        battery.addSample(sample);
    }

    BatteryEstimator* estimator = &battery;

    estimator->processData();

    return 0;
}