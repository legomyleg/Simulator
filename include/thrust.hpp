#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <types.hpp>

struct ThrustPoint {
    float t;
    float N;
};

struct ThrustCurve {
    std::vector<ThrustPoint> points;

    void load(std::string filename) {
        points.clear();
        std::ifstream file(filename);
        
        std::string line;
        while (std::getline(file, line)) {
            ThrustPoint point;
            std::stringstream ss(line);
            std::string t_str;
            std::string N_str;
            std::getline(ss, t_str, ' ');
            std::getline(ss, N_str, ' ');
            point.t = std::stof(t_str);
            point.N = std::stof(N_str);
            points.push_back(point);
        }
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
