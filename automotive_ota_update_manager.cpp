/**
 * @file automotive_ota_update_manager.cpp
 * @author Gandla Bhargavi
 * @brief Automotive ECU OTA firmware update manager simulation
 * @date 18-10-2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

// Firmware update states
enum class UpdateState {
    Idle,
    Downloading,
    Verifying,
    ReadyToInstall,
    Installing,
    Completed,
    RolledBack,
    Failed
};

// Firmware package information
struct FirmwarePackage {
    string targetECU;
    string currentVersion;
    string newVersion;

    bool compatible;
    bool signatureValid;
    bool checksumValid;
    bool installationSucceeds;
};

// Abstract base class
class OTAUpdateSystem {
public:
    virtual void processData() = 0;

    virtual ~OTAUpdateSystem() = default;
};

// Derived class
class OTAUpdateManager : public OTAUpdateSystem {
private:
    FirmwarePackage package;
    UpdateState state;

    vector<string> eventLog;
    unordered_map<string, int> eventCounts;

    string installedVersion;

    void logEvent(const string& message) {
        eventLog.push_back(message);
        eventCounts[message]++;
        cout << message << '\n';
    }

    string stateToString(UpdateState currentState) const {
        switch (currentState) {
            case UpdateState::Idle:
                return "IDLE";

            case UpdateState::Downloading:
                return "DOWNLOADING";

            case UpdateState::Verifying:
                return "VERIFYING";

            case UpdateState::ReadyToInstall:
                return "READY TO INSTALL";

            case UpdateState::Installing:
                return "INSTALLING";

            case UpdateState::Completed:
                return "COMPLETED";

            case UpdateState::RolledBack:
                return "ROLLED BACK";

            case UpdateState::Failed:
                return "FAILED";
        }

        return "UNKNOWN";
    }

public:
    explicit OTAUpdateManager(const FirmwarePackage& firmware)
        : package(firmware),
          state(UpdateState::Idle),
          installedVersion(firmware.currentVersion) {
    }

    void processData() override {
        cout << "\n========================================\n";
        cout << "AUTOMOTIVE OTA UPDATE MANAGER\n";
        cout << "========================================\n";

        cout << "Target ECU: " << package.targetECU << '\n';
        cout << "Current version: "
             << installedVersion << '\n';

        cout << "New version: "
             << package.newVersion << "\n\n";

        // Step 1: Check compatibility
        if (!package.compatible) {
            state = UpdateState::Failed;
            logEvent("[ERROR] Firmware is incompatible.");
            showSummary();
            return;
        }

        logEvent("[OK] Firmware compatibility verified.");

        // Step 2: Simulate downloading firmware
        state = UpdateState::Downloading;
        logEvent("[DOWNLOAD] Firmware downloaded.");

        // Step 3: Verify firmware integrity and signature
        state = UpdateState::Verifying;

        logEvent("[VERIFY] Checking firmware signature.");

        if (!package.signatureValid) {
            state = UpdateState::Failed;
            logEvent("[ERROR] Firmware signature verification failed.");
            showSummary();
            return;
        }

        logEvent("[OK] Firmware signature verified.");

        logEvent("[VERIFY] Checking firmware checksum.");

        if (!package.checksumValid) {
            state = UpdateState::Failed;
            logEvent("[ERROR] Firmware integrity check failed.");
            showSummary();
            return;
        }

        logEvent("[OK] Firmware integrity verified.");

        // Step 4: Firmware is ready for installation
        state = UpdateState::ReadyToInstall;
        logEvent("[OK] Firmware is ready to install.");

        // Step 5: Simulate installation
        state = UpdateState::Installing;
        logEvent("[INSTALL] Starting firmware installation.");

        if (!package.installationSucceeds) {
            logEvent("[ERROR] Installation failed.");

            // Simulate restoring the previous firmware.
            installedVersion = package.currentVersion;
            state = UpdateState::RolledBack;

            logEvent("[ROLLBACK] Previous firmware restored.");

            showSummary();
            return;
        }

        // Step 6: Update completed
        installedVersion = package.newVersion;
        state = UpdateState::Completed;

        logEvent("[SUCCESS] Firmware update completed.");

        showSummary();
    }

    void showSummary() const {
        cout << "\n--- Update Summary ---\n";

        cout << "Final state: "
             << stateToString(state) << '\n';

        cout << "Installed version: "
             << installedVersion << '\n';

        cout << "Events recorded: "
             << eventLog.size() << '\n';

        cout << "\nEvent counts:\n";

        for (const auto& entry : eventCounts) {
            cout << entry.first
                 << ": " << entry.second << '\n';
        }
    }
};

int main() {
    // Scenario 1: Successful firmware update
    FirmwarePackage successfulUpdate = {
        "BodyControlECU",
        "1.0.0",
        "1.1.0",
        true,   // Compatible
        true,   // Signature valid
        true,   // Checksum valid
        true    // Installation succeeds
    };

    // Scenario 2: Installation failure with rollback
    FirmwarePackage failedUpdate = {
        "GatewayECU",
        "2.0.0",
        "2.1.0",
        true,   // Compatible
        true,   // Signature valid
        true,   // Checksum valid
        false   // Installation fails
    };

    unique_ptr<OTAUpdateSystem> update1 =
        make_unique<OTAUpdateManager>(successfulUpdate);

    unique_ptr<OTAUpdateSystem> update2 =
        make_unique<OTAUpdateManager>(failedUpdate);

    cout << "SCENARIO 1: SUCCESSFUL UPDATE\n";
    update1->processData();

    cout << "\nSCENARIO 2: FAILED UPDATE\n";
    update2->processData();

    return 0;
}