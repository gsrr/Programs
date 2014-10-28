#!/bin/bash
for i in `seq 1 100`
do
	sudo ./dhcpdiscover_attack -v $i
	sleep 1
done
