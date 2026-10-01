/**
 * @file ev_dtc_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an Electric Vehicle Diagnostic Trouble Code
 *   (DTC) Management System.
 *
 *   Features:
 *   - Store DTC information
 *   - Search DTC by code
 *   - Display DTC description
 *   - Display severity
 *   - Display recommended action
 *   - Generate diagnostic summary
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL unordered_map
 *   - STL optional
 *   - STL vector
 *   - STL algorithms
 *
 * @date 01-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @struct DTCInfo
 * @brief Stores information about a diagnostic trouble code.
 */
struct DTCInfo
{
    string description;
    string severity;
    string action;
};

/**
 * @class EVSystem
 * @brief Abstract base class for EV diagnostic systems.
 */
class EVSystem
{
public:

    /**
     * @brief Process diagnostic information.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~EVSystem() = default;
};

/**
 * @class EV_DTC_Manager
 * @brief Manages EV Diagnostic Trouble Codes.
 */
class EV_DTC_Manager : public EVSystem
{
private:

    /**
     * @brief DTC database.
     *
     * Key   -> DTC code
     * Value -> DTC information
     */
    unordered_map<string, DTCInfo> dtcDatabase
    {
        {
            "P0A80",
            {
                "Replace Hybrid/Electric Vehicle Battery Pack",
                "CRITICAL",
                "Inspect battery pack and BMS"
            }
        },
        {
            "P0AA6",
            {
                "High Voltage System Insulation Fault",
                "CRITICAL",
                "Inspect HV insulation and isolation"
            }
        },
        {
            "P0C78",
            {
                "Drive Motor Temperature Too High",
                "HIGH",
                "Check motor cooling system"
            }
        },
        {
            "P0D00",
            {
                "Charging System Fault",
                "HIGH",
                "Inspect charging system and connector"
            }
        },
        {
            "P0562",
            {
                "System Voltage Low",
                "MEDIUM",
                "Check 12V battery and charging circuit"
            }
        },
        {
            "P1A10",
            {
                "Battery Management System Fault",
                "HIGH",
                "Perform BMS diagnostic check"
            }
        }
    };

    /**
     * @brief Returns DTC information if the code exists.
     */
    optional<DTCInfo> findDTC(
        const string& code) const
    {
        const auto it =
            dtcDatabase.find(code);

        if(it == dtcDatabase.end())
        {
            return nullopt;
        }

        return it->second;
    }

    /**
     * @brief Returns severity score.
     */
    int severityScore(
        const string& severity) const
    {
        if(severity == "CRITICAL")
        {
            return 3;
        }

        if(severity == "HIGH")
        {
            return 2;
        }

        return 1;
    }

public:

    /**
     * @brief Process predefined DTCs.
     */
    void processData() override
    {
        cout << "===== EV Diagnostic Trouble Code Manager =====\n";

        vector<string> activeDTCs
        {
            "P0AA6",
            "P0C78",
            "P0562",
            "P1234"
        };

        cout << "\nActive DTCs:\n";

        for(const string& code : activeDTCs)
        {
            const auto result =
                findDTC(code);

            cout << "\nDTC Code: "
                 << code
                 << endl;

            if(!result.has_value())
            {
                cout << "Status      : UNKNOWN DTC\n";
                cout << "Description : Code not available in database\n";
                continue;
            }

            const DTCInfo& info =
                result.value();

            cout << "Status      : IDENTIFIED\n";

            cout << "Description : "
                 << info.description
                 << endl;

            cout << "Severity    : "
                 << info.severity
                 << endl;

            cout << "Action      : "
                 << info.action
                 << endl;
        }

        /*
         * Find the most severe active DTC.
         */
        auto mostSevere =
            max_element(
                activeDTCs.begin(),
                activeDTCs.end(),
                [this](const string& first,
                       const string& second)
                {
                    const auto firstDTC =
                        findDTC(first);

                    const auto secondDTC =
                        findDTC(second);

                    const int firstScore =
                        firstDTC.has_value()
                            ? severityScore(
                                firstDTC->severity)
                            : 0;

                    const int secondScore =
                        secondDTC.has_value()
                            ? severityScore(
                                secondDTC->severity)
                            : 0;

                    return firstScore < secondScore;
                }
            );

        cout << "\n===== Diagnostic Summary =====\n";

        if(mostSevere != activeDTCs.end())
        {
            const auto result =
                findDTC(*mostSevere);

            if(result.has_value())
            {
                cout << "Most Severe DTC : "
                     << *mostSevere
                     << endl;

                cout << "Severity         : "
                     << result->severity
                     << endl;

                cout << "Recommended      : "
                     << result->action
                     << endl;
            }
        }

        /*
         * Check whether immediate attention is required.
         */
        const bool criticalFound =
            any_of(
                activeDTCs.begin(),
                activeDTCs.end(),
                [this](const string& code)
                {
                    const auto result =
                        findDTC(code);

                    return result.has_value() &&
                           result->severity == "CRITICAL";
                }
            );

        cout << "\nVehicle Status: ";

        if(criticalFound)
        {
            cout << "⚠️ CRITICAL FAULT - SERVICE REQUIRED";
        }
        else
        {
            cout << "MONITORING REQUIRED";
        }

        cout << endl;
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    EVSystem* ev =
        new EV_DTC_Manager();

    ev->processData();

    delete ev;

    return 0;
}