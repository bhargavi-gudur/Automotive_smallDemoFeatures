/**
 * @file automotive_network_signal_monitor.cpp
 * @author Gandla Bhargavi
 * @brief Validates automotive network signals and detects stale data.
 * @date 25-10-2026
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class SignalState {
    VALID,
    INVALID,
    STALE
};

struct SignalConfig {
    std::string name;
    double minimum;
    double maximum;
    int timeoutMs;
};

struct SignalData {
    double value = 0.0;
    int lastUpdateMs = -1;
    int invalidCount = 0;
    int staleCount = 0;
    bool hasValue = false;
    bool lastValueInRange = false;
    SignalState state = SignalState::STALE;
};

struct SignalSample {
    std::string name;
    double value;
    int timestampMs;
};

class SignalMonitorInterface {
public:
    virtual void processSample(const SignalSample& sample) = 0;
    virtual void evaluateStaleSignals(int currentTimeMs) = 0;
    virtual void printReport() const = 0;

    virtual ~SignalMonitorInterface() = default;
};

class NetworkSignalMonitor : public SignalMonitorInterface {
private:
    std::map<std::string, SignalConfig> configurations;
    std::map<std::string, SignalData> signals;

    static std::string stateToString(SignalState state) {
        switch (state) {
            case SignalState::VALID:
                return "VALID";
            case SignalState::INVALID:
                return "INVALID";
            case SignalState::STALE:
                return "STALE";
        }

        return "UNKNOWN";
    }

public:
    void addSignal(
        const std::string& name,
        double minimum,
        double maximum,
        int timeoutMs
    ) {
        if (minimum > maximum || timeoutMs < 0) {
            std::cout << "Invalid configuration for " << name << '\n';
            return;
        }

        configurations[name] = {
            name, minimum, maximum, timeoutMs
        };

        signals.emplace(name, SignalData{});
    }

    void processSample(const SignalSample& sample) override {
        auto configIt = configurations.find(sample.name);

        if (configIt == configurations.end()) {
            std::cout << "\nUnknown signal: " << sample.name << '\n';
            return;
        }

        SignalData& data = signals.at(sample.name);
        const SignalConfig& config = configIt->second;

        if (sample.timestampMs < 0 ||
            (data.hasValue &&
             sample.timestampMs < data.lastUpdateMs)) {
            std::cout << "\nRejected out-of-order sample for "
                      << sample.name << '\n';
            return;
        }

        data.value = sample.value;
        data.lastUpdateMs = sample.timestampMs;
        data.hasValue = true;

        data.lastValueInRange =
            sample.value >= config.minimum &&
            sample.value <= config.maximum;

        if (data.lastValueInRange) {
            data.state = SignalState::VALID;
            std::cout << "\n" << sample.name
                      << ": " << sample.value
                      << " -> VALID\n";
        } else {
            data.state = SignalState::INVALID;
            ++data.invalidCount;

            std::cout << "\n" << sample.name
                      << ": " << sample.value
                      << " -> INVALID (outside range "
                      << config.minimum << " to "
                      << config.maximum << ")\n";
        }
    }

    void evaluateStaleSignals(int currentTimeMs) override {
        std::cout << "\nChecking signal freshness at "
                  << currentTimeMs << " ms\n";

        for (auto& entry : signals) {
            const std::string& name = entry.first;
            SignalData& data = entry.second;
            const SignalConfig& config = configurations.at(name);

            if (currentTimeMs < 0) {
                std::cout << "Invalid evaluation time.\n";
                return;
            }

            if (!data.hasValue ||
                currentTimeMs - data.lastUpdateMs > config.timeoutMs) {
                if (data.state != SignalState::STALE) {
                    ++data.staleCount;
                }

                data.state = SignalState::STALE;
                std::cout << name << " -> STALE\n";
            } else if (data.lastValueInRange) {
                data.state = SignalState::VALID;
                std::cout << name << " -> VALID\n";
            } else {
                data.state = SignalState::INVALID;
                std::cout << name << " -> INVALID\n";
            }
        }
    }

    void printReport() const override {
        std::cout << "\n===== NETWORK SIGNAL REPORT =====\n";

        for (const auto& entry : signals) {
            const std::string& name = entry.first;
            const SignalData& data = entry.second;

            std::cout << name
                      << " | State: " << stateToString(data.state)
                      << " | Last value: ";

            if (data.hasValue) {
                std::cout << data.value;
            } else {
                std::cout << "N/A";
            }

            std::cout << " | Invalid samples: " << data.invalidCount
                      << " | Stale events: " << data.staleCount
                      << '\n';
        }

        std::cout << "=================================\n";
    }
};

int main() {
    NetworkSignalMonitor concreteMonitor;
    SignalMonitorInterface& monitor = concreteMonitor;

    concreteMonitor.addSignal("VehicleSpeed", 0.0, 250.0, 100);
    concreteMonitor.addSignal("EngineTemperature", -40.0, 150.0, 200);
    concreteMonitor.addSignal("SteeringAngle", -540.0, 540.0, 100);

    const std::vector<SignalSample> samples = {
        {"VehicleSpeed", 80.0, 0},
        {"EngineTemperature", 95.0, 0},
        {"SteeringAngle", 20.0, 0},
        {"VehicleSpeed", 280.0, 50},
        {"EngineTemperature", 100.0, 100}
    };

    std::cout << "Automotive Network Signal Validity Monitor\n";

    for (const SignalSample& sample : samples) {
        monitor.processSample(sample);
    }

    monitor.evaluateStaleSignals(150);
    monitor.evaluateStaleSignals(250);
    monitor.printReport();

    return 0;
}