#/bin/bash

cd ./P5/nxt;
for D in */; do cd $D; make all; cd ..; done

echo "Success!";