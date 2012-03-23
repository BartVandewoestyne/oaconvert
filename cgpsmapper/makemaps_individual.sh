#!/bin/bash
#
# Generate the Garmin maps from the files in the build/polish_format/ directory.
# Once this script is finished, a new build/garmin/ directory is created with
# for each map the following files:
#
#     <ID>.img
#     <ID>.TYP
#     <MAP_NAME>.img
#     <MAP_NAME>.reg
#     <MAP_NAME>.TDB
#     <MAP_NAME>.MDX (on Cygwin only)

# Remove old junk and temporary files
rm -f *.reg *.img *.TDB

# We're going to loop over all maps and each map needs a different ID and FID.
# These are our starting values and they will get incremented in each loop
# iteration.
ID=19780321
FID=122

mkdir -p ../build/nsis/
> ../build/nsis/create_registry_keys.nsi
> ../build/nsis/delete_registry_keys.nsi

# Loop over all maps in Polish format
for POLISH_FILE in ../build/polish_format/*.mp;
do

  MAP_FILENAME=$(basename ${POLISH_FILE})
  MAP_FILENAME=${MAP_FILENAME%%.*}

  # Increment the ID and FID to have a unique ID and FID for each map.
  ID=$((ID + 1))
  FID=$((FID + 1))


  # First, create an IMG file from the given Polish file.  With the 'ac' option
  # we make sure that the name of the file will be as defined by the ID key
  # in the header of the Polish file.  The -l option is just more elaborate
  # error info.
  # After this step, we get one extra file:
  #   <ID_from_Polish_file>.img
  sed -i -e "s/^ID=.*/ID=$ID/g" \
         -e "s/^Name=.*/Name=$MAP_FILENAME/g" $POLISH_FILE
  cgpsmapper -l ac $POLISH_FILE


  # Secondly, use our preview control file (mypreview.mp) to generate all the
  # necessary files (.TDB, .REG, .IMG) so that we can load all the stuff as
  # a map in QLandkarteGT or MapSource.

  sed -e "s/^FileName=SomeFileName/FileName=${MAP_FILENAME}/g" \
      -e "s/^MapsourceName=.*/MapsourceName=Bart's Fantastic Airspace Maps: ${MAP_FILENAME}/g" \
      -e "s/^MapSetName=.*/MapSetName=Bart's Airspace Map Set: ${MAP_FILENAME}/g" \
      -e "s/^CDSetName=.*/CDSetName=Bart's Airspace CD Set: ${MAP_FILENAME}/g" \
      -e "s/^IMG=.*/IMG=$ID.img/g" \
      -e "s/^FID=.*/FID=$FID/g" mypreview.mp > mypreview_temp.mp

  unamestr=`uname -o`
  if [[ $unamestr =~ .*Cygwin.* ]]; then
  
    cpreview mypreview_temp.mp
    cgpsmapper $MAP_FILENAME.mp
  
  elif [[ $unamestr =~ .*Linux.* ]]; then
  
    # This command generates the extra files:
    #   <MAP_FILENAME>.img
    #   <MAP_FILENAME>.reg
    #   <MAP_FILENAME>.TDB
    echo "Doing the preview thing..."
    cgpsmapper -l pv mypreview_temp.mp
    echo "done."
  
  fi
  rm -f mypreview_temp.mp


  # Create a custom TYP file.
  # Note:
  #   According to cgpsmapper output, TYP-filename cannot be longer than 8+3
  #   characters... so that is why we use the ID here instead of MAP_FILENAME.
  TYP_FILE=Airspace_chessboard.txt
  echo "Generating custom TYP file..."
  sed -e "s/^FID=.*/FID=$FID/g" $TYP_FILE > Airspace_temp.txt
  cgpsmapper typ Airspace_temp.txt $ID.TYP
  rm -f Airspace_temp.txt
  echo "done."
  

  # Move everything to the garmin build directory.
  mkdir -p ../build/garmin/

  mv $ID.img   ../build/garmin/
  mv $MAP_FILENAME.img ../build/garmin/
  mv $MAP_FILENAME.reg ../build/garmin/
  mv $MAP_FILENAME.TDB ../build/garmin/$MAP_FILENAME.tdb
  mv $ID.TYP ../build/garmin/$ID.typ
  if [[ $unamestr =~ .*Cygwin.* ]]; then
    mv $MAP_FILENAME.MDX ../build/garmin/$MAP_FILENAME.mdx
  fi
  rm -f $MAP_FILENAME.mp

  # Add necessary stuff to the NSIS installer script.
  printf "!insertmacro writeRegistryEntries \"$MAP_FILENAME\" %x00 %d\n" $FID $ID>> ../build/nsis/create_registry_keys.nsi
  printf "DeleteRegKey \"HKLM\" \"Software\Garmin\Mapsource\Families\\$MAP_FILENAME\"\n" >> ../build/nsis/delete_registry_keys.nsi

done
