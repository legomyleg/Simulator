#include <thrust.hpp>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


TEST_CASE("Testing simple case") {
    std::string test_doc_path = std::string(ROOT_DIR) + "/tests/test_thrust_doc.txt";

    ThrustPoint point1{1.0f, 2.0f};
    ThrustPoint point2{3.0f, 5.0f};

    ThrustCurve curve{};
    curve.load(test_doc_path);

    CHECK(curve.points.at(0).N == point1.N);
    CHECK(curve.points.at(0).t == point1.t);
    CHECK(curve.points.at(1).N == point2.N);
    CHECK(curve.points.at(1).t == point2.t);
}
