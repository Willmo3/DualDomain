//
// Created by will on 10/17/25.
//

#include <gtest/gtest.h>
#include "WixedForm/WixedForm.hpp"

TEST(wixed_unop, test_wixed_abs) {
    auto form = WixedForm(Winterval(-10, 3));
    auto result = form.abs();
    EXPECT_EQ(result.interval_bounds(), Winterval(0, 10));
}
TEST(wixed_unop, test_wixed_pow) {
    auto form = WixedForm(Winterval(-3, 2));
    auto result = form.pow(2);
    EXPECT_EQ(result.interval_bounds(), Winterval(-6, 9));
}