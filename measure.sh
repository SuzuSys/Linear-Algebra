#!/bin/sh
echo -n "" > result.csv
echo -n "" > clock.csv
for i in {1..1000}
do
    for j in {0..9}
    do
        ./data_generator ${i} ${j} 0
        CPP=(`./determinant`)
        echo "${CPP[1]}" >> clock.csv
        PYTHON=0 #`python3 exact_determinant.pyc`
        echo "${CPP[0]} ${PYTHON}" >> result.csv 
    done
    echo "${i}"
done