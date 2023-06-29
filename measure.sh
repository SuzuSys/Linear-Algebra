#!/bin/sh
echo -n "" > results/determinant.csv
echo -n "" > results/clock.csv
for i in {1000..1}
do
    for j in {0..9}
    do
        ./data_generator ${i} ${j} 0
        CPP=(`./determinant`)
        echo "${CPP[1]}" >> results/clock.csv
        PYTHON=`python3 exact_determinant.pyc`
        echo "${CPP[0]} ${PYTHON}" >> results/determinant.csv
    done
    echo "${i}"
done