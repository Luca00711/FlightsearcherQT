//
// Created by Luca-Miguel Christiansen on 18.06.22.
//

#include "Flights.h"
#include "Airports.h"
#include "Airlines.h"
#include <fmt/format.h>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

vector<Flights::Flight> Flights::GetFlights(const string &airline, vector<Airlines::Airline> &airlines) {
    vector<Flights::Flight> flights;
    vector<Airports::Airport> airports = Airports::GetAirports();
    cout << fmt::format("https://data-cloud.flightradar24.com/zones/fcgi/feed.js/?airline={}&type=A320", airline) << endl;
    cpr::Response r = cpr::Get(
            cpr::Url{fmt::format("https://data-cloud.flightradar24.com/zones/fcgi/feed.js/?airline={}&type=A320", airline)});
    json j = json::parse(r.text);
    for (json &i: j) {
        if ((string) i.type_name() == "array") {
            Flights::Flight f;
            i.at(8).get_to(f.aircraft);
            i.at(9).get_to(f.registration);
            f.departure = std::find_if(airports.begin(), airports.end(),
                                       [&](const auto &item) { return item.iata == i.at(11); })->icao;
            f.arrival = std::find_if(airports.begin(), airports.end(),
                                     [&](const auto &item) { return item.iata == i.at(12); })->icao;
            i.at(13).get_to(f.fn);
            i.at(16).get_to(f.callsign);
            f.airline = std::find_if(airlines.begin(), airlines.end(),
                                     [&](const auto &item) { return item.ICAO == i.at(18); })->Name;
            flights.push_back(f);
        }
    }
    return flights;
}
