
   /**
 * @file automotive_ecu_configuration_manager.cpp
 * @author Gandla Bhargavi
 * @brief Manages ECU configuration parameters, validation, and history.
 * @date 26-10-2026
 */

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct ConfigurationParameter {
    std::string name;
    double value;
    double minimum;
    double maximum;
};

struct ConfigurationChange {
    std::string parameterName;
    double oldValue;
    double newValue;
    bool accepted;
    std::string message;
    int version;
};

// Abstract interface
class ConfigurationManager {
public:
    virtual bool updateParameter(
        const std::string& name,
        double newValue
    ) = 0;

    virtual void printConfiguration() const = 0;
    virtual void printHistory() const = 0;

    virtual ~ConfigurationManager() = default;
};

class ECUConfigurationManager : public ConfigurationManager {
private:
    std::map<std::string, ConfigurationParameter> parameters;
    std::vector<ConfigurationChange> history;
    int configurationVersion = 1;

public:
    bool addParameter(
        const std::string& name,
        double initialValue,
        double minimum,
        double maximum
    ) {
        if (name.empty() ||
            !std::isfinite(initialValue) ||
            !std::isfinite(minimum) ||
            !std::isfinite(maximum) ||
            minimum > maximum ||
            initialValue < minimum ||
            initialValue > maximum ||
            parameters.find(name) != parameters.end()) {
            std::cout << "Configuration rejected for " << name
                      << ": invalid definition.\n";
            return false;
        }

        parameters.emplace(
            name,
            ConfigurationParameter{
                name, initialValue, minimum, maximum
            }
        );

        std::cout << "Parameter registered: " << name
                  << " = " << initialValue << '\n';

        return true;
    }

    bool updateParameter(
        const std::string& name,
        double newValue
    ) override {
        auto it = parameters.find(name);

        if (it == parameters.end()) {
            history.push_back({
                name, 0.0, newValue, false,
                "Unknown parameter", configurationVersion
            });

            std::cout << "Update rejected: unknown parameter "
                      << name << '\n';
            return false;
        }

        ConfigurationParameter& parameter = it->second;
        const double oldValue = parameter.value;

        if (!std::isfinite(newValue) ||
            newValue < parameter.minimum ||
            newValue > parameter.maximum) {
            history.push_back({
                name, oldValue, newValue, false,
                "Value outside permitted range",
                configurationVersion
            });

            std::cout << "Update rejected: " << name
                      << " value is outside permitted range.\n";
            return false;
        }

        if (newValue == oldValue) {
            history.push_back({
                name, oldValue, newValue, true,
                "No change required", configurationVersion
            });

            std::cout << "No change: " << name
                      << " is already " << oldValue << '\n';
            return true;
        }

        parameter.value = newValue;
        ++configurationVersion;

        history.push_back({
            name, oldValue, newValue, true,
            "Configuration updated", configurationVersion
        });

        std::cout << "Update accepted: " << name
                  << " changed from " << oldValue
                  << " to " << newValue
                  << " | Version: " << configurationVersion
                  << '\n';

        return true;
    }

    void printConfiguration() const override {
        std::cout << "\n===== ECU CONFIGURATION =====\n";
        std::cout << "Configuration version: "
                  << configurationVersion << '\n';

        for (const auto& entry : parameters) {
            const ConfigurationParameter& parameter = entry.second;

            std::cout << parameter.name
                      << " = " << parameter.value
                      << " (Range: " << parameter.minimum
                      << " to " << parameter.maximum << ")\n";
        }

        std::cout << "=============================\n";
    }

    void printHistory() const override {
        std::cout << "\n===== CONFIGURATION HISTORY =====\n";

        if (history.empty()) {
            std::cout << "No configuration changes recorded.\n";
        }

        for (const ConfigurationChange& change : history) {
            std::cout << change.parameterName
                      << " | " << (change.accepted ? "ACCEPTED" : "REJECTED")
                      << " | " << change.message
                      << " | Version: " << change.version
                      << '\n';
        }

        std::cout << "=================================\n";
    }
};

int main() {
    ECUConfigurationManager concreteManager;
    ConfigurationManager& manager = concreteManager;

    std::cout << "Automotive ECU Configuration Manager\n\n";

    concreteManager.addParameter("IdleSpeedRPM", 800, 600, 1200);
    concreteManager.addParameter("FanOnTempC", 95, 80, 110);
    concreteManager.addParameter("CabinTargetTempC", 22, 16, 30);

    std::cout << "\nApplying configuration updates...\n";

    manager.updateParameter("IdleSpeedRPM", 900);
    manager.updateParameter("FanOnTempC", 120);
    manager.updateParameter("CabinTargetTempC", 24);
    manager.updateParameter("UnknownParameter", 10);

    manager.printConfiguration();
    manager.printHistory();

    return 0;
}    