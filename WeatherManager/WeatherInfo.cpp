#include "WeatherInfo.h"

#include <string>
#include <vector>
#include <cmath>

short to_short(float val) {
    return static_cast<short>(std::round(val));
}

void WeatherInfo::SetWeather(float val) {
    weather = to_short(val);
}

void WeatherInfo::SetTemperature(float val) {
    min_temperature = std::min(min_temperature, to_short(val));
    max_temperature = std::max(max_temperature, to_short(val));
}

void WeatherInfo::SetWindSpeed(float val) {
    min_wind_speed = std::min(min_wind_speed, to_short(val));
    max_wind_speed = std::max(max_wind_speed, to_short(val));
}

void WeatherInfo::SetWindDirection(float val) {
    wind_direction = to_short(val);
}

void WeatherInfo::SetPressure(float val) {
    if (val == 0.0f) {
        pressure = 760; // normal pressure
        return;
    }

    pressure = to_short(val * 0.75f); // to mmHg
}

void WeatherInfo::SetPrecipitation(float val) {
    std::string str_val = std::to_string(val);
    str_val.erase(std::find(str_val.begin(), str_val.end(), '.') + 2, str_val.end());

    precipitation = std::move(str_val);
}

void WeatherInfo::SetPrecipitationProbability(float val) {
    precipitation_probability = to_short(val);
}

[[nodiscard]] uint16_t WeatherInfo::GetWeatherCode() const {
    return weather;
}

[[nodiscard]] std::vector<std::string> WeatherInfo::GetString(const ColorMode& mode) const {
    std::vector<std::string> res;
    res.reserve(5);

    res.push_back(weather_names.at(weather));
    res.push_back(GetTemperature(mode) + " °C");
    res.push_back(GetWind(mode) + ' ' + wind_speed);
    res.push_back(GetColorPressure(mode) + ' ' + mmHg);
    res.push_back(precipitation + ' ' + mm + " | " + std::to_string(precipitation_probability) + "%");

    return res;
}

[[nodiscard]] std::string WeatherInfo::GetTemperature(const ColorMode& mode) const {
    std::string res = GetColorTemperature(max_temperature, mode);
    if (min_temperature != max_temperature) {
        res += '(' + GetColorTemperature(min_temperature, mode) + ')';
    }

    return res;
}

[[nodiscard]] std::string WeatherInfo::GetWind(const ColorMode& mode) const {

    int arrow_wind = (wind_direction + 45 / 2) / 45;
    if (arrow_wind >= arrows.size()) {
        arrow_wind = 0;
    }

    std::string res = arrows[arrow_wind] + ' ' + GetColorWindSpeed(min_wind_speed, mode);
    if (min_wind_speed != max_wind_speed) {
        res += '-' + GetColorWindSpeed(max_wind_speed, mode);
    }

    return res;
}

std::string WeatherInfo::GetColorTemperature(short val, const ColorMode& mode) {
    std::string res;

    if (mode == None) {
        if (val > 0) {
            res += '+';
        }

        return res + std::to_string(val);
    }

    if (mode == HTML) {
        res += "<span style=\"color: ";
    }

    if (val <= -15) {
        res += (mode == Prefix) ? "&1" : "darkblue";
    } else if (val <= 0) {
        res += (mode == Prefix) ? "&1" : "blue";
    } else if (val <= 15) {
        res += (mode == Prefix) ? "&2" : "darkgreen";
    } else if (val <= 25) {
        res += (mode == Prefix) ? "&:" : "green";
    } else if (val <= 30) {
        res += (mode == Prefix) ? "&>" : "yellow";
    } else {
        res += (mode == Prefix) ? "&<" : "red";
    }

    if (mode == HTML) {
        return res + "\">" + ((val > 0) ? "+" : "") + std::to_string(val) + "</span>";
    }

    return res + ((val > 0) ? "+" : "") + std::to_string(val) + "&7";
}

std::string WeatherInfo::GetColorWindSpeed(short val, const ColorMode& mode) {
    std::string res;

    if (mode == None) {
        return std::to_string(val);
    }

    if (mode == HTML) {
        res += "<span style=\"color: ";
    }

    if (val <= 5) {
        res += (mode == Prefix) ? "&:" : "green";
    } else if (val <= 10) {
        res += (mode == Prefix) ? "&2" : "darkgreen";
    }  else if (val <= 15) {
        res += (mode == Prefix) ? "&6" : "yellow";
    } else if (val <= 20) {
        res += (mode == Prefix) ? "&>" : "yellow";
    } else if (val <= 30) {
        res += (mode == Prefix) ? "&<" : "red";
    } else {
        res += (mode == Prefix) ? "&5" : "violet";
    }

    if (mode == HTML) {
        return res + "\">" + std::to_string(val) + "</span>";
    }

    return res + std::to_string(val) + "&7";
}

[[nodiscard]] std::string WeatherInfo::GetColorPressure(const ColorMode& mode) const {
    std::string res;

    if (mode == None) {
        return std::to_string(pressure);
    }

    if (mode == HTML) {
        res += "<span style=\"color: ";
    }

    if (pressure <= 735) {
        res += (mode == Prefix) ? "&5" : "violet";
    } else if (pressure < 755) {
        res += (mode == Prefix) ? "&6" : "yellow";
    } else if (pressure <= 765) {
        res += (mode == Prefix) ? "&:" : "green";
    } else if (pressure <= 780) {
        res += (mode == Prefix) ? "&>" : "yellow";
    } else {
        res += (mode == Prefix) ? "&<" : "red";
    }

    if (mode == HTML) {
        return res + "\">" + std::to_string(pressure) + "</span>";
    }

    return res + std::to_string(pressure) + "&7";
}

void WeatherInfo::SetDesignations(const std::string& wind_speed_, const std::string& mmHg_, const std::string& mm_) {
    wind_speed = wind_speed_;
    mmHg = mmHg_;
    mm = mm_;
}
