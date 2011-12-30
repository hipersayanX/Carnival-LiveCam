#!/bin/bash

basedir=$PWD

for project in $(find . -path './extras' -prune -o -iname '*.pro')
do
    cd $basedir/$(dirname $project)

    make clean
    qmake && make

    if [ $? -ne 0 ];then
        exit 1
    fi

    make clean
done

cd $basedir

doxygen Doxyfile
