#!/bin/bash

# Copy our generated Polish Files here.
cp ../openair/belgium/belgium.mp .

# First, create an IMG file from the given Polish file.  With the 'ac' option
# we make sure that the name of the file will be as defined by the ID key
# in the header of the Polish file.  The -l option is just more elaborate
# error info.
cgpsmapper -l ac belgium.mp

# Secondly, use our preview control file (mypreview.mp) to generate all the
# necessary files (.TDB, .REG, .IMG) so that we can load all the stuff as
# a map in QLandkarteGT or MapSource.
cgpsmapper -l pv mypreview.mp
