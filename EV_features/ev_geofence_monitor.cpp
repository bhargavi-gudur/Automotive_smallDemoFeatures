/**
 * @file ev_geofence_monitor.cpp
 * @author Gandla Bhargavi
 * @brief EV Geofencing and Vehicle Location Alert using OOP and STL
 * @date 03-09-2026
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Represents a GPS coordinate.
 */
struct GPSCoordinate
{
    double latitude;
    double longitude;
};

/**
 * @brief Represents an EV geofence.
 */
struct Geofence
{
    string name;
    GPSCoordinate center;
    double radiusKm;
};

/**
 * @brief Abstract base class for a telematics system.
 */
class TelematicsSystem
{
public:
    virtual void processData() = 0;

    virtual ~TelematicsSystem() = default;
};

/**
 * @brief Monitors EV location against predefined geofences.
 */
class EVGeofenceMonitor : public TelematicsSystem
{
private:
    GPSCoordinate vehicleLocation;

    vector<Geofence> geofences;
    vector<GPSCoordinate> routeHistory;

    map<string, bool> zoneState;
    set<string> visitedZones;

    /**
     * @brief Converts degrees to radians.
     */
    double toRadians(double degrees) const
    {
        constexpr double PI = 3.14159265358979323846;
        return degrees * PI / 180.0;
    }

    /**
     * @brief Calculates distance between two GPS coordinates.
     *
     * Uses the Haversine formula.
     */
    double calculateDistanceKm(const GPSCoordinate& first,
                               const GPSCoordinate& second) const
    {
        constexpr double EARTH_RADIUS_KM = 6371.0;

        const double latitudeDifference =
            toRadians(second.latitude - first.latitude);

        const double longitudeDifference =
            toRadians(second.longitude - first.longitude);

        const double firstLatitude = toRadians(first.latitude);
        const double secondLatitude = toRadians(second.latitude);

        const double haversine =
            sin(latitudeDifference / 2.0) *
            sin(latitudeDifference / 2.0) +
            cos(firstLatitude) *
            cos(secondLatitude) *
            sin(longitudeDifference / 2.0) *
            sin(longitudeDifference / 2.0);

        const double angularDistance =
            2.0 * atan2(sqrt(haversine), sqrt(1.0 - haversine));

        return EARTH_RADIUS_KM * angularDistance;
    }

    /**
     * @brief Checks vehicle position against all geofences.
     */
    void checkGeofences()
    {
        for (const auto& zone : geofences)
        {
            const double distance =
                calculateDistanceKm(vehicleLocation, zone.center);

            const bool isInside = distance <= zone.radiusKm;
            const bool wasInside = zoneState[zone.name];

            cout << "\nZone: " << zone.name
                 << "\nDistance: " << fixed << setprecision(3)
                 << distance << " km"
                 << "\nRadius: " << zone.radiusKm << " km";

            if (isInside && !wasInside)
            {
                cout << "\nALERT: Vehicle ENTERED " << zone.name;

                visitedZones.insert(zone.name);
                zoneState[zone.name] = true;
            }
            else if (!isInside && wasInside)
            {
                cout << "\nALERT: Vehicle EXITED " << zone.name;

                zoneState[zone.name] = false;
            }
            else if (isInside)
            {
                cout << "\nStatus: Vehicle is INSIDE " << zone.name;
            }
            else
            {
                cout << "\nStatus: Vehicle is OUTSIDE " << zone.name;
            }
        }
    }

public:
    /**
     * @brief Adds a geofence to the EV telematics system.
     */
    void addGeofence(const Geofence& zone)
    {
        geofences.push_back(zone);
        zoneState[zone.name] = false;
    }

    /**
     * @brief Updates the vehicle GPS position.
     */
    void updateLocation(const GPSCoordinate& location)
    {
        vehicleLocation = location;
        routeHistory.push_back(location);
    }

    /**
     * @brief Displays current vehicle location.
     */
    void displayLocation() const
    {
        cout << "\nVehicle GPS Location"
             << "\nLatitude : " << fixed << setprecision(6)
             << vehicleLocation.latitude
             << "\nLongitude: " << vehicleLocation.longitude
             << '\n';
    }

    /**
     * @brief Processes the latest GPS data.
     */
    void processData() override
    {
        displayLocation();
        checkGeofences();
    }

    /**
     * @brief Displays geofences visited by the EV.
     */
    void displayVisitedZones() const
    {
        cout << "\nVisited Geofences:\n";

        if (visitedZones.empty())
        {
            cout << "No geofences visited.\n";
            return;
        }

        for (const auto& zone : visitedZones)
        {
            cout << "- " << zone << '\n';
        }
    }

    /**
     * @brief Displays number of GPS points stored.
     */
    void displayRouteStatistics() const
    {
        cout << "\nRoute Statistics"
             << "\nGPS points recorded: "
             << routeHistory.size() << '\n';
    }
};

int main()
{
    EVGeofenceMonitor monitor;

    // Home geofence
    monitor.addGeofence({
        "HOME",
        {17.385044, 78.486671},
        1.0
    });

    // Workplace geofence
    monitor.addGeofence({
        "WORKPLACE",
        {17.448294, 78.391487},
        0.8
    });

    // Service center geofence
    monitor.addGeofence({
        "SERVICE_CENTER",
        {17.440081, 78.348916},
        0.5
    });

    vector<GPSCoordinate> gpsPoints =
    {
        {17.385500, 78.487000},   // Home
        {17.448700, 78.392000},   // Workplace
        {17.450000, 78.400000},   // Outside workplace
        {17.440300, 78.349100}    // Service center
    };

    for (const auto& location : gpsPoints)
    {
        monitor.updateLocation(location);
        monitor.processData();
    }

    monitor.displayVisitedZones();
    monitor.displayRouteStatistics();

    return 0;
}