#!/bin/bash

javac $1

OIFS=$IFS
IFS="."
export IFS

index=0
for word in $1
do
	arr[$index]="$word"
	index=`expr $index + 1`
done
java ${arr[0]}

IFS=$OIFS
