//
// Created by will on 10/8/25.
//

#include "MixedForm.hpp"

#include <complex>
#include <memory>

/*
 * Constructors
 */
// NOTE: the repeated copying here may be cause for performance trouble later on, as new forms will be generated frequently.
// TODO: ensure deep copy.
MixedForm::MixedForm(const AffineForm &affine_rep, const Winterval &interval_rep) :
    _affine_rep(affine_rep),
    _intersected_bounds(interval_intersection(affine_rep, interval_rep)) {}

MixedForm::MixedForm(const AffineForm &affine_rep) :
    _affine_rep(affine_rep),
    _intersected_bounds(affine_rep.to_interval()) {}

MixedForm::MixedForm(const Winterval &interval_rep) :
    _affine_rep(interval_rep),
    _intersected_bounds(interval_rep) {}

MixedForm::MixedForm() :
    _affine_rep(AffineForm()),
    _intersected_bounds(Winterval()) {}

MixedForm::~MixedForm() = default;

/*
 * Accessors
 */
const AffineForm &MixedForm::affine_rep() const {
    return _affine_rep;
}
const Winterval &MixedForm::interval_bounds() const {
    return _intersected_bounds;
}

/*
 * Scalar operators
 */
MixedForm MixedForm::operator+(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep + scalar, _intersected_bounds + scalar };
}
MixedForm MixedForm::operator-(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep - scalar, _intersected_bounds - scalar };
}
MixedForm MixedForm::operator*(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return {
        _affine_rep * scalar,
        interval_intersection(_affine_rep * scalar, _intersected_bounds * scalar)
    };
}
MixedForm MixedForm::operator/(const double scalar) const {
    // Divison by 0 ill defined for affine forms.
    if (scalar == 0) {
        return MixedForm(_intersected_bounds / scalar);
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
bool MixedForm::operator>(double scalar) const {
    return _intersected_bounds > scalar;
}
bool MixedForm::operator>=(double scalar) const {
    return _intersected_bounds >= scalar;
}
bool MixedForm::operator<(double scalar) const {
    return _intersected_bounds < scalar;
}
bool MixedForm::operator<=(double scalar) const {
    return _intersected_bounds <= scalar;
}

/*
 * Wixed-Wixed operations
 */
MixedForm MixedForm::operator-(const MixedForm &right) const {
    return { _affine_rep - right._affine_rep, _intersected_bounds - right._intersected_bounds };
}
MixedForm MixedForm::operator+(const MixedForm &w) const {
    return { _affine_rep + w._affine_rep, _intersected_bounds + w._intersected_bounds };
}
MixedForm MixedForm::operator*(const MixedForm &w) const {
    return { _affine_rep * w._affine_rep, _intersected_bounds * w._intersected_bounds };
}
MixedForm MixedForm::operator/(const MixedForm &w) const {
    return { _affine_rep / w._affine_rep, _intersected_bounds / w._intersected_bounds };
}
MixedForm MixedForm::union_with(const MixedForm &w) const {
    // Loses noise symbol dependence, but this would happen anyways.
    return MixedForm(interval_bounds().union_with(w.interval_bounds()));
}

/*
 * Unary wixed operations
 */
MixedForm MixedForm::abs() const {
    // Use only the interval. Abs over affine forms repeatedly reduces the magnitude of the form.
    // This can lead to (technically sound, under our semantics) but very small magnitude results.
    return MixedForm(_intersected_bounds.abs());
}
MixedForm MixedForm::pow(uint32_t pow) const {
    // TODO: fix powers to be only unsigned.
    return { _affine_rep.pow(pow), _intersected_bounds.pow(pow) };
}

/*
 * Public helpers
 */
bool MixedForm::operator==(const MixedForm &other) const {
    return _affine_rep == other._affine_rep && _intersected_bounds == other._intersected_bounds;
}


/*
 * Internal helpers
 */
Winterval MixedForm::interval_intersection(const AffineForm &a, const Winterval &b) {
    auto min_intersect = std::max(a.to_interval().min(), b.min());
    auto max_intersect = std::min(a.to_interval().max(), b.max());

    if (min_intersect > max_intersect) {
        // This can happen e.g. when dividing by 0.
        max_intersect = min_intersect;
    }

    return {min_intersect, max_intersect};
}

std::ostream& operator<<(std::ostream& os, const MixedForm &rhs) {
    os << "m" << rhs.interval_bounds();
    return os;
}