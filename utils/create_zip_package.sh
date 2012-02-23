#!/bin/bash

datestring=`date +%Y-%m-%d-%H-%M-%S`
filename="BartsFantasticAirspaceMaps-${datestring}.zip"

# TODO: can we do this cleaner without the copy?  The point is not to have
#       the build directory inside the zip-file structure...
mkdir -p airspace_maps
cp -r ../build/creative_commons_license.txt \
      ../build/garmin \
      ../build/gpx \
      ../build/kml \
      ../build/openair \
      ../build/polish_format airspace_maps/

zip -r $filename airspace_maps

mv $filename ../build/
rm -rf airspace_maps/
