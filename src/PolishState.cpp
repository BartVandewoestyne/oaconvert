/*
  Copyright 2011 Bart Vandewoestyne, Yves Frederix.
  
  This file is part of oaconvert.
  
  oaconvert is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  oaconvert is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with oaconvert.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "PolishState.h"

#include <cassert>

#include "Airspace.h"
#include "Circle.h"
#include "CurvedPolygon.h"

using namespace std;
using namespace Constants;

PolishState* PolishState::_instance = 0;

PolishState::PolishState()
  {
  }

PolishState* PolishState::getInstance()
  {
  if (_instance == 0)
    {
    _instance = new PolishState;
    }
  return _instance;
  }

void PolishState::writeHeader(std::ostream &out) const
  {

  out << "; Generated by oa2pm (OpenAir to Polish Format converter)\n";

  // Section identifier (mandatory).
  out << "[IMG ID]" << endl;

  // Unique identifier (up to 8 decimal digits) for the map (mandatory).  May
  // be only written in a decimal format.  The cgpsmapper manual gives has as
  // an example an ID=11000204 so that is the one we use.  In the oa2pm source
  // code, the value 42200100 is used.
  out << "ID=11000204" << endl;

  // Map name to be displayed in the GPS receiver's Map Info menu (mandatory).
  out << "Name=My Very Special Map" << endl;

  // Instead of single byte coding, use full-byte (8-bit) character coding
  // with the specified codepage (depending on the GPS firmware) (optional).
  // We use the default of 0 here, but the oa2gm source code has a value
  // of 1250, probably because the author needed it (see for example
  // http://en.wikipedia.org/wiki/Windows-1250 ).
  out << "Codepage=0" << endl;

  // Only index objects if POI index info is explicitly provided.  With
  // 'indexing', we mean 'make searcheable by the Find function in the GPS'.
  // We follow the default value  of 'N' here.
  out << "POIIndex=N" << endl;

  // Maximum allowed region size.  A higher value increases the allowable
  // region size, but may decrease the map performance; a lower value may
  // increase the map size.
  // Suggested values:
  //   topo maps: 1000-2000
  //   city (dense streets): 2000-5000
  //   countryside: 6000-10000
  out << "TreSize=1311" << endl;

  // Maximal number of elements in one region (mandatory).
  // Can be any value between ~50 and 1024 (values less than 50 don't make
  // sense).  Recent experiments show that this parameter does not impact
  // map performance and can be set to maximum allowed value: 1024.
  // Suggested value: 1024
  out << "RgnLimit=1024" << endl;

  // Kind of pre-processing.  We're setting it to the default here...
  out << "PreProcess=F" << endl;


  // This is what oa2gm uses, but it didn't work with GPSMapEdit 1.0.70.0.
  //out << "Levels=5\n";
  //out << "Level0=21\n";
  //out << "Level1=19\n";
  //out << "Level2=17\n";
  //out << "Level3=15\n";
  //out << "Level4=14\n";
  //out << "Zoom0=0\n";
  //out << "Zoom1=1\n";
  //out << "Zoom2=2\n";
  //out << "Zoom3=3\n";
  //out << "Zoom4=4\n";

  // This is from http://vjet.f2s.com/gmap/cgpsmapper.html
  out << "Levels=5\n";
  out << "Level0=24\n";
  out << "Level1=22\n";
  out << "Level2=20\n";
  out << "Level3=19\n";
  out << "Level4=18\n";
  out << "Zoom0=0\n";
  out << "Zoom1=1\n";
  out << "Zoom2=2\n";
  out << "Zoom3=3\n";
  out << "Zoom4=4\n";

  //// Below is what GPSMapEdit 1.0.69.1 outputs, and it seems to work in
  //// GPSMapEdit... so we use this.  Note that this might not work as fluently
  //// on actual GPS units like the Garmin 60CSX.

  //// Note 1: the last layer must always be empty, e.g. Levels=3
  ////         means that two layers only are available for map objects.
  //// Note 2: GPS unit map detail must be set to 'Normal'!!!!!
  //// See section 4.4 (on page 40) of cgpsmapper manual (mandatory).

  //// Number of map zoom levels (layers) in the map (mandatory, at least 2,
  //// not more than 10, numbered starting at 0).
  //cout << "Levels=2\n";

  //// Map zoom level 0 corresponds to hardware zoom level 24 ('Up to 120m')
  //// This means that map objects and coordinates defined as map level 0, will
  //// be used at hardware zoom levels 24 and above.  So they will be visible
  //// if the scale is 120m or more detailed.
  //cout << "Level0=24\n";

  //// Last level is a special one that dictates when our map replaces the
  //// base map.  It means the following: from hardware level
  //// 14 ('80km to 120 km') or higher, we will see our map.  At hardware
  //// zoom levels 13 and below, we will see the base map.
  //// We are not allowed to define map objects and coordinates at this level.
  //cout << "Level1=14\n";

  //cout << "Zoom0=0\n";
  //cout << "Zoom1=1\n";


  // Section terminator (mandatory)
  out << "[END-IMG ID]\n" << endl;

}


void PolishState::writeFooter(std::ostream &out) const
  {
  // TODO
  }


// void PolishState::write(ostream& out, const Airspace& s) const
// {
//   /* TODO
//   if ( s.hasPolygon() )
//   {
//     //cout << "DEBUG: Airspace has a polygon" << endl;
//     write(out, s.getPolygon(), s.getName());
//   }
//   if ( s.hasCircle() )
//   {
//     //cout << "DEBUG: Airspace has a circle" << endl;
//     write(out, s.getCircle().toPolygon(100), s.getName());;
//   }
//   */
// }

void PolishState::write(std::ostream& stream, const Airspace& airspace) const
  {
  if( ! airspace.getRegion() )
    {
    std::cout << " WARNING: Not printing airspace with empty region." << std::endl;
    return;
    }

  // See section 4.2.4.2 in http://cgpsmapper.com/download/cGPSmapper-UsrMan-v02.1.pdf

  // oa2gm used [RGN40] here, which is a [POLYLINE]... I think one could also
  // use [RGN80] here, which is a [POLYGON].
  stream << "[POLYLINE]" << endl;
  // Type of [POLYGON] element: 'Airport'
  // We should probably change this to something which is more appropriate
  // for each earspace separately.
  // See section 12.3.3 in the cgpsmapper manual.
  // Note that oa2gm used Type=0x0a which is an 'Unpaved Road-thin', but this
  // is for [POLYLINE], not [POLYGON]...
  stream << "Type=" << getType(airspace.getClass()) << endl;

  stream << "Label=" << airspace.getName() << endl;
  stream << "EndLevel=4" << endl; // Number must not be higher than highest X in LevelX in header.
  OutputState::write(stream, airspace.getRegion());
  }


void PolishState::write(std::ostream& stream, const Circle* circle) const
  {
  cout << "PolishState::write(Circle)" << endl;
  std::vector<Coordinate> coords;
  // TODO: check what resolution to use!
  circle->discretize( coords, 1 );
  write( stream, coords );
//    write(s.getCircle().toPolygon(NBPOINTS), s.getName());;
//  assert( ! "TODO" );
  }


void PolishState::write(std::ostream& stream, const CurvedPolygon* curved_polygon) const
  {
  cout << "PolishState::write(CurvedPolygon)" << endl;
  std::vector<Coordinate> coords;
  // TODO: check what resolution to use!
  curved_polygon->discretize( coords, 1 );
  write( stream, coords );
//  assert( ! "TODO" );
  }


void PolishState::write(ostream& out, const Coordinate& c) const
{
  out << "(" << c.getLatitude().getAngle() << "," << c.getLongitude().getAngle() << ")";
}


void PolishState::write(std::ostream& out, const std::vector<Coordinate>& coords) const
{
  if (coords.size() > 0)
  {
    out << "Data0=";
    for (size_t i = 0; i < coords.size()-1; ++i)
    {
      write(out, coords[i]);
      out << ",";
    }
    write(out, coords.back());
    out << endl;
  }
  out << "[END]\n" << endl;
}

/*
 * Return the Polish File [POLYGON] type for the given airspace class.
 * For the listing of the different possible types, see cgpsmapper manual, table 9.3.3 page 89.
 */
std::string PolishState::getType(const std::string& airspaceClass) const
{
  if (airspaceClass == "R")
  {
    // Restricted area.
    return string("0x0702");
    // Restriction area/line (invisible)
    //return string("0x0500");
  }
  else if (airspaceClass == "Q")
  {
    // Danger line (invisible).
    return string("0x0409");
  }
  else if (airspaceClass == "P")
  {
    // Prohibited area (invisible).
    return string("0x0503");
  }
  else if (airspaceClass == "CTR")
  {
    // Airport.
    return string("0x07");
  }
  else
  {
    // Defaults used by oa2gm:

    // University.
    return string("0x0a");
    // Golf.
    //return string("0x18");
  }
}
