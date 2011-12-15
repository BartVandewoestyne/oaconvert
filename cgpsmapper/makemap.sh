#!/bin/bash

# Check if a Polish file has been specified.
if [ $# -ne 1 ]
then
  echo "Usage: `basename $0` path/to/some_polish_file.mp"
  exit $E_BADARGS
fi

# Remove old junk.
rm -f *.reg *.img *.TDB airspace.mp

# First, create an IMG file from the given Polish file.  With the 'ac' option
# we make sure that the name of the file will be as defined by the ID key
# in the header of the Polish file.  The -l option is just more elaborate
# error info.
cgpsmapper -l ac $1

# Secondly, use our preview control file (mypreview.mp) to generate all the
# necessary files (.TDB, .REG, .IMG) so that we can load all the stuff as
# a map in QLandkarteGT or MapSource.
unamestr=`uname -o`
if [[ "$unamestr" == 'Cygwin' ]]; then
  cpreview mypreview.mp
  cgpsmapper airspace.mp
elif [[ "$unamestr" == 'Linux' || "$unamestr" == 'GNU/Linux' ]]; then
  cgpsmapper -l pv mypreview.mp
fi

# Create a custom TYP file
cgpsmapper typ Airspace.txt AIRSPACE.TYP

mkdir -p ../build/garmin/
mv 19780321.img   ../build/garmin/
mv airspace.img ../build/garmin/
mv airspace.TDB ../build/garmin/
mv AIRSPACE.TYP ../build/garmin/
if [[ "$unamestr" == 'Cygwin' ]]; then
  mv airspace.MDX ../build/garmin/
fi

# After setting ProductCode=1 in the Polish file and the preview file,
# putting all .img and .tdb files in
#
#   "C:\\Program Files\\Belgian Airspace Maps\\"
#
# the registry file content should be changed to:
# ------------------------------------------------------------------------------
# REGEDIT4
# 
# [HKEY_LOCAL_MACHINE\SOFTWARE\Garmin\MapSource\Products\1]
# "LOC"="C:\\Program Files\\Belgian Airspace Maps\\"
# "BMAP"="C:\\Program Files\\Belgian Airspace Maps\\MyFileName.img"
# "TDB"="C:\\Program Files\\Belgian Airspace Maps\\MyFileName.tdb"
# ------------------------------------------------------------------------------
