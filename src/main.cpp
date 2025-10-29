
#include <fstream>

#include "WixedForm/WixedForm.hpp"

int main() {
    // Quick I/O sanity test.
    std::ofstream file("out.json");
    cereal::JSONOutputArchive archive(file);

    WixedForm w = WixedForm(AffineForm(Winterval(-2, 3)), Winterval(-1, 2));
    archive(w);
    return 0;
}
