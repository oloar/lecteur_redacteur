#! /usr/bin/bash

mkdir dist
PROJECTDIR=$PWD
for DIR in {priorite_{lecteur,redacteur},fifo}; do
    cd $PROJECTDIR/$DIR
    make dist
    make clean
done
