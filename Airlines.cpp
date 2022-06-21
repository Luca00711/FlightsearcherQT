//
// Created by Luca-Miguel Christiansen on 19.06.22.
//

#include "Airlines.h"
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

std::vector<Airlines::Airline> Airlines::GetAirlines() {
    vector<Airlines::Airline> airlines;
    cpr::Response r = cpr::Get(
            cpr::Url{"https://www.flightradar24.com/_json/airlines.php"});
    json j = json::parse(r.text);
    for (json &i: j["rows"]) {
        Airlines::Airline a;
        i.at("Name").get_to(a.Name);
        i.at("Code").get_to(a.Code);
        i.at("ICAO").get_to(a.ICAO);
        airlines.push_back(a);
    }
    return airlines;
}
