#!/bin/bash

src=$1
tgt=$2

cnt=0
for file in $1/*
do
	#echo "$file"
	arrO[ $cnt ]="$file"
	(( cnt++ ))
done


cnt=0
for file in $1/*
do
	#echo "$file"
	arrN[ $cnt ]="$file"
	(( cnt++ ))
done

echo $cnt
i=0
while [ $i != $cnt ]
do
	diff ${arrO[$i]} ${arrN[$i]}
	(( i++ ))
done
