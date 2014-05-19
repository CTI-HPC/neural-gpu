#!/bin/bash

for DIR in integral map
do
    cd $DIR
    make clean
    cd ..
    tar caf $DIR.tgz $DIR
done

