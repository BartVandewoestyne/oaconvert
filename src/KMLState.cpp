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

    const string gray   = "82c0c0c0";
    const string orange = "820066ff";
    const string red    = "820000ff";
    const string green  = "8200ff00";
    const string blue   = "82ff0000";

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    out << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << endl;
    out << "<Document>" << endl;

    out << endl;

    writeStyle(out, "ctr", red);
    writeStyle(out, "prohibited", red);

    writeStyle(out, "cta", orange);
    writeStyle(out, "tma", orange);
    writeStyle(out, "restricted", orange);

    writeStyle(out, "lfag", green);
    writeStyle(out, "danger", green);

    writeStyle(out, "bynotam", blue);

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
          stream << "    <styleUrl>" << getPolygonType(airspace) << "</styleUrl>" << endl;
          stream << "    <name>";
          stream << airspace.get2DLabel();
          stream << "</name>" << endl;
          stream << "  <MultiGeometry>" << endl;

          stream << "    <Polygon>" << endl;
          if ( airspace.hasAGLCeiling() || airspace.hasSFCCeiling() ) {
            stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
          } else {
            stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
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
          if ( airspace.hasAGLFloor() || airspace.hasSFCFloor() || airspace.hasGNDFloor() ) {
            stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
          } else {
            stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
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
              if ( airspace.hasAGLFloor() || airspace.hasSFCFloor() ) { // TODO: what if floor and ceiling have different altitude convention (absolute/relativeToGround)?
                stream << "      <altitudeMode>relativeToGround</altitudeMode>" << endl;
              } else {
                stream << "      <altitudeMode>absolute</altitudeMode>" << endl;
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
 * Return the KML File [POLYGON] type for the given airspace class.
 * For the listing of the different possible types, see cgpsmapper manual,
 * table 9.3.3 page 89.
 *
 * Note: The Python script at
 *
 *   http://www.penguin.cz/~ondrap/paragliding.php
 *
 * sets the polygon type according to the following rules:
 *
 *      if AH - AL < 500 and AL < 2000:
 *          type = '78'
 *      elif AL == 0:
 *          type = '0x08'
 *      elif AL < 500:
 *          type = '0x1e'
 *      elif AL < 1000:
 *          type = '0x3c'
 *      elif AL < 1900:
 *          type = '0x18'
 *      else:
 *          type = '0x53'
 *
 */
std::string KMLState::getPolygonType(const Airspace& space) const
{
    if (space.isCTR()) {
        return string("#ctr");
    } else if (space.isCTA()) {
        return string("#cta");
    } else if (space.isTMA()) {
        return string("#tma");
    } else if ( space.isFloating() && !space.isLowFlyingAreaGolf() ) {
        return string("#default");
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
  if (space.isFIR()) {
      return string("#fir");
  } else if (space.isDanger()) {
      return string("#danger");
  } else if (space.isRestricted()) {
      return string("#restricted");
  } else if (space.isByNOTAM()) {
      return string("#bynotam");
  } else if (space.isMapEdge()) {
      return string("#mapEdge");
  } else {
      return string("#default");
  }
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
