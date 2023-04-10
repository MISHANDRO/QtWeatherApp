#include "WeatherManager.h"

#include "Day.h"
#include "WeatherInfo.h"

#include "nlohmann/json.hpp"
#include "cpr/cpr.h"

#include <iostream>
#include <list>

WeatherManager::WeatherManager(std::string city)
        : city_(std::move(city))
{}

void WeatherManager::Request() {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                               cpr::Parameters{{"name", city_}},
                               cpr::Header{{"X-Api-Key", "nDiNfJvc76/eQPfcOD0FIw==wJV04TtRzRKbjUvM"}});

    if (r.text.empty()) {
        request_status_ = RequestStatus::NetworkError;
        return;
    }

    nlohmann::json responseJson = nlohmann::json::parse(r.text);

    if (responseJson[0]["latitude"].is_null()) {
        request_status_ = RequestStatus::CityError;
        return;
    }

//        city_ += ", " + responseJson[0]["country"].get<std::string>();

    r = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                 cpr::Parameters{
                         {"latitude", std::to_string(responseJson[0]["latitude"].get<double>())},
                         {"longitude", std::to_string(responseJson[0]["longitude"].get<double>())},
                         {"hourly", "temperature_2m,relativehumidity_2m,"
                                    "precipitation_probability,precipitation,"
                                    "weathercode,surface_pressure,"
                                    "windspeed_10m,winddirection_10m"},
                         {"current_weather", "true"},
                         {"forecast_days", "16"},
                         {"windspeed_unit", "ms"},
                         {"timezone", "auto"}
                 });

    try {
        responseJson = nlohmann::json::parse(r.text);

        WeatherInfo wi;
        std::string cur_time = responseJson["current_weather"]["time"];

        std::list<Day> tmp_list;

        for (int i = 0; i < responseJson["hourly"]["time"].size() - 24 + 6; i++) {

            if (std::strcmp(responseJson["hourly"]["time"][i].get<std::string>().c_str(), cur_time.c_str()) == 0) {
                now_ = WeatherInfo();
                SetConstInfo(now_, responseJson, i);
                now_.SetTemperature(GetVal(responseJson["hourly"]["temperature_2m"][i]));
                now_.SetWindSpeed(GetVal(responseJson["hourly"]["windspeed_10m"][i]));
            }

            if (responseJson["hourly"]["weathercode"][i].is_null()) {
                tmp_list.pop_back();
                max_days_ = tmp_list.size();
                break;
            }

            wi.SetTemperature(GetVal(responseJson["hourly"]["temperature_2m"][i]));
            wi.SetWindSpeed(GetVal(responseJson["hourly"]["windspeed_10m"][i]));

            // add night info (to 6:00 of next day)
            if (i != 5 && (i % 24 == 11 || i % 24 == 17 || i % 24 == 22 || i % 24 == 5)) {
                tmp_list.back().AddPart(wi);
            }

            if (i % 24 % 6 == 2 && i != 2) {
                SetConstInfo(wi, responseJson, i);
            }

            if (i % 24 == 6) {
                if (tmp_list.size() == max_days_) {
                    break;
                }
                tmp_list.emplace_back(responseJson["hourly"]["time"][i]);
            }
        }

        have_info_ = true;
        days_ = std::move(tmp_list);
        request_status_ = RequestStatus::Success;
    } catch (...) {
        request_status_ = RequestStatus::WeatherError;
    }
}

[[nodiscard]] std::string WeatherManager::city() const {
    return city_;
}

[[nodiscard]] const WeatherInfo& WeatherManager::now() const {
    return now_;
}

[[nodiscard]] const std::list<Day>& WeatherManager::GetDayList() const {
    return days_;
}

[[nodiscard]] RequestStatus WeatherManager::status() const {
    return request_status_;
}

[[nodiscard]] bool WeatherManager::HaveInfo() const {
    return have_info_;
}

void WeatherManager::SetMaxDays(uint16_t val) {
    max_days_ = std::min<uint16_t>(val, 14);
}

float WeatherManager::GetVal(const nlohmann::basic_json<>& inf) {
    if (inf.is_null()) {
        return 0.0f;
    }

    float res;
    inf.get_to(res);

    return res;
}

void WeatherManager::SetConstInfo(WeatherInfo& wi, const nlohmann::basic_json<>& inf, uint16_t num) {
    wi.SetWeather(GetVal(inf["hourly"]["weathercode"][num]));
    wi.SetWindDirection(GetVal(inf["hourly"]["winddirection_10m"][num]));
    wi.SetPressure(GetVal(inf["hourly"]["surface_pressure"][num]));
    wi.SetPrecipitation(GetVal(inf["hourly"]["precipitation"][num]));
    wi.SetPrecipitationProbability(GetVal(inf["hourly"]["precipitation_probability"][num]));
}
