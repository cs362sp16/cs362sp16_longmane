# Emily Longman 5/13/16
# Script to run random tests quickly and easily

echo "RANDOM CARD TESTS"

echo "Starting randomtestadventurer..."
echo "Seed: 45"
echo "Times: 1000"
rm -f randomtestadventurer.out
randomtestadventurer 45 2000 0 >> randomtestadventurer.out
gcov dominion.c >> randomtestadventurer.out
echo 
echo 
echo 
cat randomtestadventurer.out
echo 
echo
echo


echo "Running: randomtestcard1"
echo "Seed: 45"
echo "Times: 1000"
rm -f randomtestcard1.out
randomtestcard1 45 2000 0 >> randomtestcard1.out
gcov dominion.c >> randomtestcard1.out
echo 
echo 
echo
cat randomtestcard1.out
echo 
echo
echo


echo "Running: randomtestcard2"
echo "Seed: 45"
echo "Times: 1000"
rm -f randomtestcard2.out
randomtestcard2 45 2000 0 >> randomtestcard2.out
gcov dominion.c >> randomtestcard2.out
echo 
echo 
echo
cat randomtestcard2.out
echo 
echo
echo
