//
// Created by Luca-Miguel Christiansen on 19.06.22.
//

#ifndef FLIGHTSEARCHER_AIRPORTS_H
#define FLIGHTSEARCHER_AIRPORTS_H
#include <vector>
#include <iostream>

class Airports {
public:
    struct Airport {
        std::string name;
        std::string iata;
        std::string icao;
        double lat;
        double lon;
        std::string country;
    };
    static std::vector<Airport> GetAirports();
};


#endif //FLIGHTSEARCHER_AIRPORTS_H
