#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

namespace Constants
{
  const double pi = 4 * std::atan(1.0);
  const int NBPOINTS = 100;

  /* Resolution in Nautical Miles */
  /* For circles and arcs, each nautical mile ( = each 1852 m) we put a point */
  const double RESOLUTION = 1;
}

#endif /* ONSTANTS_H */
