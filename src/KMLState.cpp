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

#include "KMLState.h"

#include <cassert>
#include <cmath>
#include <string>

#include "Airspace.h"
#include "Circle.h"
#include "Constants.h"
#include "CurvedPolygon.h"

using namespace std;
using namespace Constants;

KMLState* KMLState::_instance = 0;


KMLState::KMLState()
{
}


KMLState* KMLState::getInstance()
{
    if (_instance == 0)
    {
        _instance = new KMLState;
    }
    return _instance;
}


void KMLState::writeHeader(std::ostream &out) const
{

    // Colors are specified as aabbggrr where
    //
    //   aa = alpha (transparency)
    //   bb = blue
    //   gg = green
    //   rr = red
    //
    // See also https://developers.google.com/kml/documentation/kmlreference#colorstyle
    const string gray   = "82c0c0c0";
    const string orange = "820066ff";
    const string red    = "820000ff";
    const string green  = "8200ff00";
    const string blue   = "82ff0000";
    const string darkblue  = "828b0000";
    const string lightblue = "82e6d8ad";

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    out << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << endl;
    out << "<Document>" << endl;

    out << endl;

    writeStyle(out, "ctr", red);
    writeStyle(out, "prohibited", red);

    writeStyle(out, "cta", orange);
    writeStyle(out, "atz", orange);
    writeStyle(out, "tma", orange);
    writeStyle(out, "restricted", orange);

    writeStyle(out, "lfag", green);
    writeStyle(out, "danger", green);

    writeStyle(out, "bynotam", darkblue);
    writeStyle(out, "byaup", lightblue);

    writeStyle(out, "default", gray);

    out << endl;

}


void KMLState::writeFooter(std::ostream &out) const
{
    out << "</Document>" << endl;
    out << "</kml>" << endl;
}


void KMLState::write(std::ostream& stream, const Airspace& airspace) const
{

    if ( !( airspace.isFIR() || airspace.isMapEdge() ) )
    {
        std::vector<Coordinate> coords;
        airspace.getCurvedPolygon().discretize( coords, RESOLUTION );

        if (coords.size() > 0)
        {

          /* polygon representing ceiling */
          stream << "  <Placemark>" << endl;
          stream << "    <name>";
          stream << getPlacemarkName(airspace);
          stream << "</name>" << endl;
          stream << "    <description>" << endl;
          stream << "Ceiling: " << airspace.getCeilingString() << " (" << ceil(airspace.getCeiling()) << " m)" << endl;
          stream << "Floor  : " << airspace.getFloorString() << " (" << floor(airspace.getFloor()) << " m)" << endl;
          stream << "    </description>" << endl;
          stream << "    <styleUrl>" << getPolygonType(airspace) << "</styleUrl>" << endl;
          stream << "  <MultiGeometry>" << endl;

          /* polygon representing ceiling */
          stream << "    <Polygon>" << endl;
          if ( airspace.hasAbsoluteCeiling() ) {
            stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
          } else {
            stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
          }
          stream << "      <outerBoundaryIs>" << endl;
          stream << "        <LinearRing>" << endl;
          stream << "          <coordinates>" << endl;

          write( stream, coords, airspace.getCeiling());

          stream << "          </coordinates>" << endl;
          stream << "        </LinearRing>" << endl;
          stream << "      </outerBoundaryIs>" << endl;
          stream << "    </Polygon>" << endl;

          /* polygon representing floor */
          stream << "    <Polygon>" << endl;
          if ( airspace.hasAbsoluteCeiling() ) {
            stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
          } else {
            stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
          }
          stream << "      <outerBoundaryIs>" << endl;
          stream << "        <LinearRing>" << endl;
          stream << "          <coordinates>" << endl;

          write( stream, coords, airspace.getFloor());

          stream << "          </coordinates>" << endl;
          stream << "        </LinearRing>" << endl;
          stream << "      </outerBoundaryIs>" << endl;
          stream << "    </Polygon>" << endl;

          /* Polygon borders: loop over all coordinates and draw a 'side-rectangle' for each coordinate. */

          for (size_t i = 0; i < coords.size(); ++i)
          {
              stream << "    <Polygon>" << endl;
              if (airspace.hasAbsoluteCeiling() || airspace.hasAbsoluteFloor()) {
                stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
              } else {
                stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
              }
              stream << "      <outerBoundaryIs>" << endl;
              stream << "        <LinearRing>" << endl;
              stream << "          <coordinates>" << endl;

              /* Draw the 'side-rectangle' (4 points) */
              stream << "          ";
              write(stream, coords[i], airspace.getFloor());
              stream << endl;
              stream << "          ";
              write(stream, coords[(i+1)%coords.size()], airspace.getFloor());
              stream << endl;
              stream << "          ";
              write(stream, coords[(i+1)%coords.size()], airspace.getCeiling());
              stream << endl;
              stream << "          ";
              write(stream, coords[i], airspace.getCeiling());
              stream << endl;
              // One extra point, because the KML-requirement that the
              // last point must be identical to the first one to form a closed figure.
              stream << "          ";
              write(stream, coords[i], airspace.getFloor());
              stream << endl;

              stream << "          </coordinates>" << endl;
              stream << "        </LinearRing>" << endl;
              stream << "      </outerBoundaryIs>" << endl;
              stream << "    </Polygon>" << endl;
          }

          stream << "    </MultiGeometry>" << endl;
          stream << "  </Placemark>\n" << endl;

       }
    }
}


void KMLState::write(std::ostream& out, const std::vector<Coordinate>& coords, double altitude) const
{
    if (coords.size() > 0)
    {
        for (size_t i = 0; i < coords.size(); ++i)
        {
            out << "          ";
            write(out, coords[i], altitude);
            out << endl;
        }
    }
}


void KMLState::write(ostream& out, const Coordinate& c, double altitude) const
{
    out << c.getLongitude().getAngle() << "," << c.getLatitude().getAngle() << "," << altitude;
}


/*
 * Return the KML File Polygon type for the given airspace class.
 */
std::string KMLState::getPolygonType(const Airspace& space) const {

    // A lot of zones are BY NOTAM.  If they are, they should be colored with
    // the BY NOTAM color, not with the color for their type.  Therefore, the
    // isByNOTAM() check needs to come first!

    if (space.isByNOTAM()) {
        return (string("#bynotam"));
    } else if (space.isByAUP()) {
        return (string("#byaup"));
    } else if (space.isATZ()) {
        if (space.getClass() == "CTR") {
          return string("#ctr");
        } else {
          return string("#atz");
        }
    } else if (space.isCTR()) {
        return string("#ctr");
    } else if (space.isCTA()) {
        return string("#cta");
    } else if (space.isTMA()) {
        return string("#tma");
    } else if (space.isLowFlyingAreaGolf()) {
        return string("#lfag");
    } else if (space.isRestricted()) {
        return string("#restricted");
    } else if (space.isProhibited()) {
        return string("#prohibited");
    } else if (space.isDanger()) {
        return string("#danger");
    } else {
        return string("#default");
    }

}


std::string KMLState::getLineType(const Airspace& space) const
{

  // A lot of zones are BY NOTAM.  If they are, they should be colored with the
  // BY NOTAM color, not with the color of their type.  Therefore, the
  // isByNOTAM() check needs to come first!

  if (space.isByNOTAM()) {
      return string("#bynotam");
  } else if (space.isByAUP()) {
      return string("#byaup");
  } else if (space.isFIR()) {
      return string("#fir");
  } else if (space.isMapEdge()) {
      return string("#mapEdge");
  } else if (space.isDanger()) {
      return string("#danger");
  } else if (space.isRestricted()) {
      return string("#restricted");
  } else {
      return string("#default");
  }

}


/**
 * Return a KML Placemark name for this airspace.  For now, we just use
 * The name of the airspace... we can add more info later.
 */
std::string KMLState::getPlacemarkName(const Airspace& airspace) const
{   
    string pName;

    pName.append( airspace.getName() );

    return pName;

}


void KMLState::writeStyle(std::ostream &out, std::string id, std::string color) const
{
    out << "  <Style id=\"" + id + "\">" << endl;
    out << "      <LineStyle>" << endl;
    out << "          <color>" + color + "</color>" << endl;
    out << "      </LineStyle>" << endl;
    out << "      <PolyStyle>" << endl;
    out << "          <color>" + color + "</color>" << endl;
    out << "      </PolyStyle>" << endl;
    out << "  </Style>" << endl;
}
