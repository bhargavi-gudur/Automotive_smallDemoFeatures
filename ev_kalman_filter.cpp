/**
 * @file ev_kalman_filter.cpp
 * @author Gandla Bhargavi
 * @brief EV battery temperature estimation using a Kalman filter
 * @date 14-10-2026
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>

using namespace std;

// Abstract base class
class EVSensorSystem {
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class implementing a scalar Kalman filter
class BatteryTemperatureKalmanFilter : public EVSensorSystem {
private:
    vector<double> sensorReadings;

    double estimatedTemperature;
    double estimationUncertainty;

    double processNoise;
    double measurementNoise;

public:
    BatteryTemperatureKalmanFilter(
        const vector<double>& readings,
        double initialTemperature,
        double initialUncertainty,
        double q,
        double r
    )
        : sensorReadings(readings),
          estimatedTemperature(initialTemperature),
          estimationUncertainty(initialUncertainty),
          processNoise(q),
          measurementNoise(r) {
    }

    // Override the pure virtual function
    void processData() override {
        cout << fixed << setprecision(2);

        cout << "EV Battery Temperature Kalman Filter\n";
        cout << "-------------------------------------\n";

        cout << left
             << setw(10) << "Sample"
             << setw(18) << "Sensor Temp"
             << setw(18) << "Kalman Gain"
             << setw(20) << "Estimated Temp"
             << "\n";

        cout << string(66, '-') << "\n";

        for (size_t i = 0; i < sensorReadings.size(); ++i) {
            double measuredTemperature = sensorReadings[i];

            // Step 1: Predict the next temperature.
            // This simple model assumes no temperature change
            // before receiving the next sensor measurement.
            double predictedTemperature = estimatedTemperature;

            // Step 2: Predict estimation uncertainty.
            double predictedUncertainty =
                estimationUncertainty + processNoise;

            // Step 3: Calculate Kalman gain.
            double kalmanGain =
                predictedUncertainty /
                (predictedUncertainty + measurementNoise);

            // Step 4: Correct the temperature estimate.
            estimatedTemperature =
                predictedTemperature +
                kalmanGain *
                (measuredTemperature - predictedTemperature);

            // Step 5: Update estimation uncertainty.
            estimationUncertainty =
                (1.0 - kalmanGain) * predictedUncertainty;

            cout << left
                 << setw(10) << i + 1
                 << setw(18) << measuredTemperature
                 << setw(18) << kalmanGain
                 << setw(20) << estimatedTemperature
                 << "\n";
        }

        cout << "\nFinal Estimated Temperature: "
             << estimatedTemperature << " C\n";

        cout << "Final Estimation Uncertainty: "
             << estimationUncertainty << "\n";
    }
};

int main() {
    // Simulated battery temperature sensor readings
    vector<double> temperatureReadings = {
        26.0, 26.5, 27.2, 29.0
    };

    // Create the filter using illustrative parameters.
    double initialTemperature = 25.0;
    double initialUncertainty = 1.0;
    double processNoise = 0.1;
    double measurementNoise = 4.0;

    // Base-class pointer demonstrates polymorphism.
    unique_ptr<EVSensorSystem> sensor =
        make_unique<BatteryTemperatureKalmanFilter>(
            temperatureReadings,
            initialTemperature,
            initialUncertainty,
            processNoise,
            measurementNoise
        );

    sensor->processData();

    return 0;
}