/**
 * @file automotive_dtc_priority_manager.cpp
 * @author Gandla Bhargavi
 * @brief Prioritizes automotive DTCs and escalates repeated faults.
 * @date 24-10-2026
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class Severity {
    INFO = 1,
    WARNING = 2,
    CRITICAL = 3
};

struct DTCEvent {
    std::string code;
    std::string description;
    Severity severity;
};

struct DTCRecord {
    std::string code;
    std::string description;
    Severity baseSeverity;
    Severity currentSeverity;
    int occurrences = 0;
};

class DiagnosticManager {
public:
    virtual void processEvent(const DTCEvent& event) = 0;
    virtual void printPriorityReport() const = 0;

    virtual ~DiagnosticManager() = default;
};

class DTCPriorityManager : public DiagnosticManager {
private:
    std::map<std::string, DTCRecord> records;

    static int severityRank(Severity severity) {
        return static_cast<int>(severity);
    }

    static std::string severityToString(Severity severity) {
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

    static Severity higherSeverity(Severity first, Severity second) {
        return severityRank(first) >= severityRank(second)
            ? first
            : second;
    }

    static Severity calculateSeverity(const DTCRecord& record) {
        Severity result = record.baseSeverity;

        // Educational escalation rules:
        // 2 or more occurrences: at least WARNING.
        // 3 or more occurrences: CRITICAL.
        if (record.occurrences >= 3) {
            result = higherSeverity(result, Severity::CRITICAL);
        } else if (record.occurrences >= 2) {
            result = higherSeverity(result, Severity::WARNING);
        }

        return result;
    }

public:
    void processEvent(const DTCEvent& event) override {
        auto it = records.find(event.code);

        if (it == records.end()) {
            DTCRecord newRecord{
                event.code,
                event.description,
                event.severity,
                event.severity,
                0
            };

            it = records.emplace(event.code, newRecord).first;
        }

        DTCRecord& record = it->second;

        // Keep the more severe base classification if the same
        // DTC is received with different severity classifications.
        record.baseSeverity =
            higherSeverity(record.baseSeverity, event.severity);

        ++record.occurrences;
        record.currentSeverity = calculateSeverity(record);

        std::cout << "DTC: " << record.code
                  << " | Occurrences: " << record.occurrences
                  << " | Priority: "
                  << severityToString(record.currentSeverity)
                  << '\n';
    }

    void printPriorityReport() const override {
        std::vector<DTCRecord> sortedRecords;

        for (const auto& entry : records) {
            sortedRecords.push_back(entry.second);
        }

        // Highest severity first, then most occurrences,
        // then DTC code alphabetically.
        std::sort(
            sortedRecords.begin(),
            sortedRecords.end(),
            [](const DTCRecord& first, const DTCRecord& second) {
                if (first.currentSeverity != second.currentSeverity) {
                    return severityRank(first.currentSeverity) >
                           severityRank(second.currentSeverity);
                }

                if (first.occurrences != second.occurrences) {
                    return first.occurrences > second.occurrences;
                }

                return first.code < second.code;
            }
        );

        std::cout << "\n===== DTC PRIORITY REPORT =====\n";

        if (sortedRecords.empty()) {
            std::cout << "No diagnostic faults recorded.\n";
        }

        for (const DTCRecord& record : sortedRecords) {
            std::cout << record.code
                      << " | " << record.description
                      << " | Priority: "
                      << severityToString(record.currentSeverity)
                      << " | Occurrences: "
                      << record.occurrences
                      << '\n';
        }

        std::cout << "===============================\n";
    }
};

int main() {
    DTCPriorityManager manager;

    const std::vector<DTCEvent> events = {
        {"P0130", "Oxygen sensor circuit", Severity::WARNING},
        {"C1234", "Brake system fault", Severity::CRITICAL},
        {"P0130", "Oxygen sensor circuit", Severity::WARNING},
        {"U0100", "ECU communication loss", Severity::WARNING},
        {"P0130", "Oxygen sensor circuit", Severity::WARNING},
        {"U0100", "ECU communication loss", Severity::WARNING},
        {"B1010", "Cabin sensor alert", Severity::INFO}
    };

    std::cout << "Automotive DTC Priority Manager\n\n";

    for (const DTCEvent& event : events) {
        manager.processEvent(event);
    }

    manager.printPriorityReport();

    return 0;
}