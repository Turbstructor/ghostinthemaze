#!/bin/zsh

local SECTOR="C"
local ROOM_NAME=""
local PASSWORD=("pseudo" "wi1o2p" "ws9f87" "f7a89a" "Jkjlk2") # first room does NOT have password.
local GROUP_NAME="sector$SECTOR"

groupadd $GROUP_NAME

for number in 1 2 3 4 5
do
    ROOM_NAME="room$SECTOR$number"

    mkdir -p "/home/$GROUP_NAME/$ROOM_NAME"

    useradd -d "/home/$GROUP_NAME/$ROOM_NAME" -g "$GROUP_NAME" -s $(which zsh) -p $(openssl passwd -crypt $(echo "$PASSWORD[$number]")) "$ROOM_NAME"
    chown $ROOM_NAME:$GROUP_NAME "/home/$GROUP_NAME/$ROOM_NAME"
    
    cp "p$number"/* "p$number/".* "/home/$GROUP_NAME/$ROOM_NAME"
    cp "../.tmux.conf" "../.zshrc" "/home/$GROUP_NAME/$ROOM_NAME"

    chown "$ROOM_NAME":"$GROUP_NAME" "/home/$GROUP_NAME/$ROOM_NAME/p$number.cpp"

    chmod o-rx "/home/$GROUP_NAME/$ROOM_NAME"
done

passwd -d "room$SECTOR""1"