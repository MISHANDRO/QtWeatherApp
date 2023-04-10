#include "Day.h"

#include "WeatherInfo.h"

#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

Day::Day(const std::string& date)
        : current_day(GetTm(date))
{
    day_parts.reserve(4);
}

Day::~Day() {
    for (const WeatherInfo* wi : day_parts) {
        delete wi;
    }
}

void Day::AddPart(WeatherInfo& wi) {
    if (day_parts.size() == day_parts.capacity()) {
        return;
    }

    day_parts.push_back(new WeatherInfo(std::move(wi)));
}

std::tm Day::GetTm(const std::string& date) {
    std::tm tm{};

    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M");
    std::time_t time = mktime(&tm);

    std::tm* res = std::localtime(&time);
    tm.tm_year += 1900;
    tm.tm_wday = res->tm_wday;

    return tm;
}

[[nodiscard]] const std::vector<const WeatherInfo*>& Day::GetParts() const {
    return day_parts;
};

std::string Day::GetStrDate() const {
    return weekday_names[current_day.tm_wday] + ". " + std::to_string(current_day.tm_mday) + " "
           + month_names[current_day.tm_mon];
}

void Day::SetMessages(std::vector<std::string>& time_parts_, std::vector<std::string>& weekday_names_,
                        std::vector<std::string>& month_names_) {
    time_parts = std::move(time_parts_);
    weekday_names = std::move(weekday_names_);
    month_names = std::move(month_names_);
}
