/**
 * @file Vector2.h
 * Contains template class Vector2 of type V
 *
 * @author <a href="mailto:martin.kallnik@gmx.de">Martin Kallnik</a>
 * @author Max Risler
 */

#ifndef __Vector2_h__
#define __Vector2_h__

#include <cmath>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Geometry>

//namespace itandroids_lib {
namespace math {

/** This class represents a 2-vector */
template<class V>
class Vector2 {
public:
    /** The vector values */
    V &x;
    V &y;
private:
    /** The real implementation of the vector */
    Eigen::Matrix<V, 2, 1> vector;
public:
    /** Default constructor. */
    Vector2<V>() : vector(2),
                   x(vector[0]), y(vector[1]) {
        x = V();
        y = V();
    }

    /** Default constructor. */
    Vector2<V>(V x, V y) : Vector2<V>() {
        this->x = x;
        this->y = y;
    }

    /** Assignment operator
     *\param other The other vector that is assigned to this one
     *\return A reference to this object after the assignment.
     */
    Vector2<V> &operator=(const Vector2<V> &other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    /** Copy constructor
     *\param other The other vector that is copied to this one
     */
    Vector2<V>(const Vector2<V> &other) : Vector2<V>() {
        *this = other;
    }

    /** Addition of another vector to this one.
     *\param other The other vector that will be added to this one
     *\return A reference to this object after the calculation.
     */
    Vector2<V> &operator+=(const Vector2<V> &other) {
        vector += other.vector;
        return *this;
    }

    /** Substraction of this vector from another one.
     *\param other The other vector this one will be substracted from
     *\return A reference to this object after the calculation.
     */
    Vector2<V> &operator-=(const Vector2<V> &other) {
        vector -= other.vector;
        return *this;
    }

    /** Multiplication of this vector by a factor.
     *\param factor The factor this vector is multiplied by
     *\return A reference to this object after the calculation.
     */
    Vector2<V> &operator*=(const V &factor) {
        vector *= factor;
        return *this;
    }

    /** Division of this vector by a factor.
     *\param factor The factor this vector is divided by
     *\return A reference to this object after the calculation.
     */
    Vector2<V> &operator/=(const V &factor) {
        vector /= factor;
        return *this;

    }

    /** Addition of another vector to this one.
     *\param other The other vector that will be added to this one
     *\return A new object that contains the result of the calculation.
     */
    Vector2<V> operator+(const Vector2<V> &other) const {
        return Vector2<V>(*this) += other;
    }

    /** Subtraction of another vector to this one.
     *\param other The other vector that will be added to this one
     *\return A new object that contains the result of the calculation.
     */
    Vector2<V> operator-(const Vector2<V> &other) const {
        return Vector2<V>(*this) -= other;
    }

    /** Negation of this vector.
     *\return A new object that contains the result of the calculation.
     */
    Vector2<V> operator-() const {
        return Vector2<V>() -= *this;
    }

    /** Inner product of this vector and another one.
     *\param other The other vector this one will be multiplied by
     *\return The inner product.
     */
    V operator*(const Vector2<V> &other) const {
        // Using the eigen product to try to optimize it
        return vector.dot(other.vector.transpose());
    }

    /** Multiplication of this vector by a factor.
     *\param factor The factor this vector is multiplied by
     *\return A new object that contains the result of the calculation.
     */
    Vector2<V> operator*(const V &factor) const {
        return Vector2<V>(*this) *= factor;
    }

    /** Division of this vector by a factor.
     *
     *\param factor The factor this vector is divided by
     *\return A new object that contains the result of the calculation.
     */
    Vector2<V> operator/(const V &factor) const {
        return Vector2<V>(*this) /= factor;
    }

    /** Comparison of another vector with this one.
     *\param other The other vector that will be compared to this one
     *\return Whether the two vectors are equal.
     */
    bool operator==(const Vector2<V> &other) const {
        return vector == other.vector;
    }


    /** Comparison of another vector with this one.
     *\param other The other vector that will be compared to this one.
     *\return Whether the two vectors are unequal.
     */
    bool operator!=(const Vector2<V> &other) const {
        return !(*this == other);
    }

    /** Calculation of the length of this vector.
     *\return The length.
     */
    V abs() const {
        return vector.norm();
    }

    /** Calculation of the square length of this vector.
     *\return length*length.
     */
    V squareAbs() const {
        return vector.dot(vector);
    }

    /** normalize this vector.
     *\param len The length, the vector should be normalized to, default=1.
     *\return the normalized vector.
     */
    Vector2<V> normalize(V len = 1) {
        vector.normalize();
        vector *= len;
        return *this;
    }


    /**
     * Calculate of the distance between this vector and another one
     * \param other The other vector to be used to calculate the distance
     * \return Distance between two vectors
     */
    double distance(const Vector2<V> &other) const {
        return (vector - other.vector).norm();
    }

    /** transpose this vector.
     *\return the transposed vector.
     */
    Vector2<V> transpose() {
        V buffer = x;
        x = y;
        y = buffer;
        return *this;
    }

    /** the vector is rotated left by 90 degrees.
     *\return the rotated vector.
     */
    Vector2<V> rotateLeft() {
        V buffer = -y;
        y = x;
        x = buffer;
        return *this;
    }

    /** the vector is rotated right by 90 degrees.
     *\return the rotated vector.
     */
    Vector2<V> rotateRight() {
        V buffer = -x;
        x = y;
        y = buffer;
        return *this;
    }

    /** the vector is rotated by alpha degrees.
     *\return the rotated vector.
     * @todo it shouldn't return a vector
     */
    Vector2<V> rotate(double alpha) {
        Eigen::Rotation2D<V> rot(alpha);
        vector = rot * vector;
        return *this;
    }

    /**
     * A rotation function that doesn't affect the instance vector
     * @param alpha
     * @return the rotated vector
     */
    Vector2<V> rotation(double alpha) const {
        Vector2<V> retVal(*this);
        retVal.rotate(alpha);
        return retVal;
    }


    /** Converts from a coordinate frame relative to the origin Pose2D passed in,
     to the one that the origin Pose2D was defined in. */
    Vector2<V> relativeToGlobal(const Vector2<V> &old_origin, double old_rot) const {
        Vector2<V> retVal(*this);
        retVal.rotate(old_rot);
        retVal += old_origin;
        return retVal;
    }

    /** Converts from the coordinate frame the origin Pose2D is defined in,
     to one relative to it. */
    Vector2<V> globalToRelative(const Vector2<V> &new_origin, double new_rot) {
        Vector2<V> retVal(*this);
        retVal -= new_origin;
        retVal.rotate(-new_rot);
        return retVal;
    }

    /**
     * array-like member access.
     * \param i index of coordinate
     * \return reference to x or y
     */
    V &operator[](int i) {
        return vector[i];
    }

    /**
     * const array-like member access.
     * \param i index of coordinate
     * \return reference to x or y
     */
    const V &operator[](int i) const {
        return vector[i];
    }

    /**
     * Calculation of the angle of this vector
     * \return angle of this vector
     */
    double angle() const {
        return atan2((double) y, (double) x);
    }

    /**
     * Calculate of the angle between this vector and another one
     * \param other The other vector to be used to calculate the angle
     * \return Angle between two vectors
     */
    double angle(Vector2<V> other) const {
        double dx = this->x - other.x;
        double dy = this->y - other.y;
        return atan2(dy, dx);
    }

    double cross(Vector2<V> &other) const {
        return (this->x * other.y - this->y * other.x);
    }

    /**
     * Calculation of the square of the vector.
     * \deprecated
     * \return The square
     */
    V sqr() const {
        return squareAbs();
    }


    /**
     * This is the offstream operator for easier data representation
     * @param out
     * @param vec
     * @return out
     */
    friend std::ostream &operator<<(std::ostream &out, const Vector2<V> &vec) {
        out << "(" << vec.x << "," << vec.y << ")";
        return out;
    }
};

template<class V>
Vector2<V> operator*(const V &factor, const Vector2<V> &vector) {
    return Vector2<V>(vector) *= factor;
}

/**
 * This is a double especialization for the == operator, in case the near comparison is better
 */
//	template<>
//	bool Vector2<double>::operator==(const Vector2<double> & other) const{
//		double max_diff = 0.0001;
//		return (vector-other.vector).norm() < max_diff;
//	}


using Vector2d = Vector2<double>;
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

} /* namespace math */
//} /* namespace itandroids_lib */

#endif // __Vector2_h__
