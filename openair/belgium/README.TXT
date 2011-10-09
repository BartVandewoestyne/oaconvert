Please always duplicate the begin and end point of an arc.  This way of
specifying the DA and DB records helps us visually checking the implementation.

For example:


DB-records
----------
If the AIP specifies something like:

  <coordinate1> - an arc of circle, 5 NM radius, centred on <coordinateX> and
  traced clockwise to <coordinate2>

then this should be translated into

  ...
  <coordinate1>
  V D=+
  V X=<coordinateX>
  * Radius: 5 NM
  DB <coordinate1>,<coordinate2>
  <coordinate2>
  ...


DA-records
----------
If the AIP specifies something like:

  TODO (haven't seen arcs with angles yet in the Belgian AIP...)

then this should be translated into

  ...
  <coordinate1>
  V D=+
  V X=<coordinateX>
  DA 5,120,340
  <coordinate2>


Also, make sure that the first point of your airspace is the same as the last
point of your airspace.  This will make sure that if certain software uses
polylines instead of polygons to represent airspaces, they will be visualized
as a closed region.


Note 1
------
In the AIP, the published geographical coordinates indicating LAT and LONG are
expressed in terms of the World Geodetic System of 1984 (WGS-84) geodetic
reference datum
-> See Part 1 GENERAL (GEN)
     GEN 2 TABLES AND CODES
       GEN 2.1  Measuring system, aircraft markings, holidays
         3 GEODETIC REFERENCE DATUM
