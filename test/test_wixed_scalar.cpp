//
// Created by will on 10/9/25.
//

#include <cmath>
#include <gtest/gtest.h>
#include "WixedForm/WixedForm.hpp"

TEST(wixed_scalar, addition) {
    auto form = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto result = form + 2.0;
    EXPECT_EQ(result.interval_bounds(), Winterval(4, 4));
}
TEST(wixed_scalar, subtraction) {
    auto form = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto result = form - 2.0;
    EXPECT_EQ(result.interval_bounds(), Winterval(0, 0));
}
TEST(wixed_scalar, multiplication) {
    auto form = WixedForm(WaffineForm(Winterval(0, 3)), Winterval(-1, 2));
    auto result = form * 2.0;
    EXPECT_EQ(result.interval_bounds(), Winterval(0, 4));
}
TEST(wixed_scalar, division) {
    auto form = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(-1, 2));
    auto result = form / 2.0;
    EXPECT_EQ(result.interval_bounds(), Winterval(0.5, 1));

    form = WixedForm(WaffineForm(Winterval(-4, 2)), Winterval(-2, 1));
    result = form / 0;
    EXPECT_EQ(result.interval_bounds(), Winterval(-INFINITY, INFINITY));
}

TEST(wixed_scalar, gt) {
    auto form = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(-1, 2));
    EXPECT_TRUE(form > 0);
    EXPECT_FALSE(form > 1);
}
TEST(wixed_scalar, lt) {
    auto form = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(-1, 2));
    EXPECT_TRUE(form < 5);
    EXPECT_FALSE(form < 2);
}
TEST(wixed_scalar, lte) {
    auto form = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(-1, 2));
    EXPECT_TRUE(form <= 2);
}
TEST(wixed_scalar, gte) {
    auto form = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(-1, 2));
    EXPECT_TRUE(form >= 1);
}
