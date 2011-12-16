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
    out << "<gpx version=\"1.1\" creator=\"oaconvert\">" << endl;
    out << "  <metadata>" << endl;
    out << "    <name>Some Filename</name>" << endl; // TODO
    out << "    <desc>Some Description</desc>" << endl; // TODO
    out << "    <author>Bart Vandewoestyne, Yves Frederix</author>" << endl;
    out << "    <copyright>Some Copyright</copyright>" << endl; // TODO
    out << "    <link>https://github.com/BartVandewoestyne/oaconvert/</link>" << endl;
    out << "    <time></time>" << endl; // TODO
    out << "    <keywords>airspace, AIP, oaconvert</keywords>" << endl; // TODO
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
    stream << "    <cmt>TODO: GPS comment for track</cmt>" << endl;
    stream << "    <desc>TODO: User description of track</desc>" << endl;
    stream << "    <src>TODO: Source of data</src>" << endl;
    stream << "    <link>TODO: link to eAIP</link>" << endl;
    stream << "    <number>TODO: number</number>" << endl;
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
    if (coords.size() > 0)
    {
        for (size_t i = 0; i < coords.size(); ++i)
        {
            write(out, coords[i]);
            out << endl;
        }
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
