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

void test_binary_wixed_ops() {
    auto a = WixedForm(WaffineForm(Winterval(2, 3)), Winterval(-1, 2));
    auto b = WixedForm(WaffineForm(Winterval(1, 4)), Winterval(0, 3));

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
    std::cout << a / b << std::endl;
}

void test_unary_wixed_ops() {
    auto form = WixedForm(Winterval(-10, 3));
    std::cout << form.abs() << std::endl;
    std::cout << form.pow(2) << std::endl;
}

int main() {
    test_scalar_wixed();
    return 0;
}
