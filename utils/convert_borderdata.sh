#!/bin/bash
#
# This script takes the third-party .poly files from the cloudmade directory
# and generates OpenAir (.txt) and Polish (.mp) versions of these files.

for file in ../third_party_data/cloudmade/*.poly
do

  echo -n "Converting $file to ${file%%.poly}.txt..."
  ./convert_polyfile.awk $file > ${file%%.poly}.txt
  echo "done."

  echo -n "Converting ${file%%.poly}.txt to ${file%%.poly}.mp..."
  ../src/oaconvert -o ${file%%.poly}.mp ${file%%.poly}.txt
  echo "done."

done
