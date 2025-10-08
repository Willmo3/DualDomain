//
// Created by will on 10/8/25.
//

#include "WixedForm.hpp"

#include <memory>

/*
 * Constructors
 */
// NOTE: the repeated copying here may be cause for performance trouble later on, as new forms will be generated frequently.
WixedForm::WixedForm(const WaffineForm &affine_rep, const Winterval &interval_rep) :
    _affine_rep(std::make_unique<WaffineForm>(affine_rep)),
    _interval_bounds(std::make_unique<Winterval>(interval_intersection(affine_rep, interval_rep))) {}

WixedForm::WixedForm(const WaffineForm &affine_rep) :
    _affine_rep(std::make_unique<WaffineForm>(affine_rep)),
    _interval_bounds(std::make_unique<Winterval>(affine_rep.to_interval())) {}

WixedForm::~WixedForm() = default;

/*
 * Accessors
 */
const WaffineForm &WixedForm::affine_rep() const {
    return *_affine_rep;
}
const Winterval &WixedForm::interval_bounds() const {
    return *_interval_bounds;
}

/*
 * Internal helpers
 */
Winterval WixedForm::interval_intersection(const WaffineForm &a, const Winterval &b) {
    auto min_intersect = std::max(a.to_interval().min(), b.min());
    auto max_intersect = std::min(a.to_interval().max(), b.max());
    return {min_intersect, max_intersect};
}

std::ostream& operator<<(std::ostream& os, const WixedForm &rhs) {
    os << rhs.interval_bounds();
    return os;
}