/**
 * @file ecu_communication_timeout_recovery.cpp
 * @author Gandla Bhargavi
 * @brief Simulates ECU communication timeout detection and recovery.
 * @date 23-10-2026
 */

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum class CommunicationState {
    ONLINE,
    RETRYING,
    OFFLINE
};

struct ECU {
    std::string name;
    int timeoutLimitMs;
    int retryCount = 0;
    int failureCount = 0;
    CommunicationState state = CommunicationState::ONLINE;
};

struct CommunicationEvent {
    std::string ecuName;
    int responseTimeMs;
    bool responseReceived;
};

// Abstract interface
class CommunicationManager {
public:
    virtual void processEvent(const CommunicationEvent& event) = 0;
    virtual void printReport() const = 0;

    virtual ~CommunicationManager() = default;
};

class ECURecoveryManager : public CommunicationManager {
private:
    std::map<std::string, ECU> ecus;
    const int maxRetries = 2;

    std::string stateToString(CommunicationState state) const {
        switch (state) {
            case CommunicationState::ONLINE:
                return "ONLINE";
            case CommunicationState::RETRYING:
                return "RETRYING";
            case CommunicationState::OFFLINE:
                return "OFFLINE";
        }

        return "UNKNOWN";
    }

public:
    void addECU(const std::string& name, int timeoutLimitMs) {
        ecus.emplace(
            name,
            ECU{name, timeoutLimitMs}
        );
    }

    void processEvent(const CommunicationEvent& event) override {
        auto it = ecus.find(event.ecuName);

        if (it == ecus.end()) {
            std::cout << "\nUnknown ECU: " << event.ecuName << '\n';
            return;
        }

        ECU& ecu = it->second;

        std::cout << "\nECU: " << ecu.name << '\n';

        if (ecu.state == CommunicationState::OFFLINE) {
            std::cout << "ECU is OFFLINE. Recovery is required.\n";
            return;
        }

        const bool timedOut =
            !event.responseReceived ||
            event.responseTimeMs > ecu.timeoutLimitMs;

        if (!timedOut) {
            if (ecu.state == CommunicationState::RETRYING) {
                std::cout << "Communication recovered after retry.\n";
            } else {
                std::cout << "Response received within timeout.\n";
            }

            ecu.state = CommunicationState::ONLINE;
            ecu.retryCount = 0;
        } else {
            ++ecu.failureCount;

            std::cout << "Communication timeout detected.\n";

            if (ecu.retryCount < maxRetries) {
                ++ecu.retryCount;
                ecu.state = CommunicationState::RETRYING;

                std::cout << "Retry attempt: "
                          << ecu.retryCount
                          << "/" << maxRetries << '\n';
            } else {
                ecu.state = CommunicationState::OFFLINE;

                std::cout << "Maximum retries exceeded.\n";
                std::cout << "ECU marked OFFLINE.\n";
            }
        }

        std::cout << "Current state: "
                  << stateToString(ecu.state) << '\n';
    }

    void printReport() const override {
        std::cout << "\n===== ECU COMMUNICATION REPORT =====\n";

        for (const auto& entry : ecus) {
            const ECU& ecu = entry.second;

            std::cout << "ECU: " << ecu.name
                      << " | State: " << stateToString(ecu.state)
                      << " | Retries: " << ecu.retryCount
                      << " | Failures: " << ecu.failureCount
                      << '\n';
        }

        std::cout << "====================================\n";
    }
};

int main() {
    std::unique_ptr<CommunicationManager> manager =
        std::make_unique<ECURecoveryManager>();

    // Configure the simulated ECUs.
    auto* recoveryManager =
        dynamic_cast<ECURecoveryManager*>(manager.get());

    recoveryManager->addECU("EngineECU", 100);
    recoveryManager->addECU("TransmissionECU", 100);
    recoveryManager->addECU("BrakingECU", 100);

    const std::vector<CommunicationEvent> events = {
        {"EngineECU", 40, true},

        {"TransmissionECU", 150, true},
        {"TransmissionECU", 60, true},

        {"BrakingECU", 150, false},
        {"BrakingECU", 170, false},
        {"BrakingECU", 180, false}
    };

    std::cout << "ECU Communication Timeout Recovery Manager\n";

    for (const CommunicationEvent& event : events) {
        manager->processEvent(event);
    }

    manager->printReport();

    return 0;
}