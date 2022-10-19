#!/bin/bash
hostname=$(ip -4 addr | grep -oP '(?<=inet\s)\d+(\.\d+){3}' | sed -n 2p)
if [ $# != 3 ]
then
    echo "usage: $0 <port> <password> <nickname>"
    exit 0
fi
irssi -c localhost -p $1 -w $2 -n $3 -h hostname