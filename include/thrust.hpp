#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "types.hpp"

struct ThrustPoint {
    float t;
    float N;
};

enum class LoadError {
    None,
    FileNotFound,
    InvalidFormat,
    MalformedData,
    ReadError
};

struct ThrustCurve {
    std::vector<ThrustPoint> points;

    LoadError load(std::string filename) {
        points.clear();

        std::ifstream file(filename);
        if (!file) return LoadError::FileNotFound;

        std::string line;
        const std::string whitespace = " \t\r\n\f\v";
        while (std::getline(file, line)) {
            const auto start = line.find_first_not_of(whitespace);
            if (start == std::string::npos) continue;
            std::string trm_line = line.substr(start);

            if (trm_line.at(0) == ';') continue;

            std::vector<std::string> tokens;
            std::stringstream ss(line);
            std::string token;
            while (ss >> token) {
                tokens.push_back(token);
            }

            if (tokens.size() != 2) { 
                points.clear();
                return LoadError::InvalidFormat;
            }

            ThrustPoint point;
            const auto val1 = tokens[0];
            const auto val2 = tokens[1];
            size_t pos;
            try {
                point.t = std::stof(val1, &pos);
                if (pos != val1.size() || !std::isfinite(point.t)) {
                    points.clear();
                    return LoadError::InvalidFormat;
                }
                point.N = std::stof(val2, &pos);
                if (pos != val2.size() || !std::isfinite(point.N)) {
                    points.clear();
                    return LoadError::InvalidFormat;
                }
            } catch (...) {
                points.clear();
                return LoadError::InvalidFormat;
            }

            if (!points.empty() && point.t <= points[points.size() - 1].t) {
                points.clear();
                return LoadError::MalformedData;
            }

            points.push_back(point);
        }

        if (file.bad()) {
            points.clear();
            return LoadError::ReadError;
        }

        if (points.empty()) return LoadError::InvalidFormat;

        return LoadError::None;
    }

    float newt_at_t(float t) {

        size_t low = 0;
        size_t high = points.size() - 1;

        if (t > points[high].t) return 0.0f;
        if (t < points[low].t) return (t/points[0].t) * points[0].N;

        size_t f0;
        size_t f1;
        
        bool found = false;
        while (!found) {

            if ((high - low) == 1) {
                f0 = low;
                f1 = high;
                found = true;
                break;
            }

            size_t mid = low + ((high - low) / 2);
            if (t < points[mid].t) high = mid;
            if (t > points[mid].t) low = mid;
            if (t == points[mid].t) return points[mid].N;
            
        }

        float t1 = points[f1].t;
        float t0 = points[f0].t;
        float F1 = points[f1].N;
        float F0 = points[f0].N;
        return F0 + (((t - t0)/(t1 - t0)) * (F1 - F0));

    }
};
