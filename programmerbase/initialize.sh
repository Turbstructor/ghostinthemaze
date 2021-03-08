#!/bin/zsh

local SECTOR="A"
local ROOM_NAME="programmerbase"
local GROUP_NAME="sector$SECTOR"

groupadd $GROUP_NAME
useradd -g $GROUP_NAME -s /bin/bash -p $(openssl passwd -crypt $(echo "7")) $ROOM_NAME

for number in 1 2 3 4 5 6 7 8 9
do
    mkdir "/home/sector$SECTOR/$number"
    mv "$number"* "/home/sector$SECTOR/$number/"
done

chown $ROOM_NAME:$GROUP_NAME /home/sector$SECTOR/7
chmod 700 /home/sector$SECTOR/7