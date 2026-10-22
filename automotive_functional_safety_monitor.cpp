/**
 * @file automotive_functional_safety_monitor.cpp
 * @author Gandla Bhargavi
 * @brief Simulates automotive fault severity handling and safety-state transitions.
 * @date 22-10-2026
 */

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum class Severity {
    INFO,
    WARNING,
    CRITICAL
};

enum class SafetyState {
    NORMAL,
    DEGRADED,
    SAFE_STATE
};

struct FaultEvent {
    std::string faultName;
    Severity severity;
};

// Abstract base class
class FaultHandler {
public:
    virtual void processFault(const FaultEvent& event) = 0;
    virtual void printStatus() const = 0;

    virtual ~FaultHandler() = default;
};

// Concrete implementation
class SafetyMonitor : public FaultHandler {
private:
    SafetyState state = SafetyState::NORMAL;
    std::map<std::string, int> faultCounts;

    std::string severityToString(Severity severity) const {
        switch (severity) {
            case Severity::INFO:
                return "INFO";
            case Severity::WARNING:
                return "WARNING";
            case Severity::CRITICAL:
                return "CRITICAL";
        }

        return "UNKNOWN";
    }

    std::string stateToString(SafetyState currentState) const {
        switch (currentState) {
            case SafetyState::NORMAL:
                return "NORMAL";
            case SafetyState::DEGRADED:
                return "DEGRADED";
            case SafetyState::SAFE_STATE:
                return "SAFE_STATE";
        }

        return "UNKNOWN";
    }

public:
    void processFault(const FaultEvent& event) override {
        ++faultCounts[event.faultName];

        std::cout << "\nFault detected: " << event.faultName
                  << " | Severity: "
                  << severityToString(event.severity) << '\n';

        // Keep SAFE_STATE latched in this simulation.
        if (state == SafetyState::SAFE_STATE) {
            std::cout << "Safety state remains SAFE_STATE.\n";
            return;
        }

        switch (event.severity) {
            case Severity::INFO:
                std::cout << "Informational event recorded.\n";
                break;

            case Severity::WARNING:
                state = SafetyState::DEGRADED;
                std::cout << "Warning response activated.\n";
                break;

            case Severity::CRITICAL:
                state = SafetyState::SAFE_STATE;
                std::cout << "Critical fault! Entering safe state.\n";
                break;
        }

        std::cout << "Current safety state: "
                  << stateToString(state) << '\n';
    }

    void printStatus() const override {
        std::cout << "\n===== SAFETY MONITOR REPORT =====\n";
        std::cout << "Safety state: " << stateToString(state) << '\n';

        std::cout << "Fault occurrence counts:\n";

        if (faultCounts.empty()) {
            std::cout << "No faults recorded.\n";
        } else {
            for (const auto& entry : faultCounts) {
                std::cout << "  " << entry.first
                          << ": " << entry.second << '\n';
            }
        }

        std::cout << "=================================\n";
    }
};

int main() {
    // Polymorphism through an abstract base-class pointer.
    std::unique_ptr<FaultHandler> monitor =
        std::make_unique<SafetyMonitor>();

    const std::vector<FaultEvent> events = {
        {"SteeringSensorTimeout", Severity::WARNING},
        {"CommunicationDelay", Severity::WARNING},
        {"BrakeControllerFailure", Severity::CRITICAL},
        {"SecondarySensorWarning", Severity::WARNING},
        {"SystemInformation", Severity::INFO}
    };

    std::cout << "Automotive Functional Safety Monitor\n";

    for (const FaultEvent& event : events) {
        monitor->processFault(event);
    }

    monitor->printStatus();

    return 0;
}