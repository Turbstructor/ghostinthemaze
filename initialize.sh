#!/bin/zsh

STAGES=("A" "B" "C" "D" "E")
SECTOR_NAME=""

for stage in $STAGES
do
    SECTOR_NAME="sector$stage"
    useradd -m -g users -G sudo -s $(which zsh) "$SECTOR_NAME" && passwd -d "$SECTOR_NAME"

    cp "/home/manager/.zshrc" "/home/$SECTOR_NAME/"
    cp "/home/manager/.tmux.conf" "/home/$SECTOR_NAME/"
done
