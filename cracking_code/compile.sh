#!/bin/bash

rm tmp
filename=$1
ext="${filename##*.}"
name="${filename%.*}"
gcc -o $name $filename -lm

