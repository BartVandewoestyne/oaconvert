#!/bin/bash

# Check if a Polish file has been specified.
if [ $# -ne 1 ]
then
  echo "Usage: `basename $0` path/to/some_polish_file.mp"
  exit $E_BADARGS
fi

# Remove old junk.
rm -f *.reg *.img *.TDB

# First, create an IMG file from the given Polish file.  With the 'ac' option
# we make sure that the name of the file will be as defined by the ID key
# in the header of the Polish file.  The -l option is just more elaborate
# error info.
cgpsmapper -l ac $1

# Secondly, use our preview control file (mypreview.mp) to generate all the
# necessary files (.TDB, .REG, .IMG) so that we can load all the stuff as
# a map in QLandkarteGT or MapSource.
cgpsmapper -l pv mypreview.mp
