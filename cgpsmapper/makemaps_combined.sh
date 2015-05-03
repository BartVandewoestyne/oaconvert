#!/bin/bash
#
# TODO: THIS IS NOT WORKING AS IT SHOULD YET!!!  IT NEEDS FIXING!!!  THE MAIN
#       SCRIPT FOR CREATING THE GARMIN MAPS IS create_garmin_maps.sh
#
# Generate the Garmin maps from the files in the build/polish_format/ directory
# and combine them into one product.  Once this script is finished, a
# new build/garmin/ directory is created with the following files:
#
#     <ID_1>.img
#       ...
#     <ID_N>.img
#     <BARTSMAP>.img
#     <BARTSMAP>.reg
#     <BARTSMAP>.tdb
#     <BARTSMAP>.typ
#     <BARTSMAP>.mdx (on Cygwin only)

# Remove old junk and temporary files
rm -f *.reg *.img *.TDB

# We're going to loop over all maps and each map needs a different ID.  This
# is our starting value and it will get incremented in each loop iteration.
ID=19780321

# Family ID.
# TODO: check whether this needs to be the same over all maps.
FID=123

# Setup our our temporary preview control file (mypreview_temp.mp) which is
# used to generate all the necessary files (.TDB, .REG, .IMG) so that we can
# load all the stuff as a map in QLandkarteGT or MapSource.
COMBINED_NAME=BARTSMAP
sed -e "s/^FileName=.*/FileName=${COMBINED_NAME}/g" \
    -e "s/^MapsourceName=.*/MapsourceName=Bart's Fantastic Airspace Maps/g" \
    -e "s/^IMG=.*//g" mypreview.mp > mypreview_temp.mp

mkdir -p ../build/garmin/
mkdir -p ../build/nsis/
> ../build/nsis/create_registry_keys.nsi
> ../build/nsis/delete_registry_keys.nsi

# Loop over all maps in Polish format.
for POLISH_FILE in ../build/polish_format/*.mp;
do

  SUBMAP_NAME=$(basename ${POLISH_FILE})
  SUBMAP_NAME=${SUBMAP_NAME%%.*}

  # Increment the ID to have a unique ID for each map.
  ID=$((ID + 1))

  # First, create an IMG file from the given Polish file.  With the 'ac' option
  # we make sure that the name of the file will be as defined by the ID key
  # in the header of the Polish file.  The -l option is just more elaborate
  # error info.
  # After this step, we get one extra file:
  #   <ID_from_Polish_file>.img
  sed -i "s/^ID=.*/ID=$ID/g" $POLISH_FILE
  cgpsmapper -l ac $POLISH_FILE

  sed -i -e "s/\[END-FILES\]/IMG=${ID}.img\n\[END-FILES\]/g" mypreview_temp.mp

done

unamestr=`uname -s`
if [[ $unamestr =~ .*CYGWIN.* ]]; then

  cpreview mypreview_temp.mp
  cgpsmapper ${COMBINED_NAME}.mp

elif [[ $unamestr =~ .*(Linux|Darwin).* ]]; then

  # This command generates the extra files:
  #   <COMBINED_NAME>.img
  #   <COMBINED_NAME>.reg
  #   <COMBINED_NAME>.TDB
  echo "Doing the preview thing..."
  cgpsmapper -l pv mypreview_temp.mp
  echo "done."

fi
rm -f mypreview_temp.mp


# Create a custom TYP file
# Note:
#   Filename cannot be longer than 8+3 characters.
echo "Generating custom TYP file..."
cgpsmapper typ Airspace.txt ${COMBINED_NAME}.TYP
echo "done."

# Move everything to the garmin build directory.
mv *.img   ../build/garmin/
mv $COMBINED_NAME.reg ../build/garmin/
mv $COMBINED_NAME.TDB ../build/garmin/$COMBINED_NAME.tdb
mv $COMBINED_NAME.TYP ../build/garmin/$COMBINED_NAME.typ
if [[ $unamestr =~ .*CYGWIN.* ]]; then
  mv $COMBINED_NAME.MDX ../build/garmin/$COMBINED_NAME.mdx
fi
rm -f $COMBINED_NAME.mp

# Add necessary stuff to the NSIS installer script.
printf "!insertmacro writeRegistryEntries \"$COMBINED_NAME\" %x00\n" $FID >> ../build/nsis/create_registry_keys.nsi
printf "DeleteRegKey \"HKLM\" \"Software\Garmin\Mapsource\Families\\$COMBINED_NAME\"\n" >> ../build/nsis/delete_registry_keys.nsi
