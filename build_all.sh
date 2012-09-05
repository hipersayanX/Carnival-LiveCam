#!/bin/bash

make clean
qmake
make
make clean
qdoc3 Carnival-LiveCam.qdocconf
