//
// Created by Luca-Miguel Christiansen on 19.06.22.
//

#include "Airports.h"
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

std::vector<Airports::Airport> Airports::GetAirports() {
    vector<Airports::Airport> airports;
    cpr::Response r = cpr::Get(
            cpr::Url{"https://www.flightradar24.com/_json/airports.php"});
    json j = json::parse(r.text);
    for (json &i: j["rows"]) {
        Airports::Airport a;
        i.at("name").get_to(a.name);
        i.at("iata").get_to(a.iata);
        i.at("icao").get_to(a.icao);
        i.at("lat").get_to(a.lat);
        i.at("lon").get_to(a.lon);
        i.at("country").get_to(a.country);
        airports.push_back(a);
    }
    return airports;
}
