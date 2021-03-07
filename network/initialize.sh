#!/bin/zsh

local SECTOR="D"
local ROOM_NAME=""
local PASSWORD=("pseudo" "i09gas") # first room does NOT have password.
local GROUP_NAME="sector$SECTOR"

groupadd $GROUP_NAME

for number in 1 2
do
    ROOM_NAME="room$SECTOR$number"

    useradd -m -g "$GROUP_NAME" -s $(which zsh) -p $(openssl passwd -crypt $(echo "$PASSWORD[$number]")) "$ROOM_NAME"
    cp "p$number"/* "p$number/".* "/home/$ROOM_NAME/"
    cp "../.tmux.conf" "../.zshrc" "/home/$ROOM_NAME/"

    chown "$ROOM_NAME":"$GROUP_NAME" "/home/$ROOM_NAME/client.c"

    chmod o-rx "/home/$ROOM_NAME"
done

passwd -d "room$SECTOR""1"