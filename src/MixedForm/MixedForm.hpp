//
// Created by will on 10/8/25.
//

#ifndef WIXED_WIXEDFORM_H
#define WIXED_WIXEDFORM_H

#include <memory>

#include "Caffeine/AffineForm.hpp"
#include "Winterval/Winterval.hpp"

/**
 * Mixed affine form. Tracks both interval and affine representation of data.
 * Credit to Phocus library.
 *
 * @author Will Morris
 */
class MixedForm {
public:
    /*
     * Constructors
     */

    /**
     * Create a new MixedForm from an affine form and an interval.
     * @param affine_rep Affine form to construct from.
     * @param interval_rep Interval to construct from.
     */
    MixedForm(const AffineForm &affine_rep, const Winterval &interval_rep);

    /**
     * Create a new MixedForm from an affine form. Interval is constructed from affine form.
     * @param affine_rep Affine form to construct from.
     */
    explicit MixedForm(const AffineForm &affine_rep);

    /**
     * Create a new MixedForm from an interval. Affine form is constructed from interval.
     * @param interval_rep Interval to construct from.
     */
    explicit MixedForm(const Winterval &interval_rep);

    /**
     * Default constructor, useful for serialization.
     * Create an empty MixedForm by calling default constructor on subcomponents.
     */
    MixedForm();

    /**
     * Destructor
     */
    ~MixedForm();

    /*
     * Accessors
     */
    const AffineForm &affine_rep() const;
    const Winterval &interval_bounds() const;

    /*
     * Wixed-Wixed operations
     */
    MixedForm operator+(const MixedForm &w) const;
    MixedForm operator-(const MixedForm &w) const;
    MixedForm operator*(const MixedForm &w) const;
    MixedForm operator/(const MixedForm &w) const;

    /*
     * Unary Wixed operations
     */
    MixedForm pow(uint32_t power) const;
    /**
     * @return Absolute value of interval bounds of this form.
     * Affine form is not considered -- abs is poorly defined for affine forms.
     */
    MixedForm abs() const;

    /*
     * Wixed-scalar operations
     */
    MixedForm operator+(double scalar) const;
    MixedForm operator-(double scalar) const;
    MixedForm operator*(double scalar) const;
    MixedForm operator/(double scalar) const;

    /*
     * Scalar relational operations
     */
    bool operator<(double scalar) const;
    bool operator<=(double scalar) const;
    bool operator>(double scalar) const;
    bool operator>=(double scalar) const;

    /*
     * Assorted helpers
     */
    bool operator==(const MixedForm &other) const;

    /*
     * Serialization support through cereal.
     */
    template<class Archive>
    void serialize(Archive & archive) {
        archive( cereal::make_nvp("affine_form", _affine_rep),
            cereal::make_nvp("intersected_bounds", _intersected_bounds ));
    }


private:
    /*
     * Internal helpers.
     */
    /**
     * @param a Affine form to intersect
     * @param b Interval to intersect
     * @return An affine form soundly representing the intersection of these two forms.
     */
    static Winterval interval_intersection(const AffineForm &a, const Winterval &b);

    /*
     * Private fields
     * Note: we use values here because large portions of the object are in memory.
     */
    AffineForm _affine_rep;
    Winterval _intersected_bounds;
};

// Utility pipe to stdout
std::ostream& operator<<(std::ostream& os, const MixedForm &rhs);


#endif //WIXED_WIXEDFORM_H