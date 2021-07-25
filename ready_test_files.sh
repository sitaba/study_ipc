#!/bin/bash

size=$((1024*1024))
if [ ! $# -eq 0 ]; then
	size=$1
fi

#head -c ${size} /dev/urandom | base64 | tr -d = > random.txt 
base64 /dev/urandom | tr -dc "[:alnum:]" | head -c ${size} > random.txt
