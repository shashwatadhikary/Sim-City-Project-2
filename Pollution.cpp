#include <iostream>
#include <vector>
#include "City.h"    // Include the City header
#include "Citizen.h" // Include the Citizen header
#include "HealthStatus.h" // Include the HealthStatus enum

using namespace std;

class Pollution {
private:
    City& city;
    double pollutionLevel;

public:
    Pollution(City& cityRef) : city(cityRef), pollutionLevel(0.0) {}

    void updatePollution() {
        pollutionLevel = calculatePollutionLevel();
        applyPollutionEffects();
    }

    double calculatePollutionLevel() {
        double level = 0.0;
        int** populations = city.getPopulations();
        int citySize = city.getCitySize();
        char** zones = city.getZones();

        // Calculate pollution based on industrial zones and vehicle emissions
        for (int y = 0; y < citySize; y++) {
            for (int x = 0; x < citySize; x++) {
                if (zones[y][x] == IndustrialZone) {
                    level += 0.1 * populations[y][x];  // Higher pollution from industrial zones
                }
                if (zones[y][x] == CommercialZone || zones[y][x] == ResidentialZone) {
                    level += 0.02 * populations[y][x];  // Lesser pollution from commercial and residential areas
                }
            }
        }

        return level;
    }

    void applyPollutionEffects() {
        vector<Citizen>& citizens = city.getCitizens();

        // Apply health effects based on pollution levels
        for (auto& citizen : citizens) {
            if (pollutionLevel > 20 && citizen.healthStatus == HEALTHY) {
                citizen.healthStatus = SICK;  // High pollution levels make healthy citizens sick
            }
            else if (pollutionLevel <= 20 && citizen.healthStatus == SICK) {
                citizen.healthStatus = RECOVERING;  // Reduced pollution helps sick citizens to start recovering
            }
        }
    }

    void displayPollutionStats() const {
        cout << "Current pollution level: " << pollutionLevel << endl;
    }
};
