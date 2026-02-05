#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip> // FIX: Added for setprecision

using namespace std;

class Vehicle {
private:
    string licensePlate;
    string type;
    long long entryTime; // FIX: Renamed for consistency
public:
    Vehicle(string plate, string vehicleType) {
        licensePlate = plate;
        type = vehicleType;
        entryTime = time(0);
    }

    string getPlate() const { return licensePlate; }

    // FIX: Renamed to match the logic call in exitVehicle
    long long getEntryTime() const { return entryTime; }
};

class ParkingGarage {
private:
    vector<Vehicle> vehicles; // FIX: Using plural 'vehicles'
    int totalSpots;
    double hourlyRate;
    double totalRevenue;

public: // FIX: EVERYTHING BELOW MUST BE PUBLIC
    ParkingGarage(int spots, double rate)
        : totalSpots(spots), hourlyRate(rate), totalRevenue(0.0) {}

    void setParkVehicle(string plate, string type) {
        if (vehicles.size() >= (size_t)totalSpots) {
            cout << "DENIED: Garage is full. " << plate << " cannot enter." << endl;
            return;
        }

        Vehicle newVehicle(plate, type);
        vehicles.push_back(newVehicle);
        cout << "[ENTRY] " << type << " (" << plate << ") has parked." << endl;
    }

    void exitVehicle(string plate) {
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if (it->getPlate() == plate) {
                long long exitTime = time(0);
                long long durationSeconds = exitTime - it->getEntryTime();

                // 1 second = 1 hour for testing
                double hours = (durationSeconds == 0) ? 1 : (double)durationSeconds;
                double fee = hours * hourlyRate;

                totalRevenue += fee;

                cout << fixed << setprecision(2);
                cout << "\n--- PARKING RECEIPT ---" << endl;
                cout << "License: " << it->getPlate() << endl;
                cout << "Duration: " << hours << " hour(s)" << endl;
                cout << "Total Fee: $" << fee << endl;
                cout << "-----------------------" << endl;

                vehicles.erase(it);
                return;
            }
        }
        cout << "ERROR: Vehicle with plate " << plate << " not found." << endl;
    }

    void showStatus() {
        cout << "\n--- GARAGE STATUS ---" << endl;
        cout << "Occupancy: " << vehicles.size() << "/" << totalSpots << endl;
        cout << "Available Spots: " << totalSpots - vehicles.size() << endl;
        cout << "Total Revenue: $" << totalRevenue << endl;
        cout << "---------------------" << endl;
    }
};

int main() {
    ParkingGarage myGarage(10, 5.00);

    myGarage.setParkVehicle("ABC-123", "Car");
    myGarage.setParkVehicle("XYZ-999", "Truck");

    myGarage.showStatus();

    cout << "\nProcessing exit for ABC-123..." << endl;
    myGarage.exitVehicle("ABC-123");

    myGarage.showStatus();

    return 0;
}