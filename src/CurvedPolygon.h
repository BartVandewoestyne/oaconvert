#ifndef CURVEDPOLYGON_H
#define CURVEDPOLYGON_H

#include <vector>
#include <ostream>

#include "Region.h"

class Arc;
class Coordinate;
class Segment;

class CurvedPolygon : public Region
  {
  public:
    CurvedPolygon();
    virtual ~CurvedPolygon();

    void addArc( const Arc& arc );
    // TODO (question Bart): shouldn't we jusd change addLinearSegment to addPoint because
    //      a CurvedPolygon in essence is a set of arcs and points (connected by line segments)???
    void addLinearSegment( const Coordinate& point );

    //////////////////////////////////////////////////
    // Interface Region
    //! @copydoc Region::write
    virtual void write( std::ostream& stream, const OutputState* outputstate ) const;

    //! @copydoc Region::discretize
    virtual void discretize( std::vector<Coordinate>& coords, double resolution ) const;

    //! @copydoc Region::print
    virtual std::ostream& print( std::ostream &stream );

  private:
    // copy-constructor is private and not implemented (yet...)!!!
    CurvedPolygon( const CurvedPolygon& i_other );

  private:
    std::vector<Segment*> m_segments;

  };



#endif /* end of include guard: CURVEDPOLYGON_H */
