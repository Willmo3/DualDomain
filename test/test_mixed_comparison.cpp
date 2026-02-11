//
// Created by will on 12/7/25.
//

#include "gtest/gtest.h"
#include "MixedForm/MixedForm.hpp"

auto form_a = MixedForm(Winterval(1, 2));

TEST(mixed_comparison, binary_equality) {
    auto b = MixedForm(Winterval(-1, 2));
    EXPECT_TRUE(form_a != b);
    EXPECT_TRUE(form_a == form_a);
}
TEST(mixed_comparison, binary_comparison) {
    auto b = MixedForm(Winterval(3, 3));
    EXPECT_TRUE(form_a < b);
    EXPECT_TRUE(form_a <= b);
    EXPECT_FALSE(form_a > b);
    EXPECT_FALSE(form_a >= b);
}

TEST(mixed_comparison, scalar_gt) {
    EXPECT_TRUE(form_a > 0);
    EXPECT_FALSE(form_a > 1);
}
TEST(mixed_comparison, scalar_lt) {
    EXPECT_TRUE(form_a < 5);
    EXPECT_FALSE(form_a < 2);
}
TEST(mixed_comparison, scalar_lte) {
    EXPECT_TRUE(form_a <= 2);
}
TEST(mixed_comparison, scalar_gte) {
    EXPECT_TRUE(form_a >= 1);
}