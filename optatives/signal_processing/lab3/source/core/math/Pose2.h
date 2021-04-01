//
// Created by francisco on 01/02/17.
//

#ifndef ITANDROIDS_LIB_POSE2_H
#define ITANDROIDS_LIB_POSE2_H

#include <vector>
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Range.h"
#include "math/Common.h"

//namespace itandroids_lib{
namespace math{

template<typename Scalar, typename RotationScalar>
class Pose2 {
public:

    RotationScalar rotation;
    Vector2<Scalar> translation;

    /**
     * This is a construtor from a Vector3 to a Pose2
     * @param vector Vector3
     */
    template <typename VectorScalar>
    Pose2<Scalar, RotationScalar>(Vector3<VectorScalar> vector) {
        translation.x = (Scalar)vector.x;
        translation.y = (Scalar) vector.y;
        rotation = (RotationScalar) vector.z;
    }

    /** noargs-constructor*/
    Pose2<Scalar, RotationScalar>() :
            rotation(0), translation(0, 0) {
    }

    /** constructor from rotation and translation
     * \param rotation rotation (double)
     * \param translation translation (Vector2)
     */
    template<typename EntryRotationScalar, typename VectorScalar>
    Pose2<Scalar, RotationScalar>(EntryRotationScalar rotation, const Vector2<VectorScalar>& translation = Vector2<VectorScalar>()) :
            rotation(rotation), translation(translation) {
    }

    /** constructor from rotation and translation
     * \param rot rotation (double)
     * \param x translation.x (double)
     * \param y translation.y (double)
     */
    Pose2<Scalar, RotationScalar>( RotationScalar rot, const Scalar x, const Scalar y) :
            rotation(rot), translation(x, y) {
    }

    /** constructor from translation
     * \param translation translation (Vector2)
     */
    Pose2<Scalar, RotationScalar>(const Vector2<Scalar>& translation) :
            rotation(0), translation(translation) {
    }

    /** constructor from two translation values
     * \param x translation x component
     * \param y translation y component
     */
    Pose2<Scalar, RotationScalar>(const Scalar x, const Scalar y) :
            rotation(0), translation(x, y) {
    }
    /**
     * Constructor that uses a simple rotation value
     * @param rotation
     */
    template<typename EntryRotationScalar>
    Pose2<Scalar, RotationScalar>(const EntryRotationScalar rotation) : rotation(rotation){
    };

    /** set using vector of doubles as x,y,rot */

    void setValues(std::vector<Scalar> vals) {
        if (vals.size() != 3)
            return;
        translation.x = vals[0];
        translation.y = vals[1];
        rotation = (RotationScalar) vals[2];
    }

    /** get the Angle
     * @return Angle the Angle which defines the rotation
     */
    inline RotationScalar getAngle() const {
        return rotation;
    }

    /** set rotation from Angle
     * @return the new Pose2<Scalar, RotationScalar>
     */
    inline Pose2<Scalar, RotationScalar> fromAngle(const Scalar a) {
        rotation = a;
        return *this;
    }

    /** get the cos of the angle
     * @return the cos of the angle
     */
    inline double getCos() const {
        return cosf(rotation);
    }

    /** get the sin of the angle
     * @return the sin of the angle
     */
    inline double getSin() const {
        return sinf(rotation);
    }

    /** Assignment operator
     *\param other The other Pose2<Scalar, RotationScalar> that is assigned to this one
     *\return A reference to this object after the assignment.
     */
    Pose2<Scalar, RotationScalar>& operator=(const Pose2<Scalar, RotationScalar>& other) {
        rotation = other.rotation;
        translation = other.translation;
        return *this;
    }

    /** Copy constructor
     *\param other The other vector that is copied to this one
     */
    Pose2<Scalar, RotationScalar>(const Pose2<Scalar, RotationScalar>& other) {
        *this = other;
    }

    /** Multiplication of a Vector2 with this Pose2<Scalar, RotationScalar>
     *\param point The Vector2 that will be multiplicated with this Pose2<Scalar, RotationScalar>
     *\return The resulting Vector2
     */

    Vector2<Scalar> operator*(const Vector2<Scalar>& point) const {
        return (point.rotation(rotation) + translation);
    }

    Pose2<Scalar, RotationScalar> operator*(Scalar scalar) {
        Pose2<Scalar, RotationScalar> res(*this);
        res.translation *= scalar;
        res.rotation *= (RotationScalar) scalar;
        return res;
    }

    /** Comparison of another pose with this one.
     *\param other The other pose that will be compared to this one
     *\return Whether the two poses are equal.
     */
    bool operator==(const Pose2<Scalar, RotationScalar>& other) const {
        return ((translation == other.translation)
                && (rotation == other.rotation));
    }

    /** Comparison of another pose with this one.
     *\param other The other pose that will be compared to this one
     *\return Whether the two poses are unequal.
     */
    bool operator!=(const Pose2<Scalar, RotationScalar>& other) const {
        return !(*this == other);
    }

    /**Concatenation of this pose with another pose.
     *\param other The other pose that will be concatenated to this one.
     *\return A reference to this pose after concatenation.
     */
    Pose2<Scalar, RotationScalar>& operator+=(const Pose2<Scalar, RotationScalar>& other) {
        translation = *this * other.translation;
        rotation += other.rotation;
        rotation = normalize(rotation);
        return *this;
    }

    /**A concatenation of this pose and another pose.
     *\param other The other pose that will be concatenated to this one.
     *\return The resulting pose.
     */
    Pose2<Scalar, RotationScalar> operator+(const Pose2<Scalar, RotationScalar>& other) const {
        Pose2<Scalar, RotationScalar> result;
        result.translation = this->translation + other.translation;
        result.rotation = this->rotation + other.rotation;
        return result;
        //return Pose2<Scalar, RotationScalar>(*this) += other;
    }

    /**Subtracts a difference pose from this one to get the source pose. So if A+B=C is the addition/concatenation, this calculates C-B=A.
     *\param diff The difference Pose2<Scalar, RotationScalar> that shall be subtracted.
     *\return The resulting source pose. Adding diff to it again would give the this pose back.
     */
    Pose2<Scalar, RotationScalar> minusDiff(const Pose2<Scalar, RotationScalar>& diff) const {
        RotationScalar rot = rotation - diff.rotation;
        double s = sinf(rot);
        double c = cosf(rot);
        return Pose2<Scalar, RotationScalar>(rot,
                                             translation.x - c * diff.translation.x + s * diff.translation.y,
                                             translation.y - c * diff.translation.y - s * diff.translation.x);
    }

    /**Difference of this pose relative to another pose. So if A+B=C is the addition/concatenation, this calculates C-A=B.
     *\param other The other pose that will be used as origin for the new pose.
     *\return A reference to this pose after calculating the difference.
     */
    Pose2<Scalar, RotationScalar>& operator-=(const Pose2<Scalar, RotationScalar>& other) {
        translation -= other.translation;
        Pose2<Scalar, RotationScalar> p(-other.rotation);
        return *this = p + *this;
    }

    /**Difference of this pose relative to another pose.
     *\param other The other pose that will be used as origin for the new pose.
     *\return The resulting pose.
     */
    Pose2<Scalar, RotationScalar> operator-(const Pose2<Scalar, RotationScalar>& other) const {
        return Pose2<Scalar, RotationScalar>(*this) -= other;
    }

    /**Concatenation of this pose with another pose
     *\param other The other pose that will be concatenated to this one.
     *\return A reference to this pose after concatenation
     */
    Pose2<Scalar, RotationScalar>& conc(const Pose2<Scalar, RotationScalar>& other) {
        return *this += other;
    }

    /**Translate this pose by a translation vector
     *\param trans Vector to translate with
     *\return A reference to this pose after translation
     */
    Pose2<Scalar, RotationScalar>& translate(const Vector2<Scalar>& trans) {
        translation = *this * trans;
        return *this;
    }

    /**Translate this pose by a translation vector
     *\param x x component of vector to translate with
     *\param y y component of vector to translate with
     *\return A reference to this pose after translation
     */
    Pose2<Scalar, RotationScalar>& translate(const double x, const double y) {
        translation = *this * Vector2<Scalar>(x, y);
        return *this;
    }

    /**Rotate this pose by a rotation
     *\param angle Angle to rotate.
     *\return A reference to this pose after rotation
     */
    Pose2<Scalar, RotationScalar>& rotate(const double angle) {
        rotation += angle;
        return *this;
    }

    /** Calculates the inverse transformation from the current pose
     * @return The inverse transformation pose.
     */
    Pose2<Scalar, RotationScalar> invert() const {
        const double& invRotation = -rotation;
        return Pose2<Scalar, RotationScalar>(invRotation,
                                             (Vector2<Scalar>() - translation).rotate(invRotation));
    }

    /** Converts from a coordinate frame relative to the origin Pose2<Scalar, RotationScalar> passed in,
     to the one that the origin Pose2<Scalar, RotationScalar> was defined in. */
    Pose2<Scalar, RotationScalar> relativeToGlobal(const Pose2<Scalar, RotationScalar> &old_origin) const {
        Pose2<Scalar, RotationScalar> retVal(*this);
        retVal.translation.rotate(old_origin.rotation);
        retVal.translation += old_origin.translation;
        retVal.rotation += old_origin.rotation;
        return retVal;
    }

    /** Converts from the coordinate frame the origin Pose2<Scalar, RotationScalar> is defined in,
     to one relative to it. */
    Pose2<Scalar, RotationScalar> globalToRelative(const Pose2<Scalar, RotationScalar> &new_origin) const {
        Pose2<Scalar, RotationScalar> retVal(*this);
        retVal.translation -= new_origin.translation;
        retVal.translation.rotate(-new_origin.rotation);
        retVal.rotation -= new_origin.rotation;
        return retVal;
    }

    /**
     * The function creates a random pose.
     * @param x The range for x-values of the pose.
     * @param y The range for y-values of the pose.
     * @param angle The range for the rotation of the pose.
     */
    static Pose2<Scalar, RotationScalar> random(const Range<double>& x, const Range<double>& y,
                                                const Range<double>& angle) { // angle should even work in wrap around case!
        return Pose2<Scalar, RotationScalar>(
                double(randomDouble() * (angle.max - angle.min) + angle.min),
                Vector2<Scalar>(
                        double(randomDouble() * (x.max - x.min) + x.min),
                        double(randomDouble() * (y.max - y.min) + y.min)));
    }

    double abs(){
        return translation.abs();
    }

};

using Pose2F = Pose2<float, float>;
}
//}


#endif //ITANDROIDS_LIB_POSE2_H
