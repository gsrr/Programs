#!/bin/bash

rm tmp
compiler=$1
filename=$2
ext="${filename##*.}"
name="${filename%.*}"
$compiler -o $name $filename -lm

