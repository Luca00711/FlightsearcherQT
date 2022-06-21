//
// Created by Luca-Miguel Christiansen on 18.06.22.
//

#ifndef TEST1_FLIGHTS_H
#define TEST1_FLIGHTS_H

#include <iostream>
#include <vector>
#include "Airlines.h"

class Flights {
public:
    struct Flight {
        std::string aircraft;
        std::string registration;
        std::string departure;
        std::string arrival;
        std::string fn;
        std::string callsign;
        std::string airline;
    };

    static std::vector<Flight> GetFlights(const std::string&, std::vector<Airlines::Airline>&);
};


#endif //TEST1_FLIGHTS_H
