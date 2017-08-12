#!/bin/bash
for x in `seq 1 31999`; do

    cp 0000000.jpg $(printf "%07d.jpg" $x);

done
