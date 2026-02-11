
#include <fstream>

#include "MixedForm/MixedForm.hpp"

int main() {
    // Quick I/O sanity test.
    std::ofstream file("out.json");
    cereal::JSONOutputArchive archive(file);

    MixedForm w = MixedForm(AffineForm(Winterval(-2, 3)), Winterval(-1, 2));
    archive(w);
    return 0;
}
