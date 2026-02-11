//
// Created by will on 10/17/25.
//

#include <cmath>
#include <gtest/gtest.h>
#include "MixedForm/MixedForm.hpp"

auto a = MixedForm(Winterval(2, 3));
auto b = MixedForm(Winterval(1, 4));

TEST(mixed_binop, test_mixed_addition) {
    auto result = a + b;
    EXPECT_EQ(result.intersected_bounds(), Winterval(3, 7));
}
TEST(mixed_binop, test_mixed_subtraction) {
    auto result = a - b;
    EXPECT_EQ(result.intersected_bounds(), Winterval(-2, 2));
}
TEST(mixed_binop, test_mixed_multiplication) {
    auto result = a * b;
    EXPECT_EQ(result.intersected_bounds(), Winterval(2, 12));
}
TEST(mixed_binop, test_mixed_division) {
    auto result = a / b;
    // NOTE: weird behavior when dividing by interval that includes 0, because the affine reps produce a tighter, but still sound, bound.
    EXPECT_EQ(result.intersected_bounds(), Winterval(0.5, 3));
}
/*
 * Compositional
 */
TEST(mixed_binop, test_mixed_union) {
    auto result = a.union_with(b);
    EXPECT_EQ(result.intersected_bounds(), Winterval(1, 4));
}
TEST(mixed_binop, test_mixed_split) {
    auto form = MixedForm(Winterval(0, 7));
    auto splits = form.split(4);

    EXPECT_EQ(splits[0].intersected_bounds(), Winterval(0, 1.75));
    EXPECT_EQ(splits[1].intersected_bounds(), Winterval(1.75, 3.5));
    EXPECT_EQ(splits[2].intersected_bounds(), Winterval(3.5, 5.25));
    EXPECT_EQ(splits[3].intersected_bounds(), Winterval(5.25, 7.0));
}