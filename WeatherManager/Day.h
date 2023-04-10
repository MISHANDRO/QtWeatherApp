#pragma once

#include "WeatherInfo.h"

#include <vector>
#include <cstdint>
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <regex>

class Day {
public:
    explicit Day(const std::string& date);
    ~Day();

    void AddPart(WeatherInfo& wi);

    [[nodiscard]] const std::vector<const WeatherInfo*>& GetParts() const;

    [[nodiscard]] std::string GetStrDate() const;

    static void SetMessages(std::vector<std::string>& time_parts_, std::vector<std::string>& weekday_names_,
                            std::vector<std::string>& month_names_);

    static inline std::vector<std::string> time_parts;
    static inline std::vector<std::string> weekday_names;
    static inline std::vector<std::string> month_names;

private:
    static std::tm GetTm(const std::string& date);

    std::vector<const WeatherInfo*> day_parts;
    const std::tm current_day;
};
