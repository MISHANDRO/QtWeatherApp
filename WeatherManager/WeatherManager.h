#pragma once

#include "Day.h"
#include "WeatherInfo.h"

#include "nlohmann/json.hpp"
#include "cpr/cpr.h"

#include <ctime>
#include <iostream>
#include <list>
#include <cmath>


enum RequestStatus {
    NotExecute, NetworkError, CityError, WeatherError, Success
};

class WeatherManager {
public:
    explicit WeatherManager(std::string city);
    void Request();

    [[nodiscard]] std::string city() const;

    [[nodiscard]] const WeatherInfo& now() const;
    [[nodiscard]] const std::list<Day>& GetDayList() const;

    [[nodiscard]] RequestStatus status() const;
    [[nodiscard]] bool HaveInfo() const;

    static void SetMaxDays(uint16_t val);

protected:
    WeatherInfo now_;
    std::list<Day> days_;

    static inline uint16_t max_days_ = 7;

private:
    static float GetVal(const nlohmann::basic_json<>& inf);
    static void SetConstInfo(WeatherInfo& wi, const nlohmann::basic_json<>& inf, uint16_t num);

    bool have_info_ = false;
    RequestStatus request_status_ = NotExecute;

    std::string city_;
};
