#!/bin/bash
#
# This script combines all individual Belgian OpenAir files into one Belgian
# OpenAir file.

OA2PM_ROOTDIR=~/Dropbox/MyProjects/oaconvert
AIRSPACES_DIR=${OA2PM_ROOTDIR}/openair
OUTPUTFILE=${OA2PM_ROOTDIR}/build/openair/brussels_fir.txt

AIRSPACES="${AIRSPACES_DIR}/belgium/*fir*.txt
           ${AIRSPACES_DIR}/belgium/*ctr*.txt
           ${AIRSPACES_DIR}/belgium/*cta*.txt
           ${AIRSPACES_DIR}/belgium/*tma*.txt
           ${AIRSPACES_DIR}/belgium/*vectoring*.txt
           ${AIRSPACES_DIR}/belgium/*prohibited*.txt
           ${AIRSPACES_DIR}/belgium/*restricted*.txt
           ${AIRSPACES_DIR}/belgium/*danger*.txt
           ${AIRSPACES_DIR}/belgium/low_flying_area*.txt
           ${AIRSPACES_DIR}/luxembourg/*tma*.txt"

mkdir -p ${OA2PM_ROOTDIR}/build
mkdir -p ${OA2PM_ROOTDIR}/build/openair
mkdir -p ${OA2PM_ROOTDIR}/build/polish_format
mkdir -p ${OA2PM_ROOTDIR}/build/gpx
mkdir -p ${OA2PM_ROOTDIR}/build/kml

# Generate OpenAir file for all airspaces.
> $OUTPUTFILE
for file in $AIRSPACES
do
  echo -n "Adding $(basename $file) to total airspace file... "
  cat $file >> $OUTPUTFILE
  echo -ne "\n\n" >> $OUTPUTFILE
  echo "done."
done


# Generate a GPX file for each airspace.
for file in $AIRSPACES
do
  echo -n "Generating GPX for $(basename $file)... "
  GPXFILE=${file%.txt}.gpx
  ${OA2PM_ROOTDIR}/src/oaconvert -o ${OA2PM_ROOTDIR}/build/gpx/$(basename $GPXFILE) $file
  echo "done."
done


# Generate Polish and GPX file for the whole of Belgium.
${OA2PM_ROOTDIR}/src/oaconvert -o ${OA2PM_ROOTDIR}/build/polish_format/brussels_fir.mp ${OA2PM_ROOTDIR}/build/openair/brussels_fir.txt
${OA2PM_ROOTDIR}/src/oaconvert -o ${OA2PM_ROOTDIR}/build/gpx/brussels_fir.gpx ${OA2PM_ROOTDIR}/build/openair/brussels_fir.txt

# Copy license
cp ../creative_commons_license.txt ${OA2PM_ROOTDIR}/build/
