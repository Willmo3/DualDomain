//
// Created by will on 10/17/25.
//

#include <cmath>
#include <gtest/gtest.h>
#include "MixedForm/MixedForm.hpp"

TEST(mixed_binop, test_mixed_addition) {
    auto a = MixedForm(AffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = MixedForm(AffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a + b;
    EXPECT_EQ(result.interval_bounds(), Winterval(3, 5));
}
TEST(mixed_binop, test_mixed_subtraction) {
    auto a = MixedForm(AffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = MixedForm(AffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a - b;
    EXPECT_EQ(result.interval_bounds(), Winterval(-1, 1));
}
TEST(mixed_binop, test_mixed_multiplication) {
    auto a = MixedForm(AffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = MixedForm(AffineForm(Winterval(1, 4)), Winterval(0, 3));

    auto result = a * b;
    EXPECT_EQ(result.interval_bounds(), Winterval(2, 6));
}
TEST(mixed_binop, test_mixed_division) {
    auto a = MixedForm(AffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = MixedForm(AffineForm(Winterval(-1, 4)), Winterval(0, 2));
    auto result = a / b;
    // NOTE: weird behavior when dividing by interval that includes 0, because the affine reps produce a tighter, but still sound, bound.
    EXPECT_EQ(result.interval_bounds(), Winterval(1, 12));
}
TEST(mixed_binop, test_mixed_union) {
    auto a = MixedForm(AffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = MixedForm(AffineForm(Winterval(1, 4)), Winterval(0, 3));
    auto result = a.union_with(b);
    EXPECT_EQ(result.interval_bounds(), Winterval(1, 3));
}