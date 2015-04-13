#!/bin/bash

filename=$1
ext="${filename##*.}"
name="${filename%.*}"

javac $filename
java $name
