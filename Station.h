#pragma once
#include<string>
using namespace std;
class Station {
private:
    int stationID;
    std::string name;
    std::string location;
    int capacity;

public:
    Station(std::string name, std::string location, int capacity)
        : name(name), location(location), capacity(capacity) {
        static int id = 1;
        stationID = id++;
    }

    int GetStationID() const { return stationID; }
    std::string GetName() const { return name; }
    std::string GetLocation() const { return location; }
    int GetCapacity() const { return capacity; }

    void UpdateCapacity(int newCapacity) { capacity = newCapacity; }

};
