#include <iostream>
#include <map>
#include <list>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

void runTransitSimulation(map<string, array<list<string>, 3>>&, int);
void loadTrafficData(map<string, array<list<string>, 3>>&, const string&);
void displayStationStatus(const map<string, array<list<string>, 3>>&);

const string TRAFFIC_FILE = "traffic.txt";
const int NUM_CYCLES = 25;
const int NUM_LISTS = 3;
const int INCOMING_INDEX = 0, OUTGOING_INDEX = 1, SERVICE_INDEX = 2;
const int INCOMING_PROBABILITY = 70, OUTGOING_PROBABILITY = 60, SERVICE_PROBABILITY = 50;
const int MAX_PROBABILITY = 100;


int main() {
    // CREATE DATA STRUCTURE
    map<string, array<list<string>, 3>> transitMap;

    // LOAD DATA
    loadTrafficData(transitMap, TRAFFIC_FILE);

    // RUN SIMULATION
    runTransitSimulation(transitMap, NUM_CYCLES);

    // FINAL STATE DISPLAY
    cout << "--- Simulation Complete ---" << endl;
    displayStationStatus(transitMap);
    return 0;
}

// @brief simulate the movement of vehicles through the transit system
void runTransitSimulation(map<string, 
    array<list<string>, 
    3>>& transitMap, 
    int cycles) {

    // Set up random number generation
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> moveChance(0, MAX_PROBABILITY);  // 0-100 for probability
    
    for (int cycle = 0; cycle < cycles; cycle++) {
        cout << "\n--- Cycle " << (cycle + 1) << " ---" << endl;
        
        // Keep moving vehicles until no more movements occur in a full pass
        bool movesThisCycle = true;
        while (movesThisCycle) {
            movesThisCycle = false;

            for (auto& [station, lists] : transitMap) {
                auto it = transitMap.find(station);
                if (it == transitMap.end()) {
                    cout << "Warning: station not found while iterating: " << station << endl;
                    continue;
                }

                auto& stationLists = it->second;

                // 70% chance to move a vehicle from Incoming (0) to Outgoing (1)
                if (!stationLists[INCOMING_INDEX].empty() && moveChance(rng) < INCOMING_PROBABILITY) {
                    string vehicle = stationLists[INCOMING_INDEX].front();
                    stationLists[INCOMING_INDEX].pop_front();
                    stationLists[OUTGOING_INDEX].push_back(vehicle);
                    cout << station << ": " << vehicle 
                        << " moved from Incoming to Outgoing" << endl;
                    movesThisCycle = true;
                }
                
                // 60% chance to move a vehicle from Outgoing (1) to Service (2)
                if (!stationLists[OUTGOING_INDEX].empty() && moveChance(rng) < OUTGOING_PROBABILITY) {
                    string vehicle = stationLists[OUTGOING_INDEX].front();
                    stationLists[OUTGOING_INDEX].pop_front();
                    stationLists[SERVICE_INDEX].push_back(vehicle);
                    cout << station << ": " << vehicle 
                        << " moved from Outgoing to Service" << endl;
                    movesThisCycle = true;
                }
                
                // 50% chance to move a vehicle from Service (2) back to Incoming (0)
                if (!stationLists[SERVICE_INDEX].empty() && moveChance(rng) < SERVICE_PROBABILITY) {
                    string vehicle = stationLists[SERVICE_INDEX].front();
                    stationLists[SERVICE_INDEX].pop_front();
                    stationLists[INCOMING_INDEX].push_back(vehicle);
                    cout << station << ": " << vehicle 
                        << " moved from Service back to Incoming" << endl;
                    movesThisCycle = true;
                }
            }
        }
    }
}

// @brief load traffic data from a file into the transit map
void loadTrafficData(
    map<string, array<list<string>, 
    3>>& transitMap, 
    const string& filename) {

    ifstream file(filename);

    // Alpha requirement: Check if file opens correctly
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename 
            << ". Check your file path." << endl;
        return;
    }

    string line;
    int lineCount = 0;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string stationName, vehicleID, statusString;

        // Parse the line using the comma ',' as a delimiter
        if (getline(ss, stationName, ',') &&
            getline(ss, vehicleID, ',') &&
            getline(ss, statusString, ',')) {
        
            // Convert the status string ("0", "1", or "2") into an integer
            try {
                int statusIndex = stoi(statusString);

                // Safety check: ensure the index corresponds to one of our 3 lists
                if (statusIndex >= 0 && statusIndex < NUM_LISTS &&
                    !stationName.empty() && !vehicleID.empty()) {
                    // Push the vehicle into the correct list at the correct station
                    transitMap[stationName][statusIndex].push_back(vehicleID);
                    lineCount++;
                } else {
                    cout << "Warning: invalid traffic record on line "
                        << lineCount + 1 << ": " << line << endl;
                }
            } catch (const invalid_argument&) {
                cout << "Warning: non-numeric status on line "
                    << lineCount + 1 << ": " << line << endl;
            } catch (const out_of_range&) {
                cout << "Warning: status value out of range on line "
                    << lineCount + 1 << ": " << line << endl;
            }
        }
    }

    file.close();
    cout << "Successfully loaded " << lineCount << " vehicles from " 
        << filename << "." << endl;
}

// @brief display the current status of each station in the transit map
void displayStationStatus(const map<string, array<list<string>, 3>>& transitMap) {
    cout << "\nStation Status:" << endl;
    for (auto const& [station, lists] : transitMap) {
        cout << "Hub: " << station << " | Incoming Count: " << lists[INCOMING_INDEX].size() << endl;
        cout << "Hub: " << station << " | Outgoing Count: " << lists[OUTGOING_INDEX].size() << endl;
        cout << "Hub: " << station << " | Service Count: " << lists[SERVICE_INDEX].size() << endl;
    }
}
