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

#ifndef POLISHSTATE_H
#define POLISHSTATE_H

#include <vector>
#include <string>
#include "OutputState.h"
#include "Constants.h"
#include "Coordinate.h"


class PolishState : public OutputState
{

public:

    static PolishState* getInstance();

    virtual void writeHeader(std::ostream &out) const;
    virtual void writeFooter(std::ostream& ) const;

    //! Use this method to write out an airspace.
    virtual void write(std::ostream& stream, const Airspace& airspace) const;


protected:

    PolishState();

private:

    // Line types for the different airspaces, sorted alphabetically.
    static const std::string LINETYPE_ATZ;
    static const std::string LINETYPE_BY_AUP;
    static const std::string LINETYPE_BY_NOTAM;
    static const std::string LINETYPE_CTA;
    static const std::string LINETYPE_CTR;
    static const std::string LINETYPE_DANGER;
    static const std::string LINETYPE_DEFAULT;
    static const std::string LINETYPE_FIR;
    static const std::string LINETYPE_LOW_FLYING_AREA;
    static const std::string LINETYPE_LOW_FLYING_ROUTE;
    static const std::string LINETYPE_MAP_EDGE;
    static const std::string LINETYPE_PROHIBITED;
    static const std::string LINETYPE_RESTRICTED;
    static const std::string LINETYPE_TMA;
    static const std::string LINETYPE_TMZ;

    // Polygon types for the different airspaces, sorted alphabetically.
    static const std::string POLYGONTYPE_ATZ;
    static const std::string POLYGONTYPE_ATZ_CTR;
    static const std::string POLYGONTYPE_BY_AUP;
    static const std::string POLYGONTYPE_BY_NOTAM;
    static const std::string POLYGONTYPE_CTA;
    static const std::string POLYGONTYPE_CTR_ABOVE_GROUND;
    static const std::string POLYGONTYPE_CTR_FROM_GROUND;
    static const std::string POLYGONTYPE_DANGER;
    static const std::string POLYGONTYPE_DEFAULT;
    static const std::string POLYGONTYPE_LFA;
    static const std::string POLYGONTYPE_LFAG;
    static const std::string POLYGONTYPE_NON_LFAG_ABOVE_GROUND;
    static const std::string POLYGONTYPE_PROHIBITED;
    static const std::string POLYGONTYPE_RESTRICTED;
    static const std::string POLYGONTYPE_TMZ;

    static PolishState* _instance;

    //! Helper method to write out an airspace
    void write(std::ostream& stream, const CurvedPolygon& p) const;
    void write(std::ostream& stream, const std::vector<Coordinate>& coords) const;
    void write(std::ostream& out, const Coordinate& c) const;

    std::string getPolygonType(const Airspace& space) const;
    std::string getLineType(const Airspace& space) const;
    std::string getPolishLabel(const Airspace& space) const;
    bool needsPolygon(const Airspace& space) const;

};

#endif /* POLISHSTATE_H */
