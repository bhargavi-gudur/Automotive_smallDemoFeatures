/**
 * @file vehicle_gateway_router.cpp
 * @author Gandla Bhargavi
 * @brief Automotive vehicle gateway message router simulation
 * @date 20-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>
#include <iomanip>
#include <cstdint>

using namespace std;

// Represents a message traveling between vehicle networks.
struct VehicleMessage {
    string sourceNetwork;
    string destinationNetwork;
    uint32_t messageId;
    vector<uint8_t> payload;
};

// Defines an allowed routing rule.
struct RouteRule {
    string sourceNetwork;
    string destinationNetwork;
    unordered_set<uint32_t> allowedMessageIds;
};

// Abstract base class.
class GatewaySystem {
public:
    virtual void processData() = 0;

    virtual ~GatewaySystem() = default;
};

// Derived class.
class VehicleGatewayRouter : public GatewaySystem {
private:
    vector<string> networks;
    vector<RouteRule> routingRules;
    vector<VehicleMessage> messages;

    unordered_set<string> knownNetworks;

    unordered_map<string, int> statistics;

    // Find a matching source-to-destination rule.
    const RouteRule* findRoute(
        const string& source,
        const string& destination
    ) const {
        for (const auto& rule : routingRules) {
            if (rule.sourceNetwork == source &&
                rule.destinationNetwork == destination) {
                return &rule;
            }
        }

        return nullptr;
    }

    // Format the CAN identifier as hexadecimal.
    string formatMessageId(uint32_t id) const {
        const char* digits = "0123456789ABCDEF";

        string result = "0x";

        bool started = false;

        for (int shift = 28; shift >= 0; shift -= 4) {
            unsigned int nibble = (id >> shift) & 0xF;

            if (nibble != 0 || started || shift == 0) {
                result += digits[nibble];
                started = true;
            }
        }

        return result;
    }

    // Process one message.
    void routeMessage(const VehicleMessage& message) {
        cout << "\nMessage ID: "
             << formatMessageId(message.messageId) << '\n';

        cout << "Source: " << message.sourceNetwork << '\n';
        cout << "Destination: "
             << message.destinationNetwork << '\n';

        // Validate the source network.
        if (knownNetworks.count(message.sourceNetwork) == 0) {
            cout << "[BLOCKED] Unknown source network.\n";
            statistics["UnknownSource"]++;
            statistics["Blocked"]++;
            return;
        }

        // Validate the destination network.
        if (knownNetworks.count(message.destinationNetwork) == 0) {
            cout << "[BLOCKED] Unknown destination network.\n";
            statistics["UnknownDestination"]++;
            statistics["Blocked"]++;
            return;
        }

        // This simulation uses classic CAN payload limits.
        if (message.payload.size() > 8) {
            cout << "[BLOCKED] Invalid classic CAN payload length.\n";
            statistics["InvalidPayload"]++;
            statistics["Blocked"]++;
            return;
        }

        // Find the routing rule.
        const RouteRule* rule = findRoute(
            message.sourceNetwork,
            message.destinationNetwork
        );

        if (rule == nullptr) {
            cout << "[BLOCKED] No routing rule configured.\n";
            statistics["NoRoute"]++;
            statistics["Blocked"]++;
            return;
        }

        // Check whether this message ID is authorized.
        if (rule->allowedMessageIds.count(message.messageId) == 0) {
            cout << "[BLOCKED] Message ID is not authorized.\n";
            statistics["Unauthorized"]++;
            statistics["Blocked"]++;
            return;
        }

        // Forward the authorized message.
        cout << "[FORWARDED] Message routed successfully.\n";

        statistics["Forwarded"]++;
    }

public:
    VehicleGatewayRouter(
        const vector<string>& networkList,
        const vector<RouteRule>& rules,
        const vector<VehicleMessage>& incomingMessages
    )
        : networks(networkList),
          routingRules(rules),
          messages(incomingMessages) {

        for (const auto& network : networks) {
            knownNetworks.insert(network);
        }
    }

    void processData() override {
        cout << "AUTOMOTIVE VEHICLE GATEWAY ROUTER\n";
        cout << "========================================\n";

        cout << "Configured networks: "
             << networks.size() << '\n';

        cout << "Routing rules: "
             << routingRules.size() << '\n';

        cout << "\nProcessing messages...\n";

        for (const auto& message : messages) {
            routeMessage(message);
        }

        displaySummary();
    }

    void displaySummary() const {
        cout << "\n\nGATEWAY ROUTING SUMMARY\n";
        cout << "========================================\n";

        cout << left << setw(24) << "Total messages"
             << messages.size() << '\n';

        cout << left << setw(24) << "Forwarded"
             << getCount("Forwarded") << '\n';

        cout << left << setw(24) << "Blocked"
             << getCount("Blocked") << '\n';

        cout << "\nBlock reasons:\n";

        cout << left << setw(24) << "Unauthorized ID"
             << getCount("Unauthorized") << '\n';

        cout << left << setw(24) << "No routing rule"
             << getCount("NoRoute") << '\n';

        cout << left << setw(24) << "Invalid payload"
             << getCount("InvalidPayload") << '\n';

        cout << left << setw(24) << "Unknown source"
             << getCount("UnknownSource") << '\n';

        cout << left << setw(24) << "Unknown destination"
             << getCount("UnknownDestination") << '\n';
    }

private:
    int getCount(const string& key) const {
        auto it = statistics.find(key);

        return it != statistics.end() ? it->second : 0;
    }
};

int main() {
    // Networks present in the simulated vehicle.
    vector<string> networks = {
        "BodyCAN",
        "InfotainmentCAN",
        "PowertrainCAN",
        "GatewayCAN",
        "DiagnosticCAN"
    };

    // Define permitted message IDs for each route.
    vector<RouteRule> rules = {
        {
            "BodyCAN",
            "InfotainmentCAN",
            {0x120, 0x121}
        },
        {
            "PowertrainCAN",
            "GatewayCAN",
            {0x201}
        },
        {
            "DiagnosticCAN",
            "GatewayCAN",
            {0x700}
        }
    };

    // Simulated incoming messages.
    vector<VehicleMessage> messages = {
        {"BodyCAN", "InfotainmentCAN", 0x120,
            {0x10, 0x20, 0x30, 0x40}},

        {"PowertrainCAN", "GatewayCAN", 0x201,
            {0x01, 0x02, 0x03}},

        {"DiagnosticCAN", "GatewayCAN", 0x700,
            {0xAA, 0xBB}},

        // Unauthorized message ID.
        {"BodyCAN", "InfotainmentCAN", 0x555,
            {0x01, 0x02}},

        // No route configured for this pair.
        {"BodyCAN", "DiagnosticCAN", 0x120,
            {0x01}},

        // Invalid payload length for classic CAN.
        {"BodyCAN", "InfotainmentCAN", 0x120,
            {0, 1, 2, 3, 4, 5, 6, 7, 8}},

        // Unknown destination.
        {"BodyCAN", "UnknownCAN", 0x120,
            {0x01}}
    };

    unique_ptr<GatewaySystem> gateway =
        make_unique<VehicleGatewayRouter>(
            networks,
            rules,
            messages
        );

    gateway->processData();

    return 0;
}