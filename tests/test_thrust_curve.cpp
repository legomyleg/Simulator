#include <thrust.hpp>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_SUITE("Read correctly") {

    std::string simple_curve = std::string(ROOT_DIR) + "/tests/data/thrust_valid.eng";

    TEST_CASE("Simple case") {
        ThrustCurve expected;
        expected.points.emplace_back(0, 0);
        expected.points.emplace_back(1, 10);
        expected.points.emplace_back(3, 0);
        expected.points.emplace_back(4, 10);
        expected.points.emplace_back(5, 10);

        ThrustCurve actual;
        actual.load(simple_curve);

        CHECK(expected == actual);
    }

    TEST_CASE("Reads whitespace and comments correctly") {
        ThrustCurve expected;
        expected.load(simple_curve);

        std::string data = std::string(ROOT_DIR) + "/tests/data/thrust_whitespace.eng";
        ThrustCurve actual;
        actual.load(data);

        CHECK(expected == actual);
    }
}


TEST_SUITE("Interpolation") {
    std::string test_doc_path = std::string(ROOT_DIR) + "/tests/data/thrust_valid.eng";
    ThrustCurve curve(test_doc_path);

    TEST_CASE("Before ignition") {
        float expected = 0;
        float actual = curve.newt_at_t(-1.0f);
        CHECK(expected == actual);
    }

    TEST_CASE("Two points") {
        float expected = 5;
        float actual = curve.newt_at_t(0.5);
        CHECK(expected == actual);
    }

    TEST_CASE("Triangle") {
        float inc_t = 0.5;
        float exp_inc_N = 2.5;
        float t = 1;
        float N = 10;
        for (int i=0; i<4; i++) {
            t += inc_t;
            N -= exp_inc_N;
            float expected = N;
            float actual = curve.newt_at_t(t);

            CHECK(expected == actual);
        }
    }

    TEST_CASE("At zero") {
        float expected = 0;
        float actual = curve.newt_at_t(0);

        CHECK(expected == actual);
    }

    TEST_CASE("Steady thrust") {
        float inc_t = 0.1;
        float t = 4.0;
        float expected = 10.0;
        CHECK(10 == curve.newt_at_t(t));
        for (int i=0; i<10; i++) {
            t += inc_t;
            float actual = curve.newt_at_t(t);

            CHECK(expected == actual);
        }
    }

    TEST_CASE("After burnout") {
        float expected = 0;
        float actual = curve.newt_at_t(5.1);
        CHECK(expected == actual);
    }
}

TEST_SUITE("Load failure") {
    std::string path = std::string(ROOT_DIR) + "/tests/data/thrust_malformed.eng";

    TEST_CASE("Malformed data") {
        ThrustCurve tc;
        auto error = tc.load(path);

        CHECK(LoadError::MalformedData == error);
    }

    TEST_CASE("Can't find file") {
        ThrustCurve tc;
        std::string wrong_path = std::string(ROOT_DIR) + "/tests/thurt_mlfrms.eng";
        auto error = tc.load(wrong_path);

        CHECK(LoadError::FileNotFound == error);
    }

    TEST_CASE("Empty curve") {
        ThrustCurve tc;
        std::string path = std::string(ROOT_DIR) + "/tests/data/thrust_empty.eng";
        auto error = tc.load(path);

        CHECK(LoadError::InvalidFormat == error);
    }
}
