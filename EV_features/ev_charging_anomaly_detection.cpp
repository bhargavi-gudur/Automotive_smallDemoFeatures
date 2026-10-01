/**
 * @file ev_charging_anomaly_detection.cpp
 * @author Gandla Bhargavi
 * @brief EV Charging Session Anomaly Detection using OOP and STL
 * @date 10-09-2026
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief Represents one EV charging session.
 */
struct ChargingSession
{
    int sessionId;
    double voltage;
    double current;
    double durationMinutes;
    double energyKWh;
};

/**
 * @brief Abstract base class for EV charging analytics.
 */
class ChargingAnalytics
{
public:
    virtual void processData() = 0;

    virtual ~ChargingAnalytics() = default;
};

/**
 * @brief Detects anomalies in EV charging sessions.
 */
class EVChargingAnomalyDetector : public ChargingAnalytics
{
private:
    vector<ChargingSession> sessions;

    unordered_map<string, double> limits =
    {
        {"MinVoltage", 200.0},
        {"MaxVoltage", 250.0},
        {"MaxCurrent", 32.0},
        {"MaxDuration", 480.0}
    };

    /**
     * @brief Calculates expected charging energy.
     */
    double calculateExpectedEnergy(
        const ChargingSession& session) const
    {
        /*
         * Energy(kWh) =
         * Voltage(V) × Current(A) × Time(h) / 1000
         */
        return (session.voltage *
                session.current *
                (session.durationMinutes / 60.0)) / 1000.0;
    }

    /**
     * @brief Determines whether a charging session is abnormal.
     */
    bool isAnomalous(const ChargingSession& session) const
    {
        const double expectedEnergy =
            calculateExpectedEnergy(session);

        const double energyDifference =
            abs(session.energyKWh - expectedEnergy);

        const bool voltageAbnormal =
            session.voltage < limits.at("MinVoltage") ||
            session.voltage > limits.at("MaxVoltage");

        const bool currentAbnormal =
            session.current > limits.at("MaxCurrent");

        const bool durationAbnormal =
            session.durationMinutes >
            limits.at("MaxDuration");

        /*
         * Allow a small measurement difference because
         * practical charging measurements are not ideal.
         */
        const bool energyAbnormal =
            energyDifference > 2.0;

        return voltageAbnormal ||
               currentAbnormal ||
               durationAbnormal ||
               energyAbnormal;
    }

    /**
     * @brief Generates an explanation for an anomaly.
     */
    vector<string> getAnomalyReasons(
        const ChargingSession& session) const
    {
        vector<string> reasons;

        if (session.voltage < limits.at("MinVoltage"))
        {
            reasons.push_back("Low charging voltage");
        }

        if (session.voltage > limits.at("MaxVoltage"))
        {
            reasons.push_back("High charging voltage");
        }

        if (session.current > limits.at("MaxCurrent"))
        {
            reasons.push_back("Excessive charging current");
        }

        if (session.durationMinutes >
            limits.at("MaxDuration"))
        {
            reasons.push_back("Charging duration too long");
        }

        const double expectedEnergy =
            calculateExpectedEnergy(session);

        if (abs(session.energyKWh - expectedEnergy) > 2.0)
        {
            reasons.push_back("Energy measurement mismatch");
        }

        return reasons;
    }

    /**
     * @brief Calculates average delivered energy.
     */
    double calculateAverageEnergy() const
    {
        if (sessions.empty())
        {
            return 0.0;
        }

        const double totalEnergy = accumulate(
            sessions.begin(),
            sessions.end(),
            0.0,
            [](double total,
               const ChargingSession& session)
            {
                return total + session.energyKWh;
            });

        return totalEnergy / sessions.size();
    }

public:
    /**
     * @brief Adds a charging session.
     */
    void addSession(const ChargingSession& session)
    {
        if (session.voltage > 0.0 &&
            session.current >= 0.0 &&
            session.durationMinutes > 0.0 &&
            session.energyKWh >= 0.0)
        {
            sessions.push_back(session);
        }
    }

    /**
     * @brief Processes all charging sessions.
     */
    void processData() override
    {
        if (sessions.empty())
        {
            cout << "No charging session data available.\n";
            return;
        }

        cout << "\n===== EV CHARGING ANOMALY DETECTION =====\n";

        cout << fixed << setprecision(2);

        int anomalyCount = 0;

        for (const auto& session : sessions)
        {
            const double expectedEnergy =
                calculateExpectedEnergy(session);

            cout << "\nSession ID: "
                 << session.sessionId;

            cout << "\nVoltage: "
                 << session.voltage
                 << " V";

            cout << "\nCurrent: "
                 << session.current
                 << " A";

            cout << "\nDuration: "
                 << session.durationMinutes
                 << " minutes";

            cout << "\nMeasured Energy: "
                 << session.energyKWh
                 << " kWh";

            cout << "\nExpected Energy: "
                 << expectedEnergy
                 << " kWh";

            if (isAnomalous(session))
            {
                ++anomalyCount;

                cout << "\nStatus: ANOMALY DETECTED";

                const auto reasons =
                    getAnomalyReasons(session);

                cout << "\nReasons:";

                for (const auto& reason : reasons)
                {
                    cout << "\n- " << reason;
                }
            }
            else
            {
                cout << "\nStatus: NORMAL";
            }

            cout << '\n';
        }

        cout << "\n===== CHARGING SUMMARY =====\n";

        cout << "Total Sessions: "
             << sessions.size();

        cout << "\nAnomalous Sessions: "
             << anomalyCount;

        cout << "\nNormal Sessions: "
             << sessions.size() - anomalyCount;

        cout << "\nAverage Energy Delivered: "
             << calculateAverageEnergy()
             << " kWh";

        if (anomalyCount > 0)
        {
            cout << "\nOverall Status: "
                 << "CHARGING SYSTEM REQUIRES ATTENTION";
        }
        else
        {
            cout << "\nOverall Status: "
                 << "CHARGING SYSTEM NORMAL";
        }

        cout << '\n';
    }
};

int main()
{
    EVChargingAnomalyDetector detector;

    vector<ChargingSession> chargingData =
    {
        // ID, Voltage, Current, Duration, Measured Energy
        {101, 230.0, 16.0, 120.0, 7.36},
        {102, 235.0, 24.0, 180.0, 16.92},
        {103, 190.0, 20.0, 150.0, 9.50},
        {104, 240.0, 38.0, 120.0, 10.50},
        {105, 225.0, 16.0, 600.0, 36.00}
    };

    for (const auto& session : chargingData)
    {
        detector.addSession(session);
    }

    ChargingAnalytics* system = &detector;

    system->processData();

    return 0;
}