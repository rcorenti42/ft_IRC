#!/bin/bash
if [ $# != 2 ]
then
    echo "usage: $0 <port> <password>"
    exit 0
fi
irssi -c localhost -p $1 -w $2
