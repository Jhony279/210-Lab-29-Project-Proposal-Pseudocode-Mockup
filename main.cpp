#include <iostream>
#include <map>
#include <list>
#include <array>
#include <string>
#include <fstream>

using namespace std;

// 1. FUNCTION DEFINITION
// Purpose: Iterate through the map and simulate 25 time periods of transit activity
// Parameters: The transit map (passed by reference) and the number of periods
void runTransitSimulation(map<string, array<list<string>, 3>>& transitMap, int cycles) {
    // Pseudocode: Loop for the specified number of cycles (25)
    // Pseudocode: Inside the loop, iterate through every station in the map
    // Pseudocode: Use logic to move strings between the 3 lists (Arriving, Departing, Service)
    
    // Wireframe check:
    cout << "Simulation successfully called for " << cycles << " cycles." << endl;
}

int main() {
    // 2. DATA STRUCTURE INITIALIZATION
    // Requirement: std::map with a value of an array of 3 lists
    map<string, array<list<string>, 3>> transitMap;

    // 3. FILE HANDLING PSEUDOCODE
    // Pseudocode: Open "traffic_data.txt" using ifstream
    // Pseudocode: Verify file opened correctly; if not, output error and return 1
    // Pseudocode: While reading lines, parse Hub Name and Vehicle ID
    // Pseudocode: Push Vehicle ID into the appropriate list (Incoming/Outgoing/Service)
    
    // 4. WIREFRAME DATA (MOCKUP)
    // Adding one element manually to prove the nested structure is coded correctly
    string hub = "Grand Central";
    transitMap[hub][0].push_back("Train-101"); // Index 0: Incoming
    transitMap[hub][1].push_back("Train-202"); // Index 1: Outgoing
    transitMap[hub][2].push_back("Cutter-Unit"); // Index 2: Service

    // 5. INITIAL STATE DISPLAY
    // Requirement: Neatly display the map data
    cout << "--- Initial State ---" << endl;
    for (auto const& [name, status] : transitMap) {
        cout << "Hub: " << name << " | Incoming Count: " << status[0].size() << endl;
    }

    // 6. RUN SIMULATION
    // Requirement: Show how environment changes after 25 time periods
    runTransitSimulation(transitMap, 25);

    // 7. FINAL STATE DISPLAY
    // Pseudocode: Print the contents of the map again to show changes
    cout << "--- Simulation Complete ---" << endl;

    return 0;
}