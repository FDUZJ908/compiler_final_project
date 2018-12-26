make clean
make
if [ ! -d "./results" ]; then
    mkdir ./results
fi
for i in 01 02 03 05 07 08 12 15 16 17 19 20 50
do
    ./build/bin/main ./tests/test${i}.pcat > ./results/test${i}
done
make clean
echo -e "done"
