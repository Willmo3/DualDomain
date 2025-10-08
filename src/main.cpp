#include <iostream>

#include "WixedForm/WixedForm.hpp"

void test_scalar_wixed() {
    auto form = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    std::cout << form -2 << std::endl;
    std::cout << form +2 << std::endl;
    std::cout << form *2 << std::endl;
    std::cout << form /2 << std::endl;
    std::cout << form / 0 << std::endl;
}

void test_scalar_relational_wixed() {
    auto form = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    std::cout << (form < 2) << std::endl;
    std::cout << (form <= 2) << std::endl;
    std::cout << (form > 2) << std::endl;
    std::cout << (form >= 2) << std::endl;
}

int main() {
    test_scalar_relational_wixed();
    return 0;
}
