//
// Created by will on 10/17/25.
//

#include <cmath>
#include <gtest/gtest.h>
#include "../src/WixedForm/WixedForm.hpp"

TEST(wixed_binop, test_wixed_addition) {
    auto a = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a + b;
    EXPECT_EQ(result.interval_bounds(), Winterval(3, 5));
}
TEST(wixed_binop, test_wixed_subtraction) {
    auto a = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a - b;
    EXPECT_EQ(result.interval_bounds(), Winterval(-1, 1));
}
TEST(wixed_binop, test_wixed_multiplication) {
    auto a = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a * b;
    EXPECT_EQ(result.interval_bounds(), Winterval(2, 6));
}
TEST(wixed_binop, test_wixed_division) {
    auto a = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = WixedForm(WaffineForm(Winterval(-1, 4)), Winterval(0, 2));
    auto result = a / b;
    // NOTE: weird behavior when dividing by interval that includes 0, because the affine reps produce a tighter, but still sound, bound.
    EXPECT_EQ(result.interval_bounds(), Winterval(1, 12));
}