//
// Created by will on 10/22/25.
//

#include "WixedForm/WixedForm.hpp"
#include "cereal/archives/json.hpp"
#include <gtest/gtest.h>

TEST(wixed_serialization, test_wixed_serialization) {
    // Create a WixedForm
    WixedForm original_form(WaffineForm(Winterval(-2, 3)), Winterval(-1, 2));

    // Serialize to JSON
    std::ostringstream os;
    {
        cereal::JSONOutputArchive archive(os);
        archive(original_form);
    }

    // Deserialize from JSON
    WixedForm deserialized_form = WixedForm(); // Placeholder initialization
    {
        std::istringstream is(os.str());
        cereal::JSONInputArchive archive(is);
        archive(deserialized_form);
    }

    // Check that the deserialized form matches the original
    EXPECT_EQ(original_form.interval_bounds().min(), deserialized_form.interval_bounds().min());
    EXPECT_EQ(original_form.interval_bounds().max(), deserialized_form.interval_bounds().max());
    EXPECT_EQ(original_form.affine_rep().to_interval().min(), deserialized_form.affine_rep().to_interval().min());
    EXPECT_EQ(original_form.affine_rep().to_interval().max(), deserialized_form.affine_rep().to_interval().max());

    EXPECT_EQ(original_form, deserialized_form);
}