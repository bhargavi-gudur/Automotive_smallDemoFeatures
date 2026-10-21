/**
 * @file automotive_fault_memory_logger.cpp
 * @author Gandla Bhargavi
 * @brief Automotive fault memory and diagnostic event logger
 * @date 21-10-2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iomanip>

using namespace std;

// Fault severity levels
enum class Severity {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

// Information about an active fault
struct FaultRecord {
    string code;
    string description;
    Severity severity;
    int firstSeen;
    int lastSeen;
    int occurrences;
};

// Diagnostic history event
struct DiagnosticEvent {
    int timestamp;
    string action;
    string faultCode;
};

// Abstract base class
class DiagnosticSystem {
public:
    virtual void processData() = 0;

    virtual ~DiagnosticSystem() = default;
};

// Derived class
class FaultMemoryLogger : public DiagnosticSystem {
private:
    // Currently active faults, indexed by DTC.
    map<string, FaultRecord> activeFaults;

    // Lifetime occurrence count for each fault code.
    map<string, int> lifetimeCounts;

    // Historical diagnostic events.
    vector<DiagnosticEvent> eventHistory;

    // Convert severity to readable text.
    string severityToString(Severity severity) const {
        switch (severity) {
            case Severity::INFO:
                return "INFO";

            case Severity::WARNING:
                return "WARNING";

            case Severity::ERROR:
                return "ERROR";

            case Severity::CRITICAL:
                return "CRITICAL";
        }

        return "UNKNOWN";
    }

    // Record a diagnostic event.
    void addEvent(
        int timestamp,
        const string& action,
        const string& code
    ) {
        eventHistory.push_back({
            timestamp,
            action,
            code
        });
    }

public:
    // Record a new fault or update an existing active fault.
    void recordFault(
        const string& code,
        const string& description,
        Severity severity,
        int timestamp
    ) {
        auto it = activeFaults.find(code);

        if (it != activeFaults.end()) {
            // Fault is already active.
            FaultRecord& fault = it->second;

            fault.lastSeen = timestamp;
            fault.severity = severity;
            fault.description = description;
            fault.occurrences++;

            lifetimeCounts[code]++;

            addEvent(timestamp, "REPEATED", code);

            cout << "[REPEATED] " << code
                 << " | Occurrences: "
                 << fault.occurrences << '\n';
        } else {
            // First occurrence in the current active period.
            int count = ++lifetimeCounts[code];

            FaultRecord fault = {
                code,
                description,
                severity,
                timestamp,
                timestamp,
                count
            };

            activeFaults[code] = fault;

            addEvent(timestamp, "DETECTED", code);

            cout << "[DETECTED] " << code
                 << " | Severity: "
                 << severityToString(severity) << '\n';
        }
    }

    // Clear an active fault.
    void clearFault(
        const string& code,
        int timestamp
    ) {
        auto it = activeFaults.find(code);

        if (it == activeFaults.end()) {
            cout << "[NOT FOUND] No active fault: "
                 << code << '\n';
            return;
        }

        addEvent(timestamp, "CLEARED", code);

        activeFaults.erase(it);

        cout << "[CLEARED] " << code
             << " at " << timestamp << " s\n";
    }

    // Display all currently active faults.
    void displayActiveFaults() const {
        cout << "\nACTIVE FAULT MEMORY\n";
        cout << string(90, '-') << '\n';

        cout << left
             << setw(12) << "DTC"
             << setw(30) << "Description"
             << setw(12) << "Severity"
             << setw(12) << "Occurrences"
             << setw(12) << "First Seen"
             << "Last Seen\n";

        cout << string(90, '-') << '\n';

        if (activeFaults.empty()) {
            cout << "No active faults.\n";
            return;
        }

        for (const auto& entry : activeFaults) {
            const FaultRecord& fault = entry.second;

            cout << left
                 << setw(12) << fault.code
                 << setw(30) << fault.description
                 << setw(12)
                 << severityToString(fault.severity)
                 << setw(12) << fault.occurrences
                 << setw(12) << fault.firstSeen
                 << fault.lastSeen << '\n';
        }
    }

    // Display the diagnostic event history.
    void displayHistory() const {
        cout << "\nDIAGNOSTIC EVENT HISTORY\n";
        cout << string(55, '-') << '\n';

        cout << left
             << setw(15) << "Timestamp"
             << setw(18) << "Action"
             << "DTC\n";

        cout << string(55, '-') << '\n';

        for (const auto& event : eventHistory) {
            cout << left
                 << setw(15) << event.timestamp
                 << setw(18) << event.action
                 << event.faultCode << '\n';
        }
    }

    // Display overall statistics.
    void displaySummary() const {
        cout << "\nDIAGNOSTIC SUMMARY\n";
        cout << "-----------------------------\n";

        cout << "Active faults: "
             << activeFaults.size() << '\n';

        cout << "Historical events: "
             << eventHistory.size() << '\n';

        cout << "\nLifetime fault occurrences:\n";

        for (const auto& entry : lifetimeCounts) {
            cout << entry.first
                 << ": " << entry.second << '\n';
        }
    }

    // Implement abstract base-class interface.
    void processData() override {
        cout << "AUTOMOTIVE FAULT MEMORY LOGGER\n";
        cout << "========================================\n";

        // Simulated diagnostic events.
        recordFault(
            "P0128",
            "Coolant Temperature",
            Severity::WARNING,
            100
        );

        recordFault(
            "U0100",
            "Communication Lost",
            Severity::ERROR,
            120
        );

        recordFault(
            "P0128",
            "Coolant Temperature",
            Severity::WARNING,
            150
        );

        recordFault(
            "B1001",
            "Body Control Fault",
            Severity::INFO,
            180
        );

        clearFault("U0100", 220);

        // The same fault occurs again after being cleared.
        recordFault(
            "U0100",
            "Communication Lost",
            Severity::ERROR,
            250
        );

        displayActiveFaults();
        displayHistory();
        displaySummary();
    }
};

int main() {
    unique_ptr<DiagnosticSystem> logger =
        make_unique<FaultMemoryLogger>();

    logger->processData();

    return 0;
}