//
// Created by will on 10/9/25.
//

#include <cmath>
#include <gtest/gtest.h>
#include "MixedForm/MixedForm.hpp"

auto form = MixedForm(Winterval(2, 2));

TEST(mixed_scalar, addition) {
    auto result = form + 2.0;
    EXPECT_EQ(result.intersected_bounds(), Winterval(4, 4));
}
TEST(mixed_scalar, subtraction) {
    auto result = form - 2.0;
    EXPECT_EQ(result.intersected_bounds(), Winterval(0, 0));
}
TEST(mixed_scalar, multiplication) {
    auto form = MixedForm(Winterval(0, 2));
    auto result = form * 2.0;
    EXPECT_EQ(result.intersected_bounds(), Winterval(0, 4));
}
TEST(mixed_scalar, division) {
    auto form = MixedForm(Winterval(1, 2));
    auto result = form / 2.0;
    EXPECT_EQ(result.intersected_bounds(), Winterval(0.5, 1));

    form = MixedForm(Winterval(-2, 1));
    result = form / 0;
    EXPECT_EQ(result.intersected_bounds(), Winterval(-INFINITY, INFINITY));
}
