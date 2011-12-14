#!/bin/bash
#
# This script combines all individual Belgian OpenAir files into one Belgian
# OpenAir file.  It also creates a build directory and generates all individual
# GPX files inside that directory.  Next to that, it generates a Polish and GPX
# file for the whole of Belgium and Luxemburg.

unamestr=`uname -o`
if [[ "$unamestr" == 'Cygwin' ]]; then
  OACONVERT=oaconvert.exe
elif [[ "$unamestr" == 'Linux' || "$unamestr" == 'GNU/Linux' ]]; then
  OACONVERT=oaconvert
fi
  
OA2PM_ROOTDIR=~/Dropbox/MyProjects/oaconvert
AIRSPACES_DIR=${OA2PM_ROOTDIR}/openair
OUTPUTFILE=${OA2PM_ROOTDIR}/build/openair/belux.txt

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
  ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/gpx/$(basename $GPXFILE) $file
  echo "done."
done


# Generate Polish and GPX file for the whole of Belgium and Luxemburg.
${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/polish_format/belux.mp ${OA2PM_ROOTDIR}/build/openair/belux.txt
${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/gpx/belux.gpx ${OA2PM_ROOTDIR}/build/openair/belux.txt

# Copy license
cp ../creative_commons_license.txt ${OA2PM_ROOTDIR}/build/
