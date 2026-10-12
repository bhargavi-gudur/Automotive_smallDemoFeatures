/**
 * @file ev_complementary_filter.cpp
 * @author Gandla Bhargavi
 * @brief EV sensor fusion using a complementary filter
 * @date 13-10-2026
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Sensor reading structure
struct SensorSample {
    double accelerometerAngle;
    double gyroscopeRate;
    double deltaTime;
};

// Abstract base class
class EVSensorSystem {
public:
    virtual void processData() = 0;

    virtual ~EVSensorSystem() = default;
};

// Derived class
class ComplementaryFilter : public EVSensorSystem {
private:
    vector<SensorSample> sensorData;
    double alpha;
    double estimatedAngle;

public:
    ComplementaryFilter(
        const vector<SensorSample>& data,
        double filterAlpha
    ) : sensorData(data),
        alpha(filterAlpha),
        estimatedAngle(0.0) {
    }

    // Override the pure virtual function
    void processData() override {
        cout << fixed << setprecision(2);

        cout << "EV Complementary Filter Sensor Fusion\n";
        cout << "--------------------------------------\n";

        cout << "Alpha: " << alpha << "\n\n";

        cout << left
             << setw(10) << "Sample"
             << setw(18) << "Accel Angle"
             << setw(18) << "Gyro Rate"
             << setw(18) << "Fused Angle"
             << "\n";

        cout << string(64, '-') << "\n";

        for (size_t i = 0; i < sensorData.size(); ++i) {
            const SensorSample& sample = sensorData[i];

            // Predict angle using gyroscope
            double gyroAngle =
                estimatedAngle +
                sample.gyroscopeRate * sample.deltaTime;

            // Correct estimate using accelerometer
            estimatedAngle =
                alpha * gyroAngle +
                (1.0 - alpha) * sample.accelerometerAngle;

            cout << left
                 << setw(10) << i + 1
                 << setw(18) << sample.accelerometerAngle
                 << setw(18) << sample.gyroscopeRate
                 << setw(18) << estimatedAngle
                 << "\n";
        }

        cout << "\nFinal Estimated Angle: "
             << estimatedAngle << " degrees\n";
    }
};

int main() {
    // Simulated sensor readings
    vector<SensorSample> readings = {
        {2.0, 3.0, 0.1},
        {2.5, 4.0, 0.1},
        {3.2, 2.0, 0.1},
        {3.5, 1.0, 0.1}
    };

    // Base-class pointer demonstrates polymorphism
    EVSensorSystem* sensor =
        new ComplementaryFilter(readings, 0.98);

    sensor->processData();

    delete sensor;

    return 0;
}