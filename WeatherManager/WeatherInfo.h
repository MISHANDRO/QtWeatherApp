#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <cmath>

enum ColorMode {
    None, Prefix, HTML
};

class WeatherInfo {
public:

    void SetWeather(float val);
    void SetTemperature(float val);
    
    void SetWindSpeed(float val);
    void SetWindDirection(float val);
    
    void SetPressure(float val);
    
    void SetPrecipitation(float val);
    void SetPrecipitationProbability(float val);

    [[nodiscard]] uint16_t GetWeatherCode() const;

    [[nodiscard]] std::vector<std::string> GetString(const ColorMode& mode) const;

    static void SetWeatherNames(const std::vector<std::string>& names_) {
        uint16_t iterator = 0;
        for (auto& [_, name] : weather_names) {
            if (iterator >= names_.size()) {
                break;
            }

            name = names_[iterator];
            ++iterator;
        }
    }

    static void SetDesignations(const std::string& wind_speed_, const std::string& mmHg_, const std::string& mm_);

private:
    static const inline std::vector<std::string> arrows = {
            "\u2191",
            "\u2197",
            "\u2192",
            "\u2198",
            "\u2193",
            "\u2199",
            "\u2190",
            "\u2196"
    };

    [[nodiscard]] std::string GetTemperature(const ColorMode& mode) const;
    [[nodiscard]] std::string GetWind(const ColorMode& mode) const;

    static std::string GetColorTemperature(short val, const ColorMode& mode);
    static std::string GetColorWindSpeed(short val, const ColorMode& mode);
    [[nodiscard]] std::string GetColorPressure(const ColorMode& mode) const;

    uint16_t weather;
    short min_temperature = INT16_MAX;
    short max_temperature = INT16_MIN;
    short min_wind_speed = INT16_MAX;
    short max_wind_speed = INT16_MIN;
    short wind_direction;
    short pressure;
    std::string precipitation;
    short precipitation_probability;

    static inline std::string wind_speed = "m/s";
    static inline std::string mmHg = "mm Hg";
    static inline std::string mm = "mm";

private:
    static inline std::map<uint16_t, std::string> weather_names = {
            {0,  "Clear Sky"},
            {1,  "Mainly clear"},
            {2,  "Partly cloudy"},
            {3,  "Overcast"},
            {45,  "Fog"},
            {48,  "Fog"},

            {51,  "Drizzle"},
            {53,  "Drizzle"},
            {55,  "Drizzle"},
            {56,  "Freezing"},
            {57,  "Freezing"},

            {61,  "Rain"},
            {63,  "Rain"},
            {65,  "Rain"},

            {66,  "Freezing rain"},
            {67,  "Freezing rain"},
            {71,  "Snow"},
            {73,  "Snow"},
            {75,  "Snow"},
            {77,  "Snow"},

            {80,  "Rain"},
            {81,  "Rain"},
            {82,  "Rain"},

            {85,  "Snow"},
            {86,  "Snow"},

            {95,  "Thunderstorm"},
            {96,  "Thunderstorm"},
            {99,  "Thunderstorm"},
    };
};
