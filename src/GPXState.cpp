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

#include "GPXState.h"

#include <cassert>
#include <ctime>

#include "Airspace.h"
#include "Circle.h"
#include "Constants.h"
#include "CurvedPolygon.h"

using namespace std;
using namespace Constants;

GPXState* GPXState::_instance = 0;


GPXState::GPXState()
{
}


GPXState* GPXState::getInstance()
{
    if (_instance == 0)
    {
        _instance = new GPXState;
    }
    return _instance;
}


void GPXState::writeHeader(std::ostream &out) const
{
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    out << "<gpx" << endl;
    out << " version=\"1.1\"" << endl;
    out << " creator=\"oaconvert - https://github.com/BartVandewoestyne/oaconvert/\"" << endl;
    out << " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
    out << " xmlns=\"http://www.topografix.com/GPX/1/1\"" << endl;
    out << " xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">" << endl;
    out << "  <metadata>" << endl;
    //out << "    <name>Some Filename</name>" << endl; // TODO
    //out << "    <desc>Some Description</desc>" << endl; // TODO
    // TODO: find out how to add multiple authors
    out << "    <author>" << endl;
    out << "      <name>Bart Vandewoestyne</name>" << endl;
    out << "    </author>" << endl;
    out << "    <copyright author=\"Bart Vandewoestyne\"></copyright>" << endl; // TODO
    out << "    <link href=\"https://github.com/BartVandewoestyne/oaconvert/\">" << endl;
    out << "      <text>oaconvert homepage</text>" << endl;
    out << "    </link>" << endl;
    time_t now;
    time(&now);
    char mytime[sizeof "2011-10-08T07:07:09Z"];
    strftime(mytime, sizeof mytime, "%FT%TZ", gmtime(&now)); // ISO 8601 format.
    out << "    <time>" << mytime << "</time>" << endl;
    out << "    <keywords>airspace, AIP, OpenAir, oaconvert</keywords>" << endl;
    out << "  </metadata>" << endl;
}


void GPXState::writeFooter(std::ostream &out) const
{
    out << "</gpx>" << endl;
}


void GPXState::write(std::ostream& stream, const Airspace& airspace) const
{
    // Write as TRACK
    stream << "  <trk>" << endl;
    stream << "    <name>" << airspace.getName() << "</name>" << endl;
    //stream << "    <cmt>TODO: GPS comment for track</cmt>" << endl;
    //stream << "    <desc>TODO: User description of track</desc>" << endl;
    //stream << "    <src>TODO: Source of data</src>" << endl;
    //stream << "    <link>TODO: link to eAIP</link>" << endl;
    //stream << "    <number>TODO: number</number>" << endl;
    stream << "    <type>" << airspace.getClass() << "</type>" << endl;
    stream << "    <trkseg>" << endl;
    write(stream, airspace.getCurvedPolygon());
    stream << "    </trkseg>" << endl;
    stream << "  </trk>" << endl;

    // Write as ROUTE
    //stream << "  <rte>" << endl;
    //stream << "    <name>" << airspace.getName() << "</name>" << endl;
    //stream << "    <cmt>TODO: GPS comment for track</cmt>" << endl;
    //stream << "    <desc>TODO: User description of track</desc>" << endl;
    //stream << "    <src>TODO: Source of data</src>" << endl;
    //stream << "    <link>TODO: link to eAIP</link>" << endl;
    //stream << "    <number>TODO: number</number>" << endl;
    //stream << "    <type>" << airspace.getClass() << "</type>" << endl;
    //write(stream, airspace.getCurvedPolygon());
    //stream << "  </rte>" << endl;

}


void GPXState::write(std::ostream& stream, const CurvedPolygon& p) const
{
    std::vector<Coordinate> coords;
    p.discretize( coords, RESOLUTION );
    write( stream, coords );
}


void GPXState::write(std::ostream& out, const std::vector<Coordinate>& coords) const
{
    std::vector<Coordinate>::const_iterator it;
    for ( it = coords.begin(); it < coords.end(); ++it )
    {
      write(out, *it);
      out << endl;
    }
}


void GPXState::write(ostream& out, const Coordinate& c) const
{
    // Write as TRACKPOINT in a TRACK
    out << "      <trkpt lat=\"" << c.getLatitude().getAngle() << "\" lon=\"" << c.getLongitude().getAngle() << "\"></trkpt>";

    // Write as ROUTEPOINT in a ROUTE
    //out << "      <rtept lat=\"" << c.getLatitude().getAngle() << "\" lon=\"" << c.getLongitude().getAngle() << "\"></rtept>";

    // TODO: include elevation
}
