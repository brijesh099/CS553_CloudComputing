#!/bin/bash

#make all

name=$(echo $1 | cut -d '-' -f1 -)
node1=$(echo $1 | cut -d '-' -f2 - | tr -d '[')
node2=$(echo $1 | cut -d '-' -f3 - | tr -d ']')

echo "the name nodes is $name-$node1"
echo "the hst name is $(hostname)"
if [ "$(hostname)" == "$name-$node1" ]
then
    echo $(hostname)
	echo "in server"
    ./MyNETBench-TCP network-TCP-1-1thread.dat
else
	echo "in client"
	sleep 30
    ./MyNETBench-TCP network-TCP-1-1thread.dat $name-$node1
fi