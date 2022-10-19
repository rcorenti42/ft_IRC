#!/bin/bash
hostname=$(ip -4 addr | grep -oP '(?<=inet\s)\d+(\.\d+){3}' | sed -n 2p)
irssi -c localhost -p 4243 -w lol -h hostname