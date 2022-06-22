//
// Created by Luca-Miguel Christiansen on 18.06.22.
//

#include "Flights.h"
#include "Airports.h"
#include "Airlines.h"
#include <fmt/format.h>
#include <vector>
#include <QPixmap>
#include <cpr/cpr.h>
#include <ctime>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

vector<Flights::Flight> Flights::GetFlights(const string &airline, vector<Airlines::Airline> &airlines) {
    vector<Flights::Flight> flights;
    vector<Airports::Airport> airports = Airports::GetAirports();
    cout << fmt::format("https://data-cloud.flightradar24.com/zones/fcgi/feed.js/?airline={}&type=A320", airline)
         << endl;
    cpr::Response r = cpr::Get(
            cpr::Url{fmt::format("https://data-cloud.flightradar24.com/zones/fcgi/feed.js/?airline={}&type=A320",
                                 airline)}, cpr::Header{GetHeaders()});
    json j = json::parse(r.text);
    for (json &i: j) {
        if ((string) i.type_name() == "array") {
            Airports::Airport departure = std::find_if(airports.begin(), airports.end(),
                                                       [&](const auto &item) {
                                                           return item.iata == i.at(11);
                                                       }).operator*();
            Airports::Airport arrival = std::find_if(airports.begin(), airports.end(),
                                                     [&](const auto &item) {
                                                         return item.iata == i.at(12);
                                                     }).operator*();
            Flights::Flight f;
            i.at(8).get_to(f.aircraft);
            i.at(9).get_to(f.registration);
            f.departure = departure.icao;
            f.arrival = arrival.icao;
            i.at(13).get_to(f.fn);
            i.at(16).get_to(f.callsign);
            f.airline = std::find_if(airlines.begin(), airlines.end(),
                                     [&](const auto &item) { return item.ICAO == i.at(18); })->Name;
            tm fltd = GetFlightDuration(departure.lat, departure.lon, arrival.lat, arrival.lon);
            if (fltd.tm_hour == 0) {
                f.fd = fmt::format("0{}:{}", fltd.tm_hour, fltd.tm_min);
                flights.push_back(f);
                continue;
            }
            if (fltd.tm_hour == 1 && fltd.tm_min < 10) {
                f.fd = fmt::format("0{}:0{}", fltd.tm_hour, fltd.tm_min);
                flights.push_back(f);
                continue;
            }
        }
    }
    return flights;
}

tm Flights::GetFlightDuration(double lat1, double lon1, double lat2, double lon2) {
    int R = 6371;
    double f1 = ConvertToRadians(lat1);
    double f2 = ConvertToRadians(lat2);

    double df = ConvertToRadians(lat1 - lat2);
    double dl = ConvertToRadians(lon1 - lon2);

    double a = sin(df / 2) * sin(df / 2) + cos(f1) * cos(f2) * sin(dl / 2) * sin(dl / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double d = R * c;
    d = d / 446.1;
    time_t test = d * 60 * 60;
    tm *ltm = localtime(&test);
    ltm->tm_hour = ltm->tm_hour - 1;
    return *ltm;
}

double Flights::ConvertToRadians(double angle) {
    return (M_PI / 180) * angle;
}

std::map<std::string, std::string, cpr::CaseInsensitiveCompare> Flights::GetHeaders() {
    std::map<std::string, std::string, cpr::CaseInsensitiveCompare> headers{
            {"accept-encoding", "gzip, deflate"},
            {"accept-language", "pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7"},
            {"cache-control",   "max-age=0"},
            {"origin",          "https://www.flightradar24.com"},
            {"referer",         "https://www.flightradar24.com/"},
            {"sec-fetch-dest",  "empty"},
            {"sec-fetch-mode",  "cors"},
            {"sec-fetch-site",  "same-site"},
            {"user-agent",      "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36"},
            {"accept",          "application/json"}
    };
    return headers;
}

QImage Flights::GetPhoto(std::string registration) {
    cpr::Response r = cpr::Get(
            cpr::Url{fmt::format("https://api.planespotters.net/pub/photos/reg/{}",
                                 registration)}, cpr::Header{GetHeaders()});
    json j = json::parse(r.text);
    cpr::Response r1 = cpr::Get(
            cpr::Url{fmt::format("{}",
                                 j["photos"][0]["thumbnail_large"]["src"])}, cpr::Header{GetHeaders()});
    QByteArray bytes = QByteArray::fromStdString(r1.text);
    QImage img;
    img.loadFromData(bytes);
    // QImage to QPixmap conversion
    QPixmap pixmap = QPixmap::fromImage(img);
    return img;
}

