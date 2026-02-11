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
    _interval_bounds(interval_rep) {}
MixedForm::MixedForm(const AffineForm &affine_rep) :
    _affine_rep(affine_rep),
    _interval_bounds(affine_rep.to_interval()) {}
MixedForm::MixedForm(const Winterval &interval_rep) :
    _affine_rep(interval_rep),
    _interval_bounds(interval_rep) {}
MixedForm::MixedForm() :
    _affine_rep(AffineForm()),
    _interval_bounds(Winterval()) {}

MixedForm::~MixedForm() = default;

MixedForm MixedForm::union_with(const MixedForm &w) const {
    // Loses noise symbol dependence, but this would happen anyways.
    return MixedForm(interval_bounds().union_with(w.interval_bounds()));
}

std::vector<MixedForm> MixedForm::split(uint32_t num_splits) const {
    std::vector results = std::vector<MixedForm>();
    results.reserve(num_splits);
    // Since the affine form cannot be meaningfully split while preserving noise symbols,
    // we only split over the intersected bounds.
    auto interval_splits = _interval_bounds.split(num_splits);

    for (const Winterval& split : interval_splits) {
        results.emplace_back(split);
    }

    return results;
}


/*
 * Accessors
 */
const AffineForm &MixedForm::affine_rep() const {
    return _affine_rep;
}
const Winterval &MixedForm::interval_bounds() const {
    return _interval_bounds;
}
Winterval MixedForm::intersected_bounds() const {
    auto min_intersect = std::max(_affine_rep.to_interval().min(), _interval_bounds.min());
    auto max_intersect = std::min(_affine_rep.to_interval().max(), _interval_bounds.max());

    if (min_intersect > max_intersect) {
        // This can happen e.g. when dividing by 0.
        max_intersect = min_intersect;
    }

    return {min_intersect, max_intersect};
}
/*
 * Scalar operators
 */
MixedForm MixedForm::operator+(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep + scalar, _interval_bounds + scalar };
}
MixedForm MixedForm::operator-(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return { _affine_rep - scalar, _interval_bounds - scalar };
}
MixedForm MixedForm::operator*(const double scalar) const {
    // Must propagate affine form, even if interval tighter, to preserve relationship between vars.
    return {
        _affine_rep * scalar,
        interval_intersection(_affine_rep * scalar, _interval_bounds * scalar)
    };
}
MixedForm MixedForm::operator/(const double scalar) const {
    // Divison by 0 ill defined for affine forms.
    if (scalar == 0) {
        return MixedForm(_interval_bounds / scalar);
    }

    // Otherwise, propagate affine form, even if interval tighter, to preserve relationship between vars.
    return {
        _affine_rep / scalar,
        interval_intersection(_affine_rep / scalar, _interval_bounds / scalar)
    };
}

/*
 * Binary mixed relational operations.
 */
bool MixedForm::operator==(const MixedForm &rhs) const {
    return _affine_rep == rhs._affine_rep && _interval_bounds == rhs._interval_bounds;
}
bool MixedForm::operator!=(const MixedForm &rhs) const {
    return !operator==(rhs);
}
bool MixedForm::operator>(const MixedForm &right) const {
    return intersected_bounds() > right.intersected_bounds();
}
bool MixedForm::operator>=(const MixedForm &right) const {
    return intersected_bounds() >= right.intersected_bounds();
}
bool MixedForm::operator<(const MixedForm &right) const {
    return intersected_bounds() < right.intersected_bounds();
}
bool MixedForm::operator<=(const MixedForm &right) const {
    return intersected_bounds() <= right.intersected_bounds();
}

/*
 * Scalar relational operations.
 */
bool MixedForm::operator>(double scalar) const {
    return intersected_bounds() > scalar;
}
bool MixedForm::operator>=(double scalar) const {
    return intersected_bounds() >= scalar;
}
bool MixedForm::operator<(double scalar) const {
    return intersected_bounds() < scalar;
}
bool MixedForm::operator<=(double scalar) const {
    return intersected_bounds() <= scalar;
}

/*
 * Wixed-Wixed operations
 */
MixedForm MixedForm::operator-(const MixedForm &right) const {
    return { _affine_rep - right._affine_rep, _interval_bounds - right._interval_bounds };
}
MixedForm MixedForm::operator+(const MixedForm &w) const {
    return { _affine_rep + w._affine_rep, _interval_bounds + w._interval_bounds };
}
MixedForm MixedForm::operator*(const MixedForm &w) const {
    return { _affine_rep * w._affine_rep, _interval_bounds * w._interval_bounds };
}
MixedForm MixedForm::operator/(const MixedForm &w) const {
    return { _affine_rep / w._affine_rep, _interval_bounds / w._interval_bounds };
}

/*
 * Unary wixed operations
 */
MixedForm MixedForm::abs() const {
    // Use only the interval. Abs over affine forms repeatedly reduces the magnitude of the form.
    // This can lead to (technically sound, under our semantics) but very small magnitude results.
    return MixedForm(_interval_bounds.abs());
}
MixedForm MixedForm::pow(uint32_t pow) const {
    // TODO: fix powers to be only unsigned.
    return { _affine_rep.pow(pow), _interval_bounds.pow(pow) };
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