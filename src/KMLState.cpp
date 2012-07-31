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
    const string gray      = "82c0c0c0";
    const string orange    = "820066ff";
    const string red       = "820000ff";
    const string green     = "8200ff00";
    const string blue      = "82ff0000";
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

    if ( needs3DZone(airspace) )
    {
        std::vector<Coordinate> coords;
        airspace.getCurvedPolygon().discretize( coords, RESOLUTION );

        if (coords.size() > 0)
        {

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

          writeTopBottomPolygon(stream, airspace, coords, airspace.getCeiling());
          writeTopBottomPolygon(stream, airspace, coords, airspace.getFloor());
          writeSidePolygons(stream, airspace, coords);

          stream << "    </MultiGeometry>" << endl;
          stream << "  </Placemark>\n" << endl;

       }
    } /* end if-test needs3DZone() */

    if ( needs2DLine(airspace) )
    {
      // TODO
    }

    if ( needs3DLine(airspace) )
    {
      // TODO
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


/**
 * Return true if this airspace needs to be represented by a 3D zone
 * in the output KML file.
 */
bool KMLState::needs3DZone(const Airspace&) const
{
  // Currently, all airspaces are shown as 3D zones, including FIR's.
  return true;
}


/**
 * Return true if this airspace needs to be represented by a 2D polyline
 * in the output KML file.
 */
bool KMLState::needs2DLine(const Airspace& airspace) const
{
  return airspace.isFIR();
}


/**
 * Return true if this airspace needs to be represented by a (possibly
 * non-closed) 3D 'polyline' in the output KML.  Examples are military
 * Low Flying Routes.
 */
bool KMLState::needs3DLine(const Airspace& airspace) const
{
  return airspace.isLowFlyingRoute();
}


/*
 * Draw the top or bottom polygon for the 3D zone.
 */
void KMLState::writeTopBottomPolygon(std::ostream &out, const Airspace& airspace, const std::vector<Coordinate>& coords, double altitude) const
{
    out << "    <Polygon>" << endl;
    if ( airspace.hasAbsoluteCeiling() ) {
      out << "      <altitudeMode>absolute</altitudeMode>" << endl;
    } else {
      out << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
    }
    out << "      <outerBoundaryIs>" << endl;
    out << "        <LinearRing>" << endl;
    out << "          <coordinates>" << endl;
    
    write( out, coords, altitude);
    
    out << "          </coordinates>" << endl;
    out << "        </LinearRing>" << endl;
    out << "      </outerBoundaryIs>" << endl;
    out << "    </Polygon>" << endl;
}


/*
 * Draw the sides of the 3D zone: loop over all coordinates and draw a 'side-rectangle' for each coordinate.
 */
void KMLState::writeSidePolygons(std::ostream &out, const Airspace& airspace, const std::vector<Coordinate>& coords) const
{
    for (size_t i = 0; i < coords.size(); ++i)
    {
        out << "    <Polygon>" << endl;
        if (airspace.hasAbsoluteCeiling() || airspace.hasAbsoluteFloor()) {
          out << "      <altitudeMode>absolute</altitudeMode>" << endl;
        } else {
          out << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
        }
        out << "      <outerBoundaryIs>" << endl;
        out << "        <LinearRing>" << endl;
        out << "          <coordinates>" << endl;
    
        /* Draw the 'side-rectangle' (4 points) */
        out << "          ";
        write(out, coords[i], airspace.getFloor());
        out << endl;
        out << "          ";
        write(out, coords[(i+1)%coords.size()], airspace.getFloor());
        out << endl;
        out << "          ";
        write(out , coords[(i+1)%coords.size()], airspace.getCeiling());
        out << endl;
        out << "          ";
        write(out, coords[i], airspace.getCeiling());
        out << endl;
        // One extra point, because the KML-requirement that the
        // last point must be identical to the first one to form a closed figure.
        out << "          ";
        write(out, coords[i], airspace.getFloor());
        out << endl;
    
        out << "          </coordinates>" << endl;
        out << "        </LinearRing>" << endl;
        out << "      </outerBoundaryIs>" << endl;
        out << "    </Polygon>" << endl;
    }
}
