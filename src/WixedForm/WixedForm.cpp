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
// TODO: ensure deep copy.
WixedForm::WixedForm(const WaffineForm &affine_rep, const Winterval &interval_rep) :
    _affine_rep(affine_rep),
    _intersected_bounds(interval_intersection(affine_rep, interval_rep)) {}

WixedForm::WixedForm(const WaffineForm &affine_rep) :
    _affine_rep(affine_rep),
    _intersected_bounds(affine_rep.to_interval()) {}

WixedForm::WixedForm(const Winterval &interval_rep) :
    _affine_rep(interval_rep),
    _intersected_bounds(interval_rep) {}


WixedForm::~WixedForm() = default;

/*
 * Accessors
 */
const WaffineForm &WixedForm::affine_rep() const {
    return _affine_rep;
}
const Winterval &WixedForm::interval_bounds() const {
    return _intersected_bounds;
}

/*
 * Scalar operators
 */
WixedForm WixedForm::operator+(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep + scalar, _intersected_bounds + scalar };
}
WixedForm WixedForm::operator-(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep - scalar, _intersected_bounds - scalar };
}
WixedForm WixedForm::operator*(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return {
        _affine_rep * scalar,
        interval_intersection(_affine_rep * scalar, _intersected_bounds * scalar)
    };
}
WixedForm WixedForm::operator/(const double scalar) const {
    // Divison by 0 ill defined for affine forms.
    if (scalar == 0) {
        return WixedForm(_intersected_bounds / scalar);
    }

    // Otherwise, propagate affine form, even if interval tighter, to preserve relationship between vars.
    return {
        _affine_rep / scalar,
        interval_intersection(_affine_rep / scalar, _intersected_bounds / scalar)
    };
}

/*
 * Scalar relational operations.
 */
bool WixedForm::operator>(double scalar) const {
    return _intersected_bounds > scalar;
}
bool WixedForm::operator>=(double scalar) const {
    return _intersected_bounds >= scalar;
}
bool WixedForm::operator<(double scalar) const {
    return _intersected_bounds < scalar;
}
bool WixedForm::operator<=(double scalar) const {
    return _intersected_bounds <= scalar;
}

/*
 * Wixed-Wixed operations
 */
WixedForm WixedForm::operator-(const WixedForm &right) const {
    return { _affine_rep - right._affine_rep, _intersected_bounds - right._intersected_bounds };
}
WixedForm WixedForm::operator+(const WixedForm &w) const {
    return { _affine_rep + w._affine_rep, _intersected_bounds + w._intersected_bounds };
}
WixedForm WixedForm::operator*(const WixedForm &w) const {
    return { _affine_rep * w._affine_rep, _intersected_bounds * w._intersected_bounds };
}
WixedForm WixedForm::operator/(const WixedForm &w) const {
    return { _affine_rep / w._affine_rep, _intersected_bounds / w._intersected_bounds };
}

/*
 * Unary wixed operations
 */
WixedForm WixedForm::abs() const {
    return WixedForm(_intersected_bounds.abs());
}
WixedForm WixedForm::pow(uint32_t pow) const {
    // TODO: fix powers to be only unsigned.
    return { _affine_rep.pow(pow), _intersected_bounds.pow(pow) };
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