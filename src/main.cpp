#include <iostream>

#include "WixedForm/WixedForm.hpp"

int main() {
    auto form = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    std::cout << form << std::endl;
    return 0;
}
