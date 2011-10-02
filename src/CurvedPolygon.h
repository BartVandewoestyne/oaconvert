#ifndef CURVEDPOLYGON_H
#define CURVEDPOLYGON_H

#include <vector>
#include <ostream>

#include "Region.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////////////////////////////////////
class Arc;
class Coordinate;
class Segment;

//////////////////////////////////////////////////////////////////////////////////////////
// Class CurvedPolygon
//////////////////////////////////////////////////////////////////////////////////////////

class CurvedPolygon : public Region
  {
  public:
    CurvedPolygon();
    virtual ~CurvedPolygon();

    void addArc( const Arc& arc );
    void addLinearSegment( const Coordinate& point );

    //////////////////////////////////////////////////
    // Interface Region
    virtual std::ostream& print( std::ostream &stream );
    virtual void write( std::ostream& stream, const OutputState* outputstate ) const;

  private:
    // copy-constructor is private and not implemented (yet...)!!!
    CurvedPolygon( const CurvedPolygon& i_other );

  private:
    std::vector<Segment*> m_segments;

  };



#endif /* end of include guard: CURVEDPOLYGON_H */
