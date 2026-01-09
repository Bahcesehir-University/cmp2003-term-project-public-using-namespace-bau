#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct ZoneCount {
    string zone;
    long long count;
};

struct SlotCount {
    string zone;
    int hour;
    long long count;
};

struct SlotKey {
    string zone;
    int hour;
    bool operator==(const SlotKey& o) const {
        return hour == o.hour && zone == o.zone;
    }
};

struct SlotHash {
    size_t operator()(const SlotKey& k) const {
        return hash<string>()(k.zone) ^ (hash<int>()(k.hour) << 1);
    }
};

class TripAnalyzer {
private:
    unordered_map<string, long long> zoneCounts;
    unordered_map<SlotKey, long long, SlotHash> slotCounts;

public:
    void ingestStdin();
    vector<ZoneCount> topZones(int k = 10) const;
    vector<SlotCount> topBusySlots(int k = 10) const;
};

#endif
