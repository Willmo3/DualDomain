//
// Created by will on 10/8/25.
//

#ifndef WIXED_WIXEDFORM_H
#define WIXED_WIXEDFORM_H

#include <memory>

#include "../../lib/Waffine/WaffineForm.hpp"
#include "../../lib/Winterval/Winterval.hpp"

/**
 * Mixed affine form. Tracks both interval and affine representation of data.
 * Credit to Phocus library.
 *
 * @author Will Morris
 */
class WixedForm {
public:
    /*
     * Constructors
     */

    /**
     * Create a new WixedForm from an affine form and an interval.
     * @param affine_rep Affine form to construct from.
     * @param interval_rep Interval to construct from.
     */
    WixedForm(const WaffineForm &affine_rep, const Winterval &interval_rep);

    /**
     * Create a new WixedForm from an affine form. Interval is constructed from affine form.
     * @param affine_rep Affine form to construct from.
     */
    explicit WixedForm(const WaffineForm &affine_rep);

    /**
     * Create a new WixedForm from an interval. Affine form is constructed from interval.
     * @param interval_rep Interval to construct from.
     */
    explicit WixedForm(const Winterval &interval_rep);
    ~WixedForm();

    /*
     * Accessors
     */
    const WaffineForm &affine_rep() const;
    const Winterval &interval_bounds() const;

    /*
     * Wixed-Wixed operations
     */

    /*
    WixedForm &operator+(const WixedForm &w) const;
    WixedForm &operator-(const WixedForm &w) const;
    WixedForm &operator*(const WixedForm &w) const;
    WixedForm &operator/(const WixedForm &w) const;

    WixedForm pow(uint32_t power) const;
    WixedForm abs() const;
    */

    /*
     * Wixed-scalar operations
     */

    WixedForm operator+(double scalar) const;
    WixedForm operator-(double scalar) const;
    WixedForm operator*(double scalar) const;
    WixedForm operator/(double scalar) const;

    /*
     * Scalar relational operations
     */

    /*
    bool operator<(double scalar) const;
    bool operator<=(double scalar) const;
    bool operator>(double scalar) const;
    bool operator>=(double scalar) const;
    */

private:
    /*
     * Internal helpers.
     */
    /**
     * @param a Affine form to intersect
     * @param b Interval to intersect
     * @return An affine form soundly representing the intersection of these two forms.
     */
    static Winterval interval_intersection(const WaffineForm &a, const Winterval &b);

    /*
     * Private fields
     */
    std::unique_ptr<WaffineForm> _affine_rep;
    std::unique_ptr<Winterval> _intersected_bounds;
};

// Utility pipe to stdout
std::ostream& operator<<(std::ostream& os, const WixedForm &rhs);


#endif //WIXED_WIXEDFORM_H