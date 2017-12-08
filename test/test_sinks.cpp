#include "gtest/gtest.h"
#include "xtensor/xtensor.hpp"

#include "fastscape/sinks.hpp"


TEST(sinks, fill_sinks_flat) {
    xt::xtensor<double, 2> arr
       {{1.0, 2.0, 3.0},
        {2.0, 0.1, 7.0},
        {2.0, 5.0, 7.0}};

    fs::fill_sinks_flat(arr);

    ASSERT_EQ(arr(1, 1), arr(0, 0));
}


TEST(sinks, fill_sinks_sloped) {
    xt::xtensor<double, 2> arr
       {{1.0, 2.0, 3.0},
        {2.0, 0.1, 7.0},
        {2.0, 5.0, 7.0}};

    fs::fill_sinks_sloped(arr);

    ASSERT_GT(arr(1, 1), arr(0, 0));
}