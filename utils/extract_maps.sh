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

MAPNAMES=`grep -rh MAP ../openair/* | awk '{print $3}' | sort | uniq`

for name in $MAPNAMES
do

    AIRSPACE_FILES=`grep -rl "MAP $name " ../openair/*`
    
    OUTPUTFILE=../build/openair/$name.txt

    > $OUTPUTFILE
    for file in $AIRSPACE_FILES
    do
    
      SHOW_STATUS=`grep "MAP $name " $file | awk '{print $4}'`
    
      if [[ "$SHOW_STATUS" == 'YES' ]]; then
        echo -n "Adding $(basename $file) to $(basename $OUTPUTFILE) airspace file... "
        cat $file >> $OUTPUTFILE
        echo "done."
      elif [[ "$SHOW_STATUS" == 'SEE' ]]; then
        echo -n "Adding $(basename $file) to $(basename $OUTPUTFILE) airspace file (NOTAM version)... "
        sed 's/^AN /AN By NOTAM: /g' $file >> $OUTPUTFILE
        echo "done."
      fi
      echo -ne "\n\n" >> $OUTPUTFILE
    
    done
    
    # Generate Polish and GPX file for the total.
    ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/polish_format/$name.mp ${OA2PM_ROOTDIR}/build/openair/$name.txt
    ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/gpx/$name.gpx ${OA2PM_ROOTDIR}/build/openair/$name.txt

done

# Copy license
cp ../creative_commons_license.txt ${OA2PM_ROOTDIR}/build/
