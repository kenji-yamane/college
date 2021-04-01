/**
* @file Pose2D.h
        * Contains class Pose2D
*
* @author <a href="mailto:martin.kallnik@gmx.de">Martin Kallnik</a>
* @author Max Risler
*/

#ifndef __Pose2D_h__
#define __Pose2D_h__


#include "math/Pose2.h"

//namespace itandroids_lib {
namespace math {

/** representation for 2D Transformation and Position (Location + Orientation)*/
using Pose2D = Pose2<double, double>;

} /* namespace math */
//} /* namespace itandroids_lib */

#endif // __Pose2D_h__
