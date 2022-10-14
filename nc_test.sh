#!/bin/sh
# Copyright 2014 Vivien Didelot <vivien@didelot.org>
# Licensed under the terms of the GNU GPL v3, or any later version.

NICK=irccat42
SERVER=localhost
PORT=4343
CHAN="#irccat"

{
  # join channel and say hi
  cat << IRC
NICK $NICK
USER irccat 8 x : irccat
JOIN $CHAN
PRIVMSG $CHAN :Greetings!
IRC

  # forward messages from STDIN to the chan, indefinitely
  while read line ; do
    echo "$line" | sed "s/^/PRIVMSG $CHAN :/"
  done

  # close connection
  echo QUIT
} | nc $SERVER $PORT | while read line ; do
  case "$line" in
    *PRIVMSG\ $CHAN\ :*) echo "$line" | cut -d: -f3- ;;
    #*) echo "[IGNORE] $line" >&2 ;;
  esac
done
