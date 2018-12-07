#/bin/bash

for D in ./nxt/*/; do cd $D; make all; done