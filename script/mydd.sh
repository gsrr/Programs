#!/bin/bash

outPath=$1
size=$2
dd if=/dev/urandom of=$outPath bs=1048576 count=$size
