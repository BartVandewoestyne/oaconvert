#!/bin/bash
#

unamestr=`uname -o`
if [[ "$unamestr" == 'Cygwin' ]]; then
  OACONVERT=oaconvert.exe
elif [[ "$unamestr" == 'Linux' || "$unamestr" == 'GNU/Linux' ]]; then
  OACONVERT=oaconvert
fi

OA2PM_ROOTDIR=..

mkdir -p ${OA2PM_ROOTDIR}/build
mkdir -p ${OA2PM_ROOTDIR}/build/openair
mkdir -p ${OA2PM_ROOTDIR}/build/polish_format
mkdir -p ${OA2PM_ROOTDIR}/build/gpx
mkdir -p ${OA2PM_ROOTDIR}/build/kml


BELUX_WEEK="../build/openair/belux_week.txt"


FILES_WEEK=`grep -l "MAP WEEK " ../openair/belgium/*`

> $BELUX_WEEK
for file in $FILES_WEEK
do

  COMMAND=`grep "MAP WEEK " $file | awk '{print $4}'`

  if [[ "$COMMAND" == 'YES' ]]; then
    echo -n "Adding $(basename $file) to $BELUX_WEEK airspace file... "
    cat $file >> $BELUX_WEEK
    echo "done."
  elif [[ "$COMMAND" == 'SEE' ]]; then
    echo -n "Adding $(basename $file) to $BELUX_WEEK airspace file (NOTAM version)... "
    sed 's/^AN /AN By NOTAM: /g' $file >> $BELUX_WEEK
    echo "done."
  fi
  echo -ne "\n\n" >> $BELUX_WEEK

done


# Generate Polish and GPX file for the whole of Belgium and Luxemburg.
${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/polish_format/belux_week.mp ${OA2PM_ROOTDIR}/build/openair/belux_week.txt
${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/gpx/belux_week.gpx ${OA2PM_ROOTDIR}/build/openair/belux_week.txt

# Copy license
cp ../creative_commons_license.txt ${OA2PM_ROOTDIR}/build/
