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

void loadTrafficData(map<string, array<list<string>, 3>>& transitMap, const string& filename) {
    ifstream file(filename);

    // Alpha requirement: Check if file opens correctly
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << ". Check your file path." << endl;
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
            int statusIndex = stoi(statusString);


            // Safety check: ensure the index corresponds to one of our 3 lists
            if (statusIndex >= 0 && statusIndex <= 2) {
                // Push the vehicle into the correct list at the correct station
                transitMap[stationName][statusIndex].push_back(vehicleID);
                lineCount++;
            }
        }
    }


    file.close();
    cout << "Successfully loaded " << lineCount << " vehicles from " << filename << "." << endl;
}
