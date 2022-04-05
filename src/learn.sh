#!/bin/bash

funcs="obs1 obs6 obs16 basic cube gauss2 sig square"
model="ridge lasso elastic"

SCRIPT="src/learning.py"


for i in $funcs
do
    for j in $model
    do
        echo "Generating pgf for $i $j"
        python3 $SCRIPT $i $j
    done
done