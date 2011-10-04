#!/bin/bash

echo -n "Converting test OpenAir files..."
for file in `ls ../openair/tests/*.txt`
do
  ../src/oa2pm $file > ${file%%.txt}.mp;
done
echo " done."

echo -n "Combining OpenAir files for the Belgian airspace to one map..."
cat ../openair/belgium/*.txt > ../openair/belgium/belgium.TXT
../src/oa2pm ../openair/belgium/belgium.TXT > ../openair/belgium/belgium.mp
echo " done."

echo -n "Converting third party OpenAir files..."
for file in `ls ../openair/third_party/winpilot/*.txt ../openair/third_party/*.txt`
do
  ../src/oa2pm $file > ${file%%.txt}.mp;
done
echo " done."
