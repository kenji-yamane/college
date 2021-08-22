//
// Created by mmaximo on 3/24/18.
//

#include "MathUtils.h"
#include <cmath>

namespace math {

double MathUtils::normalizeAngle(double angle) {
    while (angle >= M_PI)
        angle -= 2.0 * M_PI;
    while (angle < -M_PI)
        angle += 2.0 * M_PI;
    return angle;
}

}