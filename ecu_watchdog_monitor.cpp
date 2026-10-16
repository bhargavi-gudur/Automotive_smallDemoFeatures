/**
 * @file ecu_watchdog_monitor.cpp
 * @author Gandla Bhargavi
 * @brief Automotive ECU watchdog and task heartbeat monitor
 * @date 16-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <memory>
#include <iomanip>

using namespace std;
using namespace chrono;

// Heartbeat event
struct HeartbeatEvent {
    string taskName;
    int timeMs;
};

// ECU task information
struct TaskState {
    milliseconds timeout;
    milliseconds lastHeartbeat;
    int faultCount;
    bool faulted;
};

// Abstract base class
class ECUWatchdog {
public:
    virtual void processData() = 0;

    virtual ~ECUWatchdog() = default;
};

// Derived class
class WatchdogMonitor : public ECUWatchdog {
private:
    vector<string> taskNames;
    vector<HeartbeatEvent> events;
    unordered_map<string, TaskState> tasks;

public:
    WatchdogMonitor() {
        // Configure ECU tasks and their timeout limits.
        taskNames = {
            "SensorTask",
            "CommunicationTask",
            "DiagnosticTask"
        };

        tasks["SensorTask"] = {
            milliseconds(150), milliseconds(0), 0, false
        };

        tasks["CommunicationTask"] = {
            milliseconds(200), milliseconds(0), 0, false
        };

        tasks["DiagnosticTask"] = {
            milliseconds(250), milliseconds(0), 0, false
        };

        // Simulated heartbeat events.
        events = {
            {"SensorTask", 50},
            {"SensorTask", 100},
            {"CommunicationTask", 100},
            {"SensorTask", 150},
            {"SensorTask", 200},
            {"SensorTask", 250},
            {"SensorTask", 300},
            {"CommunicationTask", 400}
        };
    }

    // Process a heartbeat from an ECU task.
    void receiveHeartbeat(
        const string& taskName,
        milliseconds currentTime
    ) {
        auto it = tasks.find(taskName);

        if (it == tasks.end()) {
            cout << "[ERROR] Unknown task: "
                 << taskName << "\n";
            return;
        }

        TaskState& task = it->second;

        // A heartbeat after a fault indicates recovery.
        if (task.faulted) {
            cout << "[RECOVERY] " << taskName
                 << " responded again at "
                 << currentTime.count() << " ms\n";
        }

        task.lastHeartbeat = currentTime;
        task.faulted = false;
    }

    // Check whether any ECU task has timed out.
    void checkTimeouts(milliseconds currentTime) {
        for (const string& name : taskNames) {
            TaskState& task = tasks.at(name);

            milliseconds elapsed =
                currentTime - task.lastHeartbeat;

            if (elapsed > task.timeout && !task.faulted) {
                task.faulted = true;
                task.faultCount++;

                cout << "[TIMEOUT] " << name
                     << " missed its heartbeat. "
                     << "Elapsed: " << elapsed.count()
                     << " ms, Limit: "
                     << task.timeout.count() << " ms\n";
            }
        }
    }

    // Display final task status.
    void displaySummary() const {
        cout << "\nECU WATCHDOG SUMMARY\n";
        cout << "-----------------------------------------------\n";

        cout << left
             << setw(24) << "Task"
             << setw(16) << "Status"
             << "Fault Count\n";

        cout << "-----------------------------------------------\n";

        for (const string& name : taskNames) {
            const TaskState& task = tasks.at(name);

            cout << left
                 << setw(24) << name
                 << setw(16)
                 << (task.faulted ? "FAULT" : "ACTIVE")
                 << task.faultCount << "\n";
        }
    }

    // Polymorphic interface implementation.
    void processData() override {
        cout << "AUTOMOTIVE ECU WATCHDOG MONITOR\n";
        cout << "===============================================\n";

        size_t eventIndex = 0;

        // Simulated clock: 0 to 400 ms in 50 ms steps.
        for (int timeMs = 0; timeMs <= 400; timeMs += 50) {
            milliseconds currentTime(timeMs);

            // Process all heartbeats scheduled for this time.
            while (
                eventIndex < events.size() &&
                events[eventIndex].timeMs == timeMs
            ) {
                receiveHeartbeat(
                    events[eventIndex].taskName,
                    currentTime
                );

                eventIndex++;
            }

            // Check for missing heartbeats.
            checkTimeouts(currentTime);
        }

        displaySummary();
    }
};

int main() {
    // Base-class pointer demonstrates runtime polymorphism.
    unique_ptr<ECUWatchdog> watchdog =
        make_unique<WatchdogMonitor>();

    watchdog->processData();

    return 0;
}