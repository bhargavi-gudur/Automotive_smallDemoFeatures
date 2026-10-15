/**
 * @file smart_parking_management.cpp
 * @author Gandla Bhargavi
 * @brief Smart parking management system for automobiles
 * @date 15-10-2026
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <iomanip>

using namespace std;

// Vehicle information
struct Vehicle {
    string registrationNumber;
    string vehicleType;
    int entryHour;
};

// Abstract base class
class ParkingSystem {
public:
    virtual void processData() = 0;

    virtual ~ParkingSystem() = default;
};

// Derived class
class SmartParking : public ParkingSystem {
private:
    vector<int> slots;
    unordered_map<string, Vehicle> parkedVehicles;
    double hourlyRate;

public:
    SmartParking(int totalSlots, double rate)
        : slots(totalSlots, 0), hourlyRate(rate) {
    }

    // Find the nearest available slot
    int findAvailableSlot() const {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i] == 0) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    // Vehicle entry
    void parkVehicle(const Vehicle& vehicle) {
        if (parkedVehicles.count(vehicle.registrationNumber)) {
            cout << "Vehicle is already parked.\n";
            return;
        }

        int slot = findAvailableSlot();

        if (slot == -1) {
            cout << "Parking is full for vehicle "
                 << vehicle.registrationNumber << ".\n";
            return;
        }

        slots[slot] = 1;
        parkedVehicles[vehicle.registrationNumber] = vehicle;

        cout << "Vehicle " << vehicle.registrationNumber
             << " parked in slot " << slot + 1 << ".\n";
    }

    // Vehicle exit and fee calculation
    void exitVehicle(
        const string& registrationNumber,
        int exitHour
    ) {
        auto it = parkedVehicles.find(registrationNumber);

        if (it == parkedVehicles.end()) {
            cout << "Vehicle not found.\n";
            return;
        }

        int duration = exitHour - it->second.entryHour;

        if (duration < 0) {
            cout << "Invalid exit time.\n";
            return;
        }

        // Charge at least one hour, rounding partial hours up.
        int billableHours = duration == 0
            ? 1
            : duration;

        double fee = billableHours * hourlyRate;

        cout << fixed << setprecision(2);
        cout << "Vehicle: " << registrationNumber << "\n";
        cout << "Parking duration: " << duration << " hour(s)\n";
        cout << "Parking fee: Rs. " << fee << "\n";

        // Free the slot
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i] == 1) {
                // Find the vehicle's assigned slot.
                // Slot assignment is tracked separately below
                // in a production implementation.
            }
        }

        // Rebuild slot occupancy using remaining vehicles.
        // This simple approach is suitable only for this demo.
        for (auto& slot : slots) {
            slot = 0;
        }

        parkedVehicles.erase(it);

        // Restore occupied slots for remaining vehicles.
        // This demo uses sequential slot assignment.
        for (size_t i = 0; i < parkedVehicles.size(); ++i) {
            slots[i] = 1;
        }
    }

    // Display parking status
    void displayStatus() const {
        int occupied = 0;

        for (int slot : slots) {
            occupied += slot;
        }

        cout << "\nParking Status\n";
        cout << "--------------\n";
        cout << "Total slots: " << slots.size() << "\n";
        cout << "Occupied slots: " << occupied << "\n";
        cout << "Available slots: "
             << slots.size() - occupied << "\n";
    }

    void processData() override {
        displayStatus();
    }
};

int main() {
    SmartParking parking(3, 50.0);

    parking.parkVehicle({"AP01AB1234", "Car", 9});
    parking.parkVehicle({"AP02CD5678", "SUV", 10});
    parking.parkVehicle({"AP03EF9012", "Car", 11});

    parking.processData();

    cout << "\n--- Vehicle Exit ---\n";
    parking.exitVehicle("AP01AB1234", 12);

    parking.processData();

    return 0;
}