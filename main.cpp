#include <iostream>
#include <map>
#include <list>
#include <array>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void runTransitSimulation(map<string, array<list<string>, 3>>&, int);
void loadTrafficData(map<string, array<list<string>, 3>>&, const string&);


int main() {
    // Requirement: std::map with a value of an array of 3 lists
    map<string, array<list<string>, 3>> transitMap;

    // Pseudocode: Open "traffic.txt" using ifstream
    // Pseudocode: Verify file opened correctly; if not, output error and return 1
    // Pseudocode: While reading lines, parse Hub Name and Vehicle ID
    // Pseudocode: Push Vehicle ID into the appropriate list (Incoming/Outgoing/Service)
    loadTrafficData(transitMap, "traffic.txt");

    // INITIAL STATE DISPLAY
    // Requirement: Neatly display the map data

    // RUN SIMULATION
    // Requirement: Show how environment changes after 25 time periods
    runTransitSimulation(transitMap, 25);

    // FINAL STATE DISPLAY
    // Pseudocode: Print the contents of the map again to show changes
    cout << "--- Simulation Complete ---" << endl;

    return 0;
}


// Purpose: Iterate through the map and simulate 25 time periods of transit activity
// Parameters: The transit map (passed by reference) and the number of periods
void runTransitSimulation(map<string, array<list<string>, 3>>& transitMap, int cycles) {
    // Pseudocode: Loop for the specified number of cycles (25)
    // Pseudocode: Inside the loop, iterate through every station in the map
    // Pseudocode: Use logic to move strings between the 3 lists (Arriving, Departing, Service)
}