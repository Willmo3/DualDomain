//
// Created by will on 10/22/25.
//

#include "MixedForm/MixedForm.hpp"
#include "cereal/archives/json.hpp"
#include <gtest/gtest.h>

TEST(mixed_serialization, test_mixed_serialization) {
    // Create a MixedForm
    MixedForm original_form(AffineForm(Winterval(-2, 3)), Winterval(-1, 2));

    // Serialize to JSON
    std::ostringstream os;
    {
        cereal::JSONOutputArchive archive(os);
        archive(original_form);
    }

    // Deserialize from JSON
    MixedForm deserialized_form = MixedForm(); // Placeholder initialization
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