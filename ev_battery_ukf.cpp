/**
 * @file ev_battery_ukf.cpp
 * @author Gandla Bhargavi
 * @brief EV battery SoC estimation using an Unscented Kalman Filter
 * @date 15-10-2026
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct BatterySample {
    double current;
    double voltage;
    double deltaTime;
};

class EVSensorSystem {
public:
    virtual void processData() = 0;
    virtual ~EVSensorSystem() = default;
};

class BatteryUKF : public EVSensorSystem {
private:
    vector<BatterySample> samples;

    double soc;
    double covariance;
    double processNoise;
    double measurementNoise;
    double capacityAh;
    double resistance;

    // Simplified nonlinear open-circuit voltage model.
    double openCircuitVoltage(double state) const {
        return 3.0 + 1.2 * state - 0.1 * state * state;
    }

    // One-dimensional UKF parameters.
    static constexpr double alpha = 0.5;
    static constexpr double beta = 2.0;
    static constexpr double kappa = 0.0;

public:
    BatteryUKF(
        const vector<BatterySample>& data,
        double initialSoc,
        double initialCovariance,
        double q,
        double r,
        double capacity,
        double internalResistance
    )
        : samples(data),
          soc(initialSoc),
          covariance(initialCovariance),
          processNoise(q),
          measurementNoise(r),
          capacityAh(capacity),
          resistance(internalResistance) {
    }

    void processData() override {
        constexpr double n = 1.0;

        const double lambda =
            alpha * alpha * (n + kappa) - n;

        const double wm0 = lambda / (n + lambda);
        const double wc0 =
            wm0 + (1.0 - alpha * alpha + beta);

        const double wi = 1.0 / (2.0 * (n + lambda));

        cout << fixed << setprecision(4);

        cout << "EV Battery UKF - SoC Estimation\n";
        cout << "-----------------------------------------------\n";

        cout << left
             << setw(8) << "Sample"
             << setw(12) << "Voltage"
             << setw(12) << "SoC"
             << setw(14) << "Covariance"
             << "\n";

        cout << string(46, '-') << "\n";

        for (size_t i = 0; i < samples.size(); ++i) {
            const auto& sample = samples[i];

            // 1. Predict SoC using coulomb counting.
            const double predictedSoc =
                soc -
                sample.current * sample.deltaTime /
                (capacityAh * 3600.0);

            // 2. Generate sigma points around predicted SoC.
            const double predictedCovariance =
                covariance + processNoise;

            const double spread =
                sqrt((n + lambda) * predictedCovariance);

            const double sigma0 = predictedSoc;
            const double sigma1 = predictedSoc + spread;
            const double sigma2 = predictedSoc - spread;

            // 3. Propagate sigma points through the
            // nonlinear terminal-voltage model.
            const double z0 =
                openCircuitVoltage(sigma0)
                - sample.current * resistance;

            const double z1 =
                openCircuitVoltage(sigma1)
                - sample.current * resistance;

            const double z2 =
                openCircuitVoltage(sigma2)
                - sample.current * resistance;

            // 4. Calculate predicted voltage.
            const double predictedVoltage =
                wm0 * z0 + wi * z1 + wi * z2;

            // 5. Calculate voltage and state covariance.
            const double dz0 = z0 - predictedVoltage;
            const double dz1 = z1 - predictedVoltage;
            const double dz2 = z2 - predictedVoltage;

            const double innovationCovariance =
                wc0 * dz0 * dz0
                + wi * dz1 * dz1
                + wi * dz2 * dz2
                + measurementNoise;

            const double dx0 = sigma0 - predictedSoc;
            const double dx1 = sigma1 - predictedSoc;
            const double dx2 = sigma2 - predictedSoc;

            const double crossCovariance =
                wc0 * dx0 * dz0
                + wi * dx1 * dz1
                + wi * dx2 * dz2;

            // 6. Calculate UKF gain.
            const double gain =
                crossCovariance / innovationCovariance;

            // 7. Correct the SoC estimate using voltage.
            soc = predictedSoc +
                  gain * (sample.voltage - predictedVoltage);

            // Keep SoC within physical bounds.
            soc = clamp(soc, 0.0, 1.0);

            // 8. Update covariance.
            covariance =
                predictedCovariance
                - gain * innovationCovariance * gain;

            covariance = max(covariance, 1e-12);

            cout << left
                 << setw(8) << i + 1
                 << setw(12) << sample.voltage
                 << setw(12) << soc
                 << setw(14) << covariance
                 << "\n";
        }

        cout << "\nEstimated Battery SoC: "
             << soc * 100.0 << "%\n";
    }
};

int main() {
    vector<BatterySample> readings = {
        {20.0, 3.80, 10.0},
        {20.0, 3.79, 10.0},
        {20.0, 3.78, 10.0},
        {20.0, 3.77, 10.0}
    };

    unique_ptr<EVSensorSystem> system =
        make_unique<BatteryUKF>(
            readings,
            0.80,   // Initial SoC
            0.01,   // Initial covariance
            0.0001, // Process noise
            0.0004, // Voltage measurement noise
            60.0,   // Battery capacity in Ah
            0.005   // Illustrative internal resistance
        );

    system->processData();

    return 0;
}