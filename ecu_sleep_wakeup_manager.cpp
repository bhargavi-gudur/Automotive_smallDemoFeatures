/**
 * @file ecu_sleep_wakeup_manager.cpp
 * @author Gandla Bhargavi
 * @brief Automotive ECU sleep and wake-up state manager
 * @date 19-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <chrono>

using namespace std;
using namespace chrono;

// ECU operating states
enum class ECUState {
    ACTIVE,
    SLEEP_PENDING,
    SLEEP,
    WAKING_UP
};

// Vehicle event
struct VehicleEvent {
    int timeSeconds;
    string eventType;
};

// Abstract base class
class ECUManager {
public:
    virtual void processData() = 0;

    virtual ~ECUManager() = default;
};

// Derived class
class ECUSleepWakeupManager : public ECUManager {
private:
    ECUState state;

    vector<VehicleEvent> events;
    unordered_map<string, int> eventCounts;

    seconds inactivityTimeout;
    seconds lastActivity;
    seconds wakeupCompleteAt;

    bool ignitionOn;
    int sleepEntries;
    int wakeupCount;

    string getStateName(ECUState currentState) const {
        switch (currentState) {
            case ECUState::ACTIVE:
                return "ACTIVE";

            case ECUState::SLEEP_PENDING:
                return "SLEEP_PENDING";

            case ECUState::SLEEP:
                return "SLEEP";

            case ECUState::WAKING_UP:
                return "WAKING_UP";
        }

        return "UNKNOWN";
    }

    // Change state and record the transition.
    void changeState(
        ECUState newState,
        seconds currentTime
    ) {
        if (state == newState) {
            return;
        }

        cout << "[STATE] "
             << getStateName(state)
             << " -> "
             << getStateName(newState)
             << " at "
             << currentTime.count()
             << " s\n";

        state = newState;

        if (state == ECUState::SLEEP) {
            sleepEntries++;
        }
    }

    // Begin wake-up when the ECU is asleep.
    void startWakeup(seconds currentTime) {
        if (state == ECUState::SLEEP) {
            changeState(ECUState::WAKING_UP, currentTime);

            wakeupCompleteAt = currentTime + seconds(1);
            wakeupCount++;
        }
    }

    // Process ignition, door, and network events.
    void handleEvent(
        const VehicleEvent& event,
        seconds currentTime
    ) {
        cout << "[EVENT] "
             << event.eventType
             << " at "
             << currentTime.count()
             << " s\n";

        eventCounts[event.eventType]++;

        if (event.eventType == "IGNITION_ON") {
            ignitionOn = true;
            lastActivity = currentTime;

            if (state == ECUState::SLEEP) {
                startWakeup(currentTime);
            } else if (state == ECUState::SLEEP_PENDING) {
                changeState(ECUState::ACTIVE, currentTime);
            }
        }
        else if (event.eventType == "IGNITION_OFF") {
            ignitionOn = false;
            lastActivity = currentTime;

            if (state == ECUState::ACTIVE) {
                changeState(ECUState::SLEEP_PENDING, currentTime);
            }
        }
        else if (event.eventType == "DOOR_OPEN") {
            lastActivity = currentTime;

            if (state == ECUState::SLEEP) {
                startWakeup(currentTime);
            }
        }
        else if (event.eventType == "NETWORK_WAKEUP") {
            lastActivity = currentTime;

            if (state == ECUState::SLEEP) {
                startWakeup(currentTime);
            }
        }
        else {
            cout << "[WARNING] Unknown event ignored.\n";
        }
    }

public:
    ECUSleepWakeupManager(
        const vector<VehicleEvent>& vehicleEvents,
        seconds timeout
    )
        : state(ECUState::ACTIVE),
          events(vehicleEvents),
          inactivityTimeout(timeout),
          lastActivity(seconds(0)),
          wakeupCompleteAt(seconds(0)),
          ignitionOn(false),
          sleepEntries(0),
          wakeupCount(0) {
    }

    void processData() override {
        cout << "AUTOMOTIVE ECU SLEEP/WAKE-UP MANAGER\n";
        cout << "====================================\n";

        // Ensure events are processed in chronological order.
        sort(
            events.begin(),
            events.end(),
            [](const VehicleEvent& a, const VehicleEvent& b) {
                return a.timeSeconds < b.timeSeconds;
            }
        );

        size_t eventIndex = 0;

        // Simulated timeline: 0 to 25 seconds.
        for (int t = 0; t <= 25; ++t) {
            seconds currentTime(t);

            // Process events scheduled for this second.
            while (
                eventIndex < events.size() &&
                events[eventIndex].timeSeconds == t
            ) {
                handleEvent(events[eventIndex], currentTime);
                eventIndex++;
            }

            // Complete the wake-up sequence.
            if (
                state == ECUState::WAKING_UP &&
                currentTime >= wakeupCompleteAt
            ) {
                if (ignitionOn) {
                    changeState(ECUState::ACTIVE, currentTime);
                } else {
                    changeState(
                        ECUState::SLEEP_PENDING,
                        currentTime
                    );
                }
            }

            // Enter sleep after sufficient inactivity.
            if (
                state == ECUState::SLEEP_PENDING &&
                !ignitionOn &&
                currentTime - lastActivity >= inactivityTimeout
            ) {
                changeState(ECUState::SLEEP, currentTime);
            }
        }

        displaySummary();
    }

    void displaySummary() const {
        cout << "\nECU POWER MANAGEMENT SUMMARY\n";
        cout << "-----------------------------\n";

        cout << "Final state: "
             << getStateName(state) << '\n';

        cout << "Ignition: "
             << (ignitionOn ? "ON" : "OFF") << '\n';

        cout << "Sleep entries: " << sleepEntries << '\n';
        cout << "Wake-up sequences: " << wakeupCount << '\n';

        cout << "\nEvent counts:\n";

        for (const auto& entry : eventCounts) {
            cout << entry.first
                 << ": " << entry.second << '\n';
        }
    }
};

int main() {
    vector<VehicleEvent> vehicleEvents = {
        {0,  "IGNITION_ON"},
        {3,  "IGNITION_OFF"},
        {10, "NETWORK_WAKEUP"},
        {17, "DOOR_OPEN"}
    };

    unique_ptr<ECUManager> manager =
        make_unique<ECUSleepWakeupManager>(
            vehicleEvents,
            seconds(5)
        );

    manager->processData();

    return 0;
}