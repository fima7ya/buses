#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    // Реализуйте эту функцию

    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS"s) {
        q.type = QueryType::NewBus;    
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    } else if (operation_code == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;    
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;    
        is >> q.bus;

    } else if (operation_code == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    bool no_stop;
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.no_stop) {
        os << "No stop"s;
        return os;
    } 
    
    for (const auto& bus: r.buses) {
        os << bus << " "; // space at the end of line
    }

    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    bool no_bus;
    bool no_interchange;
    vector<pair<string, vector<string>>> stops;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.no_bus) {
        os << "No bus"s;
        return os;
    }

    if (r.no_interchange) {
        os << "No interchange"s;
        return os;
    }

    for (const auto& [stop, buses]: r.stops) {
        os << "Stop " << stop << ": ";
        for (const auto& bus: buses) {
            os << bus << " ";
        }
    }

    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    bool no_buses;
    vector<pair<string, vector<string>>> buses;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.no_buses) {
        os << "No buses";
        return os;
    }

    for (const auto& [bus, stops]: r.buses) {
        os << "Bus " << bus << ": ";
        for (const auto& stop: stops) {
            os << stop << " ";
        }
    }

    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        _buses_to_stops[bus] = stops;

        for (const auto& stop : stops) {
            _stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
    }
private:
    map<string, vector<string>> _buses_to_stops;
    map<string, vector<string>> _stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}



/*

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS"s) {
            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP"s) {
            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop"s << endl;
            } else {
                for (const string& bus : stops_to_buses[stop]) {
                    cout << bus << " "s;
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS"s) {
            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus"s << endl;
            } else {
                for (const string& stop : buses_to_stops[bus]) {
                    cout << "Stop "s << stop << ": "s;
                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange"s;
                    } else {
                        for (const string& other_bus : stops_to_buses[stop]) {
                            if (bus != other_bus) {
                                cout << other_bus << " "s;
                            }
                        }
                    }
                    cout << endl;
                }
            }

        } else if (operation_code == "ALL_BUSES"s) {
            if (buses_to_stops.empty()) {
                cout << "No buses"s << endl;
            } else {
                for (const auto& bus_item : buses_to_stops) {
                    cout << "Bus "s << bus_item.first << ": "s;
                    for (const string& stop : bus_item.second) {
                        cout << stop << " "s;
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
} 
*/