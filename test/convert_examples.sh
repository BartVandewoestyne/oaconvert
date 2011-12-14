#!/bin/bash

#echo -n "Converting test OpenAir files..."
#for file in `ls ../openair/tests/*.txt`
#do
#  ../src/oaconvert -o ${file%%.txt}.mp ${file};
#done
#echo " done."

echo "Converting third party OpenAir files..."
for file in `ls ../openair/third_party/winpilot/*.txt ../openair/third_party/wim_verhoeve/*.txt ../openair/third_party/lvzc/*.txt`
do
  echo -n "  Processing `basename ${file}`... "
  ../src/oaconvert -o ${file%%.txt}.mp ${file};
  echo "done."
done
echo "done."
