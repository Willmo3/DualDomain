//
// Created by will on 10/8/25.
//

#include "WixedForm.hpp"

#include <complex.h>
#include <memory>

/*
 * Constructors
 */
// NOTE: the repeated copying here may be cause for performance trouble later on, as new forms will be generated frequently.
WixedForm::WixedForm(const WaffineForm &affine_rep, const Winterval &interval_rep) :
    _affine_rep(std::make_unique<WaffineForm>(affine_rep)),
    _intersected_bounds(std::make_unique<Winterval>(interval_intersection(affine_rep, interval_rep))) {}

WixedForm::WixedForm(const WaffineForm &affine_rep) :
    _affine_rep(std::make_unique<WaffineForm>(affine_rep)),
    _intersected_bounds(std::make_unique<Winterval>(affine_rep.to_interval())) {}

WixedForm::WixedForm(const Winterval &interval_rep) :
    _affine_rep(std::make_unique<WaffineForm>(WaffineForm(interval_rep))),
    _intersected_bounds(std::make_unique<Winterval>(interval_rep)) {}

WixedForm::~WixedForm() = default;

/*
 * Accessors
 */
const WaffineForm &WixedForm::affine_rep() const {
    return *_affine_rep;
}
const Winterval &WixedForm::interval_bounds() const {
    return *_intersected_bounds;
}

/*
 * Scalar operators
 */
WixedForm WixedForm::operator+(const double scalar) const {
    // Addition and subtraction are exact over intervals, and our reduced bounds are minimal, so no need for intersection.
    return WixedForm(_intersected_bounds->operator+(scalar));
}
WixedForm WixedForm::operator-(const double scalar) const {
    // Addition and subtraction are exact over intervals, and our reduced bounds are minimal, so no need for intersection.
    return WixedForm(_intersected_bounds->operator-(scalar));
}
WixedForm WixedForm::operator*(const double scalar) const {
    return WixedForm(
        interval_intersection(_affine_rep->operator*(scalar), _intersected_bounds->operator*(scalar)));
}
WixedForm WixedForm::operator/(const double scalar) const {
    return WixedForm(
        interval_intersection(_affine_rep->operator/(scalar), _intersected_bounds->operator/(scalar)));
}

/*
 * Scalar relational operations.
 */
bool WixedForm::operator>(double scalar) const {
    return *_intersected_bounds > scalar;
}
bool WixedForm::operator>=(double scalar) const {
    return *_intersected_bounds >= scalar;
}
bool WixedForm::operator<(double scalar) const {
    return *_intersected_bounds < scalar;
}
bool WixedForm::operator<=(double scalar) const {
    return *_intersected_bounds <= scalar;
}

/*
 * Internal helpers
 */
Winterval WixedForm::interval_intersection(const WaffineForm &a, const Winterval &b) {
    auto min_intersect = std::max(a.to_interval().min(), b.min());
    auto max_intersect = std::min(a.to_interval().max(), b.max());

    if (min_intersect > max_intersect) {
        // This can happen e.g. when dividing by 0.
        max_intersect = min_intersect;
    }

    return {min_intersect, max_intersect};
}

std::ostream& operator<<(std::ostream& os, const WixedForm &rhs) {
    os << rhs.interval_bounds();
    return os;
}