#!/bin/bash

echo -n "Enter directory to compare to: "
read dir2

echo -n "Seed: "
read seed

make all
make testdom

cd $dir2
make all
make testdom

cd ..

testdom $seed > testout1
$dir2/testdom $seed > $dir2/testout2

diff --suppress-common-lines t1/testout1 $dir2/testout2 > diff_result
 
if [[ -s diff_result ]] ; then
   echo "TEST FAILED"
else
   echo "TEST SUCCESS"
fi ;
