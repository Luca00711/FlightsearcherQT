//
// Created by Luca-Miguel Christiansen on 19.06.22.
//

#ifndef TEST1_AIRLINES_H
#define TEST1_AIRLINES_H

#include <vector>
#include <iostream>


class Airlines {
public:
    struct Airline {
        std::string Name;
        std::string Code;
        std::string ICAO;
    };

    static std::vector<Airline> GetAirlines();

};


#endif //TEST1_AIRLINES_H
