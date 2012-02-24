#!/bin/bash
#
# Check the individual OpenAir files to see what maps need to be created and
# then check what individual OpenAir files go into what maps.  For each map,
# the following filetypes are being generated:
#
#   build/openair/<MAPNAME>.txt		-> OpenAir
#   build/polish_format/<MAPNAME>.mp	-> Polish Format
#   build/gpx/<MAPNAME>.gpx		-> GPX


# Set the name of the oaconvert binary, depending wether we are on
# Cygwin or on Linux.
unamestr=`uname -o`
if [[ $unamestr =~ .*Cygwin.* ]]; then
  OACONVERT=oaconvert.exe
elif [[ $unamestr =~ .*Linux.* ]]; then
  OACONVERT=oaconvert
fi

OA2PM_ROOTDIR=..

# Create the different output build directories.
mkdir -p ${OA2PM_ROOTDIR}/build
mkdir -p ${OA2PM_ROOTDIR}/build/openair
mkdir -p ${OA2PM_ROOTDIR}/build/polish_format
mkdir -p ${OA2PM_ROOTDIR}/build/gpx
mkdir -p ${OA2PM_ROOTDIR}/build/kml

# Extract the different map names from all OpenAir files.
MAPNAMES=`grep -rh MAP ../openair/* | awk '{print $3}' | sort | uniq`

# Combine individual OpenAir files into their respecitve full OpenAir file.
# Also use the oaconvert tool to create full GPX and Polish files.
for name in $MAPNAMES
do

    # TODO: Apparently, if the grep command returns *a lot* of files,
    #       then the resulting final map files have problems displaying
    #       special characters (Like the è in Liège).  If the grep command
    #       returns fewer files, then there is no problem with special
    #       characters.  Find out why and fix this!
    AIRSPACE_FILES=`grep -rl "MAP $name " ../openair/*`      # SPECIAL CHARACTER PROBLEM
    #AIRSPACE_FILES=`grep -rl "Li.*ge " ../openair/belgium/*` # NO SPECIAL CHARACTER PROBLEM
    
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
    
    echo -n "Generating Polish file $name.mp... "
    ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/polish_format/$name.mp ${OA2PM_ROOTDIR}/build/openair/$name.txt
    echo "done."
    echo -n "Generating KML file $name.kml... "
    ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/kml/$name.kml ${OA2PM_ROOTDIR}/build/openair/$name.txt
    echo "done."
    echo -n "Generating GPX file $name.gpx... "
    ${OA2PM_ROOTDIR}/src/$OACONVERT -o ${OA2PM_ROOTDIR}/build/gpx/$name.gpx ${OA2PM_ROOTDIR}/build/openair/$name.txt
    echo "done."

done

echo -n "Copying license file to build directory... "
cp ../creative_commons_license.txt ${OA2PM_ROOTDIR}/build/
echo "done."
