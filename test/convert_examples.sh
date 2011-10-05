#!/bin/bash

echo -n "Converting test OpenAir files..."
for file in `ls ../openair/tests/*.txt`
do
  ../src/oa2pm -o ${file%%.txt}.mp ${file};
done
echo " done."

echo -n "Combining OpenAir files for the Belgian airspace to one map..."
cat ../openair/belgium/*.txt > ../openair/belgium/belgium.TXT
../src/oa2pm -o ../openair/belgium/belgium.mp ../openair/belgium/belgium.TXT
echo " done."

echo -n "Converting third party OpenAir files..."
for file in `ls ../openair/third_party/winpilot/*.txt ../openair/third_party/*.txt ../openair/third_party/lvzc/*.txt`
do
  ../src/oa2pm -o ${file%%.txt}.mp ${file};
done
echo " done."
