//
// Created by Luca-Miguel Christiansen on 18.06.22.
//

#ifndef FLIGHTSEARCHER_FLIGHTS_H
#define FLIGHTSEARCHER_FLIGHTS_H

#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <cpr/cpr.h>
#include "Airlines.h"
#include <QImage>

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
        std::string fd;
    };

    static std::vector<Flight> GetFlights(const std::string&, std::vector<Airlines::Airline>&);
    static tm GetFlightDuration(double lat1, double lon1, double lat2, double lon2);
    static std::map<std::string, std::string, cpr::CaseInsensitiveCompare> GetHeaders();
    static QImage GetPhoto(std::string);
private:
    static double ConvertToRadians(double);
};


#endif //FLIGHTSEARCHER_FLIGHTS_H
