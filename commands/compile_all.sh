#/bin/bash

ls;
cd nxt;
for D in */; do cd $D; make all; cd ..; done

echo "Success!";