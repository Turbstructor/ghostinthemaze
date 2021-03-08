#!/bin/zsh

local SECTOR="B"
local GROUP_NAME="sector$SECTOR"

groupadd $GROUP_NAME
g++ -o crossword crossword.cpp
cp crossword ../
chown "sector$SECTOR":users ../crossword