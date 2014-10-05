#!/bin/bash

for i in 0 {2..29}
do
	j=$(printf "%0*d\n" 3 $i)
	patch -p0 < ../bash43-$j
done
